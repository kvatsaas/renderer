#ifndef __SCENE_H__
#define __SCENE_H__ 1

#include <string>
#include <map>

#include "XMLSceneParser.h"
#include "handleGraphicsArgs.h"

#include "SceneDataTypes.h"

using boost::property_tree::ptree;

class SceneFile_Instancer : public sivelab::SceneElementCreator
{
public:

    SceneFile_Instancer() {}
    ~SceneFile_Instancer() {}

  // Derived class functions
  void instance( ptree::value_type const &v ); 

private:

    void parseShapeData( ptree::value_type const &v );
    shaderData* parseShaderData( ptree::value_type const &v );
    
    // std::map<std::string, Texture*> textureSources;
    std::map<std::string, shaderData*> shaderMap;

};

#endif
