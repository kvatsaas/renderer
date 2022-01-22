/*
 *  test_JSONSceneParse.cpp
 *
 *  Created by Pete Willemsen on 02/18/19.
 *  Copyright 2019 Department of Computer Science, University of Minnesota-Duluth. All rights reserved.
 *
 * This file is part of CS5721 Computer Graphics library (cs5721Graphics).
 *
 * cs5721Graphics is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * cs5721Graphics is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with cs5721Graphics.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cassert>

#include "Vector3D.h"
#include "handleGraphicsArgs.h"
#include "jsonSceneParser.h"

using namespace sivelab;

class Camera 
{
public:
    Camera() : m_position(0,0,0), m_viewDir(0,0,-1) {}
    Camera(Vector3D &p, Vector3D &v) : m_position(p), m_viewDir(v) {}
    Camera(json &j) {}
    virtual ~Camera() = default;

protected:
    Vector3D m_position;
    Vector3D m_viewDir;
};

class PerspectiveCamera : public Camera
{
public:
    PerspectiveCamera() : Camera() {}
    PerspectiveCamera(Vector3D &p, Vector3D &v) : Camera(p, v) {}
    PerspectiveCamera(json &j) : Camera(j) {}
    ~PerspectiveCamera() = default;
};


class SceneContainer
{
public:
    SceneContainer( std::string &filename )
    {
        std::cout << "Attempting to parse: " << filename << std::endl;
        std::ifstream inputFileStream( filename );

        // 
        // open file and parse by json class
        //
        json j;
        inputFileStream >> j;

        // 
        // walk over all cameras.
        //
        sivelab::Vector3D p;
        json cameras = j["scene"]["camera"];
        std::cout << "array of cameras? " << cameras.is_array() << std::endl;
        if (cameras.is_array()) {
            std::cout << "Number of cameras: " << cameras.size() << std::endl;
            for (auto i=0; i<j["scene"]["camera"].size(); i++) {  

                if (j["scene"]["camera"]["_type"] == "perspective") {
                    std::cout << "Perspective Camera: " << j["scene"]["camera"]["position"] << std::endl;

                    json camInfo = j["scene"]["camera"];
                    
                    float focalLength = camInfo["focalLength"];
                    Vector3D position;
                    position = j["scene"]["camera"]["position"];
                    
                    //cameraVector.push_back( new PerspectiveCamera( ) );
                }
                else if (j["scene"]["camera"]["_type"] == "orthographic") {
                    std::cout << "Orthographic Camera: " << j["scene"]["camera"]["position"] << std::endl;
                    // cameraVector.push_back( new OrthoPerspectiveCamera(...) );
                }
                
            }
        }
        else {
            std::cout << "Perspective Camera: " << j["scene"]["camera"]["position"] << std::endl;
            p = j["scene"]["camera"]["position"];
        }
        std::cout << p << std::endl;

        // Walk over all shapes

        // Walk over all shaders
       std::cout << "Number of shaders: " << j["scene"]["shader"].size() << std::endl;
        for (auto i=0; i<j["scene"]["shader"].size(); i++) {
            sivelab::Vector3D diffuse;
            diffuse = j["scene"]["shader"][i]["diffuse"];
            std::cout << "diffuse = " << diffuse << std::endl;
        }
        
    }

private:
    std::vector<Camera*> cameraVector;
};


int main(int argc, char *argv[])
{
  GraphicsArgs args;
  args.process(argc, argv);

  if (args.inputFileName == "") {
      std::cerr << "Need input file!" << std::endl;
      exit(EXIT_FAILURE);
  }
  

  exit(EXIT_SUCCESS);
}


