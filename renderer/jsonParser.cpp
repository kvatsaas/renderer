/* Adapted from provided code. */

#define GLM_ENABLE_EXPERIMENTAL
#define EXTRACT_ROTATION_READY 0
#define TRANSFORMS_READY 0
#define MESHES_READY 0
#define ADVSHADERS_READY 0
#define ADVLIGHTS_READY 0

#include <iostream>
#include <fstream>
#include <glm/gtx/string_cast.hpp>
#include <nlohmann/json.hpp>
#include <stack>
#include <assert.h>

#include "SceneContainer.h"
#include "PerspectiveCamera.h"
#include "OrthographicCamera.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Box.h"
#include "PointLight.h"
#include "shaders.h"
//#include "Constants.h"// contains a static PI

using json = nlohmann::json;
using namespace renderer;

namespace renderer {


#if EXTRACT_ROTATION_READY
glm::mat4 extractRotation(json &rotInfo)
{
  glm::mat4 tmpM(1.0f);
  float rot = rotInfo["amount"];
  std::string axis = rotInfo["axis"];

  if (axis == "X") {
    tmpM = glm::rotate(glm::mat4(1.0f), rot * RConsts::m_pi / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    ;
  } else if (axis == "Y") {
    tmpM = glm::rotate(glm::mat4(1.0f), rot * RConsts::m_pi / 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    ;
  } else if (axis == "Z") {
    tmpM = glm::rotate(glm::mat4(1.0f), rot * RConsts::m_pi / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    ;
  }

  return tmpM;
}
#endif


glm::mat4 parseTransformData(json &transformData)
{
  glm::mat4 glM(1.0f);

  glm::mat4 tmpM(1.0f);
  std::stack<glm::mat4> transformStack;

  assert(transformData.is_array());
  for (auto xIdx = 0; xIdx < transformData.size(); xIdx++) {

    json xformInfo = transformData[xIdx];

    // Translation transform
    if (xformInfo["type"] == "translate") {
      Vector3D translation;
      translation = xformInfo["amount"];
      tmpM = glm::translate(glm::mat4(1.0f), glm::vec3(translation[0], translation[1], translation[2]));
      transformStack.push(tmpM);
    } else if (xformInfo["type"] == "scale") {
      Vector3D scale;
      scale = xformInfo["amount"];
      tmpM = glm::scale(glm::mat4(1.0f), glm::vec3(scale[0], scale[1], scale[2]));
      transformStack.push(tmpM);
    } else if (xformInfo["type"] == "rotation") {
      //transformStack.push(extractRotation(xformInfo));
    }
  }

  while (!transformStack.empty()) {
    glm::mat4 m1 = transformStack.top();
    transformStack.pop();

    //        std::cout << "m = ";
    //        std::cout << glm::to_string(m1) << std::endl;

    // glM = glM * m1; // * glM;
    glM = m1 * glM;
  }

  // std::cout << "\n\nmodelMatrix = ";
  // std::cout << glm::to_string(glM) << std::endl;

  return glM;
}


Shape *extractAndCreateShapeFromJSONData(json &shapeData)
{
  Shape *sPtr = nullptr;

  std::string type = shapeData["_type"];
  std::string name = shapeData["_name"];

#if TRANSFORMS_READY
  // Need to find the transform in the second part of the shape pair
  glm::mat4 glM(1.0f);
  if (!shapeData["xform"].empty()) {
    glM = parseTransformData(shapeData["xform"]);
  }
#endif

  if (type == "sphere") {
    float radius;
    Vector3D center;

    center = shapeData["center"];
    radius = shapeData["radius"];

    sPtr = new Sphere(center, radius);
  } else if (type == "triangle") {
    Vector3D v0, v1, v2;
    v0 = shapeData["v0"];
    v1 = shapeData["v1"];
    v2 = shapeData["v2"];

    sPtr = new Triangle(v0, v1, v2);
  } else if (type == "box") {
    Vector3D minPt, maxPt;

    minPt = shapeData["minPt"];
    maxPt = shapeData["maxPt"];

    sPtr = new Box(minPt, maxPt);
  }

#if MESHES_READY
  else if (type == "mesh") {
    std::string mesh_filename = shapeData["file"];
    std::string meshFile_fullPath(getFilePath() + "/" + mesh_filename);

    Shader *defaultShader = locateShader(shapeData["shader"]["_ref"]);
    sPtr = new OBJMesh(meshFile_fullPath, defaultShader, m_useBVH);
  } else if (type == "instance") {

    // Need to instance an object
    // check for the instance id
    std::string instanceIDName = shapeData["_id"];

    // attempt to locate this object to instance in the
    // instanceMap
    std::map<std::string, Shape *>::iterator roIter = m_instanceMap.find(instanceIDName);
    if (roIter != m_instanceMap.end()) {
      Shape *robj = roIter->second;
      Matrix4x4 m(glM[0][0], glM[0][1], glM[0][2], glM[0][3], glM[1][0], glM[1][1], glM[1][2], glM[1][3], glM[2][0], glM[2][1], glM[2][2], glM[2][3], glM[3][0], glM[3][1], glM[3][2], glM[3][3]);
      m = m.transpose();
      Matrix4x4 minv = m.inverse();

      sPtr = new InstancedObject(robj, m, minv);

      if (!shapeData["shader"]["_ref"].empty()) {
        sPtr->provideShader(locateShader(shapeData["shader"]["_ref"]));
      }
    }
  }
#endif


  assert(sPtr);// must have one
  sPtr->setName(name);

  return sPtr;
}


void parseJSONData(const std::string &filename, SceneContainer &scene)
{
  std::cout << "Attempting to parse: " << filename << std::endl;
  std::ifstream inputFileStream(filename);

  // ///////////////////////////////////////
  // open file and parse by json class
  // ///////////////////////////////////////
  json j;
  inputFileStream >> j;

  // Grab the background color:
  if (!j["scene"]["_bgColor"].empty()) {
    scene.setBGColor(Vector3D(j["scene"]["_bgColor"]));
    std::cout << "BG Color: " << scene.getBGColor().toString() << std::endl;
  }

  // ///////////////////////////////////////
  //
  // Loop over all cameras in scene
  //
  // /////////////////////////////////////////
  Vector3D p;
  json jsonCameraStructure = j["scene"]["camera"];
  if (jsonCameraStructure.is_array()) {
    std::cout << "Number of cameras: " << jsonCameraStructure.size() << std::endl;

    for (auto i = 0; i < jsonCameraStructure.size(); i++) {

      json camInfo = jsonCameraStructure[i];

      Vector3D position, viewDir;
      position = camInfo["position"];

      if (!camInfo["lookatPoint"].empty()) {
        Vector3D lookAtPoint;
        lookAtPoint = camInfo["lookatPoint"];
        viewDir = lookAtPoint - position;
      } else {
        viewDir = camInfo["viewDir"];
      }

      float focalLength = camInfo["focalLength"];
      float imagePlaneWidth = camInfo["imagePlaneWidth"];
      std::string camType = camInfo["_type"];
      std::string camName = camInfo["_name"];

      if (camType == "perspective") {
        scene.addCamera(new PerspectiveCamera(camName, position, viewDir, focalLength, imagePlaneWidth, scene.get_nx(), scene.get_ny()));
      } else if (camType == "orthographic") {
        scene.addCamera(new OrthographicCamera(camName, position, viewDir, imagePlaneWidth, scene.get_nx(), scene.get_ny()));
      }
    }
  }

  // //////////////////////////////
  //
  // Loop over shaders and place them in a std::map
  //
  // //////////////////////////////
  std::cout << "Number of shaders: " << j["scene"]["shader"].size() << std::endl;
  for (auto i = 0; i < j["scene"]["shader"].size(); i++) {

    json shaderInfo = j["scene"]["shader"][i];
    std::string shaderType = shaderInfo["_type"];

    Shader *shaderPtr = nullptr;
    if (shaderType == "Lambertian" || shaderType == "Diffuse") {

      Vector3D diffuse;
      diffuse = shaderInfo["diffuse"];

      if (shaderType == "Lambertian")
        shaderPtr = new LambertianShader(diffuse);

      else if (shaderType == "Diffuse")
        shaderPtr = new LambertianShader(diffuse);//DiffuseShader(diffuse);
    }

#if ADVSHADERS_READY
    else if (shaderType == "Dielectric") {
      float refrIdx;
      Vector3D attenCoef;
      attenCoef = shaderInfo["attenuationCoef"];
      refrIdx = shaderInfo["refractiveIndex"];

      shaderPtr = new sivelab::Dielectric(refrIdx, attenCoef);
    }
#endif

    else if (shaderType == "BlinnPhong" || shaderType == "Phong") {

      float phongExp;
      Vector3D diffuse, specular;
      diffuse = shaderInfo["diffuse"];
      specular = shaderInfo["specular"];
      phongExp = shaderInfo["phongExp"];

      if (shaderType == "BlinnPhong")
        shaderPtr = new BlinnPhongShader(diffuse, specular, phongExp);
      else
        shaderPtr = new BlinnPhongShader(diffuse, specular, phongExp);//PhongShader(diffuse, specular, phongExp);
    }

    else if (shaderType == "Mirror") {
      shaderPtr = new MirrorShader();
    }
#if ADVSHADERS_READY
    else if (shaderType == "Glaze") {
      Vector3D kd;
      kd = shaderInfo["diffuse"];

      float mirrorCoef = 1.0;
      mirrorCoef = shaderInfo["mirrorCoef"];

      shaderPtr = new sivelab::Glaze(kd, mirrorCoef);
    } else if (shaderType == "BlinnPhongMirrored") {
      Vector3D d, s;

      d = shaderInfo["diffuse"];
      Vector3D kd(d, 0);

      // boost::optional<std::string> pTexName = v.second.get_optional<std::string>("diffuse.<xmlattr>.tex");
      // if (pTexName) {
      // kd = Vector3D(d, textureSources[*pTexName]);
      // }
      // else {
      // kd = Vector3D(d, 0);
      // }

      s = shaderInfo["specular"];

      // pTexName = v.second.get_optional<std::string>("specular.<xmlattr>.tex");
      // if (pTexName) {
      // find the texture ptr
      // ks = Vector3D(s, textureSources[*pTexName]);
      // }
      // else {
      Vector3D ks = Vector3D(s, 0);
      // }

      float phongExp = shaderInfo["phongExp"];

      float mirrorCoef = shaderInfo["mirrorCoef"];
      float roughnessCoef = shaderInfo["roughness"];

      shaderPtr = new sivelab::BlinnPhongMirrored(kd, ks, phongExp, mirrorCoef, roughnessCoef);
    }
#endif

    assert(shaderPtr);

    std::string name = shaderInfo["_name"];
    shaderPtr->setName(name);
    scene.addShader(shaderPtr);
  }


#if MESHES_READY
  // //////////////////////////////////////
  //
  // Loop over all shapes that may be instanced -- note that these
  // are located in an instance array
  //
  // //////////////////////////////////////
  std::cout << "Number of Instance Objects: " << j["scene"]["instance"].size() << std::endl;
  if (j["scene"]["instance"].is_array()) {

    for (auto i = 0; i < j["scene"]["instance"].size(); i++) {

      // This contains the information that needs to be instanced
      // but we need to still create the base shape.
      json instanceShapeData = j["scene"]["instance"][i];

      Shape *shapePtr = extractAndCreateShapeFromJSONData(instanceShapeData);
      m_instanceMap[instanceShapeData["_name"]] = shapePtr;
    }
  }
#endif


  // //////////////////////////////////////
  //
  // Loop over all shapes
  //
  // //////////////////////////////////////
  std::cout << "Number of shapes: " << j["scene"]["shape"].size() << std::endl;
  for (auto i = 0; i < j["scene"]["shape"].size(); i++) {

    json shapeInfo = j["scene"]["shape"][i];

    Shape *sPtr = extractAndCreateShapeFromJSONData(shapeInfo);

    if (!shapeInfo["shader"]["_ref"].empty()) {
      sPtr->setShader(scene.getShader(shapeInfo["shader"]["_ref"]));
    }

    scene.addShape(sPtr);
  }
  std::cout << "Completed parsing shapes." << std::endl;

  // Walk over all ligths
  std::cout << "Number of lights: " << j["scene"]["light"].size() << std::endl;
  for (auto i = 0; i < j["scene"]["light"].size(); i++) {

    std::string type = j["scene"]["light"][i]["_type"];

    Vector3D position, radiantEnergy;
    radiantEnergy = j["scene"]["light"][i]["intensity"];

    if (type == "point") {
      position = j["scene"]["light"][i]["position"];
      scene.addLight(new PointLight(position, radiantEnergy));
    }

#if ADVLIGHTS_READY
    else if (type == "area") {

      position = j["scene"]["light"][i]["position"];

      Vector3D normal;
      normal = j["scene"]["light"][i]["normal"];

      float width = 1.0, length = 1.0;
      width = j["scene"]["light"][i]["width"];
      length = j["scene"]["light"][i]["length"];

      AreaLight *aLight = new AreaLight(position, radiantEnergy, normal, width, length);
      lights.push_back(aLight);

      //
      // Create two triangles aligned with normal to represent the
      // light with an emissive shader.
      //
      // pos is the center of the light at this point (the area light
      // class manipulates it to the lower left of the light corner),
      // so lower left corner is
      //
      // pos - aLight->binormal()*width/2.0 - aLight->tangent()*length/2.0;

      Vector3D v0 = position - aLight->binormal() * width / 2.0 - aLight->tangent() * length / 2.0,
               v1 = position - aLight->binormal() * width / 2.0 + aLight->tangent() * length / 2.0,
               v2 = position + aLight->binormal() * width / 2.0 + aLight->tangent() * length / 2.0;

      sivelab::Emission *eSPtr = new sivelab::Emission(radiantEnergy);

      Triangle *tPtr = new Triangle(v0, v1, v2);
      tPtr->setIntersectionVisibility();
      tPtr->setName("area light");
      tPtr->provideShader(eSPtr);

      m_otherObjs.push_back(tPtr);

      v0 = position - aLight->binormal() * width / 2.0 - aLight->tangent() * length / 2.0;
      v1 = position + aLight->binormal() * width / 2.0 + aLight->tangent() * length / 2.0;
      v2 = position + aLight->binormal() * width / 2.0 - aLight->tangent() * length / 2.0;

      tPtr = new Triangle(v0, v1, v2);
      tPtr->setIntersectionVisibility();
      tPtr->setName("area light");
      tPtr->provideShader(eSPtr);

      m_otherObjs.push_back(tPtr);
    }

    else if (type == "shape") {

      json shapeInfo = j["scene"]["light"][i]["shape"];

      std::cout << "shape emitter: " << shapeInfo << std::endl;

      Shape *emitter_ShapePtr = extractAndCreateShapeFromJSONData(shapeInfo);

      sivelab::Emission *eSPtr = new sivelab::Emission(radiantEnergy);

      emitter_ShapePtr->provideShader(eSPtr);
      m_otherObjs.push_back(emitter_ShapePtr);
    }
#endif
  }
}

}// namespace renderer