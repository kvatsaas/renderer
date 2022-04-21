#include <iostream>

#include "OBJMesh.h"
#include "Triangle.h"
#include "BlinnPhongShader.h"

#include "../src/model_obj.h"

namespace renderer {

OBJMesh::OBJMesh(const std::string &filename, Shader *defaultShader)
{
  std::vector<int> indexList;
  std::vector<Vector3D> vertexList;

  std::cerr << "Parsing render file: " << filename << "..." << std::endl;

  ModelOBJ mOBJ;
  if (mOBJ.import(filename.c_str()))
    std::cout << "...loading successful." << std::endl;
  else {
    std::cout << "...unsuccessful! Exiting!" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << "Number of meshes contained within OBJ: " << mOBJ.getNumberOfMeshes() << std::endl;
  std::cout << "Number of triangles contained within OBJ: " << mOBJ.getNumberOfTriangles() << std::endl;

  const ModelOBJ::Mesh *pMesh = 0;
  const ModelOBJ::Material *pMaterial = 0;
  const ModelOBJ::Vertex *pVertices = 0;
  std::vector<Shape *> triList;// list of triangles in a mesh

  // Create a vector of BVH Nodes... each triangle Mesh within the OBJ
  // will become a BVH itself.  We can then use the list of BVH's to
  // construct a BVH.  There may be better ways to do this, but this was easy
  // and works reasonably well.
  std::vector<Shape *> bvhNodeList;

  const int *idxBuffer = mOBJ.getIndexBuffer();
  for (int mIdx = 0; mIdx < mOBJ.getNumberOfMeshes(); mIdx++) {

    // Clear the triangle list for each mesh so we can keep adding
    // separate BVHs for the different meshes that exist.
    triList.clear();

    pMesh = &mOBJ.getMesh(mIdx);
    pMaterial = pMesh->pMaterial;
    pVertices = mOBJ.getVertexBuffer();

    // We use a BlinnPhong shader here because the materials within
    // the OBJ file provide diffuse, specular and phong (shininess)
    // components.
    Shader *shaderPtr = nullptr;
    if (pMaterial) {
      shaderPtr = new BlinnPhongShader(Vector3D(pMaterial->diffuse[0], pMaterial->diffuse[1], pMaterial->diffuse[2]),
        Vector3D(pMaterial->specular[0], pMaterial->specular[1], pMaterial->specular[2]),
        pMaterial->shininess);
    } else {
      shaderPtr = defaultShader;
    }

    for (int i = pMesh->startIndex; i < (pMesh->startIndex + pMesh->triangleCount * 3); i += 3) {
      ModelOBJ::Vertex v0, v1, v2;
      v0 = pVertices[idxBuffer[i]];
      v1 = pVertices[idxBuffer[i + 1]];
      v2 = pVertices[idxBuffer[i + 2]];

      // Update the estimate of the bounding box based on the most recent triangle
      Vector3D tv0(v0.position[0], v0.position[1], v0.position[2]);
      Vector3D tv1(v1.position[0], v1.position[1], v1.position[2]);
      Vector3D tv2(v2.position[0], v2.position[1], v2.position[2]);
      bound.addPoint(tv0);
      bound.addPoint(tv1);
      bound.addPoint(tv2);

      Triangle *tPtr = new Triangle(tv0, tv1, tv2, shaderPtr);
      tPtr->setNormals(Vector3D(v0.normal[0], v0.normal[1], v0.normal[2]), Vector3D(v1.normal[0], v1.normal[1], v1.normal[2]), Vector3D(v2.normal[0], v2.normal[1], v2.normal[2]), false);

      // Add the triangle to the mesh's triangle list
      triList.push_back(tPtr);
    }

    // Add the triangle list from the mesh as a BVH to our list of BVHs for
    // the entire model
    bvhNodeList.push_back(new BVHNode(triList, 0));
  }

  // Finally, create one BVH for all the BVH's in the list
  meshRoot = new BVHNode(bvhNodeList, 0);
}

bool OBJMesh::closestHit(const Ray &r, const float tmin, float &tmax, HitStructure &hit, int depth)
{
  if (!bound.intersectClosest(r, depth))
    return false;

  return meshRoot->closestHit(r, tmin, tmax, hit, depth);
}

bool OBJMesh::hit(const Ray &r, float tmin, float tmax, int depth)
{
  if (!bound.intersectAny(r, depth))
    return false;

  return meshRoot->hit(r, tmin, tmax, depth);
}

}// namespace renderer