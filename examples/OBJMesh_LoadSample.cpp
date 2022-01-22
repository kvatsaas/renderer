#include "model_obj.h"

void load(const std::string &filename)
{ 
  std::vector<int> indexList;
  std::vector<Vector3D> vertexList;
  
  std::cerr << "Parsing render file: " << filename << "..." << std::endl;
  
  ModelOBJ mOBJ;
  if (mOBJ.import( filename.c_str() ))
    std::cout << "...loading successful." << std::endl;
  else 
    {
      std::cout << "...unsuccessful! Exiting!" << std::endl;
      exit(EXIT_FAILURE);
    }

  std::cout << "Number of meshes contained within OBJ: " << mOBJ.getNumberOfMeshes() << std::endl;
  std::cout << "Number of triangles contained within OBJ: " << mOBJ.getNumberOfTriangles() << std::endl;

  const ModelOBJ::Mesh *pMesh = 0;
  const ModelOBJ::Material *pMaterial = 0;
  const ModelOBJ::Vertex *pVertices = 0;

  const int *idxBuffer = mOBJ.getIndexBuffer();
  for (int mIdx=0; mIdx<mOBJ.getNumberOfMeshes(); mIdx++)
    {
      pMesh = &mOBJ.getMesh(mIdx);
      pMaterial = pMesh->pMaterial;
      pVertices = mOBJ.getVertexBuffer();
    
      // Would be good to look over the material structure so that you
      // can create the correct shader here for the mesh
      // 
      // pMaterial->diffuse[0], pMaterial->diffuse[1], pMaterial->diffuse[2], etc...

      for (int i=pMesh->startIndex; i<(pMesh->startIndex + pMesh->triangleCount*3); i+=3)
	{
	  ModelOBJ::Vertex v0, v1, v2;
	  v0 = pVertices[ idxBuffer[i] ];
	  v1 = pVertices[ idxBuffer[i+1] ];
	  v2 = pVertices[ idxBuffer[i+2] ];
	  
	  // ModelOBJ Vertex follows this format: v0.position[0],
	  // v0.position[1], v0.position[2]

	  // You can also access the normals too v0.normal[0],
	  // v0.normal[1], v0.normal[2]. Notice that these are part of
	  // the ModelOBJ::Vertex structure.
	}      
    }
}
