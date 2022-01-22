/*
 *  test_XMLSceneParse.cpp
 *
 *  Created by Pete Willemsen on 10/6/09.
 *  Copyright 2009 Department of Computer Science, University of Minnesota-Duluth. All rights reserved.
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
#include <cstdlib>
#include <cassert>

#include "Vector3D.h"
#include "handleGraphicsArgs.h"
#include "XMLSceneParser.h"

#include "SceneFile_Instancer.h"

using namespace sivelab;

int main(int argc, char *argv[])
{
  GraphicsArgs args;
  args.process(argc, argv);

  XMLSceneParser xmlScene;

  SceneFile_Instancer *sceneFactory = new SceneFile_Instancer();

  // register object creation function with xmlScene
  xmlScene.registerCallback("camera", sceneFactory);
  xmlScene.registerCallback("light", sceneFactory);
  xmlScene.registerCallback("shader", sceneFactory);
  xmlScene.registerCallback("shape", sceneFactory);

  std::cout << "Width = " << args.width << std::endl;

  if (args.inputFileName != "")
    xmlScene.parseFile( args.inputFileName );
  else
    {
      std::cerr << "Need input file!" << std::endl;
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);
}


