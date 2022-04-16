#pragma once
#include <vector>
#include <map>

using namespace std;

/* This file includes a number of different vectors containing triangle data for different
 * components of the OpenGL labs, for easy switching. Note that different fragment/vertex
 * shaders are needed depending on the scene.
*/

/* Two triangles using barycentric interpolation on predetermined vertex colors.
 * Fragment shader: fragmentShader_perVertexColor.glsl
 * Vertex shader:   vertexShader_perVertexColor.glsl
 * Aspect ratio: 1.5
 * Coords:
 * float left = -7.5f;
 * float right = 7.5f;
 * float bottom = -4.2f;
 * float top = 4.2f;
 * float near = -10.0f;
 * float far = 10.0f;
*/
vector<float> TwoTriangles{
  -3.0f,// vertex 0
  3.0f,
  0.0f,
  1.0f,// vertex 0 color
  0.0f,
  0.0f,
  -6.0f,// vertex 1
  -3.0f,
  0.0f,
  0.0f,// vertex 1 color
  1.0f,
  0.0f,
  0.0f,// vertex 2
  -3.0f,
  0.0f,
  0.0f,// vertex 2 color
  0.0f,
  1.0f,
  1.5f,// triangle 2 vertex 0
  0.0f,
  0.0f,
  0.514f,// vertex 0 color
  0.310f,
  0.149f,
  3.0f,// vertex 1
  -3.0f,
  0.0f,
  0.149f,// vertex 1 color
  0.514f,
  0.310f,
  4.5f,// vertex 2
  0.0f,
  0.0f,
  0.310f,// vertex 2 color
  0.149f,
  0.514f
};

/* The same as the above, but using the half-space mapping on normals of the vertices. These two
 * triangles all have normals facing the camera, so they just come out a solid yellow color. 
 * Fragment shader: fragmentShader_perVertexColor.glsl
 * Vertex shader:   vertexShader_perVertexNormalShading.glsl
 * Aspect ratio: 1.5
 * Coords:
 * float left = -7.5f;
 * float right = 7.5f;
 * float bottom = -4.2f;
 * float top = 4.2f;
 * float near = -10.0f;
 * float far = 10.0f;
*/
vector<float> TwoOrthogonalTriangles{
  -3.0f,// vertex 0
  3.0f,
  0.0f,
  0.0f,// vertex 0 normal
  0.0f,
  -1.0f,
  -6.0f,// vertex 1
  -3.0f,
  0.0f,
  0.0f,// vertex 1 normal
  0.0f,
  -1.0f,
  0.0f,// vertex 2
  -3.0f,
  0.0f,
  0.0f,// vertex 2 normal
  0.0f,
  -1.0f,
  1.5f,// triangle 2 vertex 0
  0.0f,
  0.0f,
  0.0f,// vertex 0 normal
  0.0f,
  -1.0f,
  3.0f,// vertex 1
  -3.0f,
  0.0f,
  0.0f,// vertex 1 normal
  0.0f,
  -1.0f,
  4.5f,// vertex 2
  0.0f,
  0.0f,
  0.0f,// vertex 2 normal
  0.0f,
  -1.0f,
};

/* Two triangles that are non-orthographic to the camera, with simple normals.
 * Fragment shader: fragmentShader_perVertexColor.glsl
 * Vertex shader:   vertexShader_perVertexNormalShading.glsl
 * Aspect ratio: 1.5
 * Coords:
 * float left = -7.5f;
 * float right = 7.5f;
 * float bottom = -4.2f;
 * float top = 4.2f;
 * float near = -10.0f;
 * float far = 10.0f;
*/
vector<float> TwoAngledTriangles{
  -3.0f,// vertex 0
  3.0f,
  -9.0f,
  -0.577f,// vertex 0 normal
  -0.577f,
  -0.577f,
  -6.0f,// vertex 1
  -3.0f,
  0.0f,
  -0.707f,// vertex 1 normal
  0.0f,
  -0.707f,
  0.0f,// vertex 2
  -3.0f,
  9.0f,
  0.0f,// vertex 2 normal
  -0.707f,
  -0.707f,
  1.5f,// triangle 2 vertex 0
  0.0f,
  9.0f,
  0.577f,// vertex 0 normal
  0.577f,
  -0.577f,
  3.0f,// vertex 1
  -3.0f,
  0.0f,
  0.707f,// vertex 1 normal
  0.0f,
  -0.707f,
  4.5f,// vertex 2
  0.0f,
  -9.0f,
  0.0f,// vertex 2 normal
  0.707f,
  -0.707f,
};

/* A mesh-like scene in which triangles meet at their vertices. Technically, the normals are lies,
 * since this mesh is actually flat, but it's helpful for testing.
 * If an OBJ file is a LEGO kit, this is Mega Bloks.
 * Reference: https://i.imgur.com/VVPl0nw.png
 * Fragment shader: fragmentShader_perVertexColor.glsl
 * Vertex shader:   vertexShader_perVertexNormalShading.glsl
 * Aspect ratio: 1.0
 * Coords:
 * float left = -7.0f;
 * float right = 7.0f;
 * float bottom = -7.0f;
 * float top = 7.0f;
 * float near = -10.0f;
 * float far = 10.0f;
*/
vector<float> FlatMiniMesh()
{
  auto vertices = map<char, vector<float>>();
  vertices.emplace('a', vector<float>{ -3.0f, 3.0f, 0.0f, -0.707f, 0.707f, 0.0f });
  vertices.emplace('b', vector<float>{ 0.0f, 3.0f, 0.0f, 0.0f, 1.0f, 0.0f });
  vertices.emplace('c', vector<float>{ 3.0f, 3.0f, 0.0f, 0.707f, 0.707f, 0.0f });
  vertices.emplace('d', vector<float>{ -3.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f });
  vertices.emplace('e', vector<float>{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f });
  vertices.emplace('f', vector<float>{ 3.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f });
  vertices.emplace('g', vector<float>{ -3.0f, -3.0f, 0.0f, -0.707f, -0.707f, 0.0f });
  vertices.emplace('h', vector<float>{ 0.0f, -3.0f, 0.0f, 0.0f, -1.0f, 0.0f });
  vertices.emplace('i', vector<float>{ 3.0f, -3.0f, 0.0f, 0.707f, -0.707f, 0.0f });
  vertices.emplace('j', vector<float>{ -6.0f, 0.0f, 0.0f, 0.707f, 0.0f, -0.707f });
  vertices.emplace('k', vector<float>{ 6.0f, 0.0f, 0.0f, -0.707f, 0.0f, -0.707f });
  vertices.emplace('l', vector<float>{ 0.0f, 6.0f, 0.0f, 0.0f, -0.707f, -0.707f });
  vertices.emplace('m', vector<float>{ 0.0f, -6.0f, 0.0f, 0.0f, 0.707f, -0.707f });

  auto flatMiniMesh = vector<float>();

  flatMiniMesh.insert(flatMiniMesh.end(), vertices['e'].begin(), vertices['e'].end());
  flatMiniMesh.insert(flatMiniMesh.end(), vertices['b'].begin(), vertices['b'].end());
  flatMiniMesh.insert(flatMiniMesh.end(), vertices['c'].begin(), vertices['c'].end());

  flatMiniMesh.insert(flatMiniMesh.end(), vertices['e'].begin(), vertices['e'].end());
  flatMiniMesh.insert(flatMiniMesh.end(), vertices['f'].begin(), vertices['f'].end());
  flatMiniMesh.insert(flatMiniMesh.end(), vertices['c'].begin(), vertices['c'].end());

  flatMiniMesh.insert(flatMiniMesh.end(), vertices['e'].begin(), vertices['e'].end());
  flatMiniMesh.insert(flatMiniMesh.end(), vertices['f'].begin(), vertices['f'].end());
  flatMiniMesh.insert(flatMiniMesh.end(), vertices['i'].begin(), vertices['i'].end());

  flatMiniMesh.insert(flatMiniMesh.end(), vertices['e'].begin(), vertices['e'].end());
  flatMiniMesh.insert(flatMiniMesh.end(), vertices['h'].begin(), vertices['h'].end());
  flatMiniMesh.insert(flatMiniMesh.end(), vertices['i'].begin(), vertices['i'].end());

  flatMiniMesh.insert(flatMiniMesh.end(), vertices['e'].begin(), vertices['e'].end());
  flatMiniMesh.insert(flatMiniMesh.end(), vertices['h'].begin(), vertices['h'].end());
  flatMiniMesh.insert(flatMiniMesh.end(), vertices['g'].begin(), vertices['g'].end());

  flatMiniMesh.insert(flatMiniMesh.end(), vertices['e'].begin(), vertices['e'].end());
  flatMiniMesh.insert(flatMiniMesh.end(), vertices['d'].begin(), vertices['d'].end());
  flatMiniMesh.insert(flatMiniMesh.end(), vertices['g'].begin(), vertices['g'].end());

  flatMiniMesh.insert(flatMiniMesh.end(), vertices['e'].begin(), vertices['e'].end());
  flatMiniMesh.insert(flatMiniMesh.end(), vertices['d'].begin(), vertices['d'].end());
  flatMiniMesh.insert(flatMiniMesh.end(), vertices['a'].begin(), vertices['a'].end());

  flatMiniMesh.insert(flatMiniMesh.end(), vertices['e'].begin(), vertices['e'].end());
  flatMiniMesh.insert(flatMiniMesh.end(), vertices['b'].begin(), vertices['b'].end());
  flatMiniMesh.insert(flatMiniMesh.end(), vertices['a'].begin(), vertices['a'].end());

  flatMiniMesh.insert(flatMiniMesh.end(), vertices['a'].begin(), vertices['a'].end());
  flatMiniMesh.insert(flatMiniMesh.end(), vertices['d'].begin(), vertices['d'].end());
  flatMiniMesh.insert(flatMiniMesh.end(), vertices['j'].begin(), vertices['j'].end());

  flatMiniMesh.insert(flatMiniMesh.end(), vertices['g'].begin(), vertices['g'].end());
  flatMiniMesh.insert(flatMiniMesh.end(), vertices['d'].begin(), vertices['d'].end());
  flatMiniMesh.insert(flatMiniMesh.end(), vertices['j'].begin(), vertices['j'].end());

  flatMiniMesh.insert(flatMiniMesh.end(), vertices['c'].begin(), vertices['c'].end());
  flatMiniMesh.insert(flatMiniMesh.end(), vertices['f'].begin(), vertices['f'].end());
  flatMiniMesh.insert(flatMiniMesh.end(), vertices['k'].begin(), vertices['k'].end());

  flatMiniMesh.insert(flatMiniMesh.end(), vertices['i'].begin(), vertices['i'].end());
  flatMiniMesh.insert(flatMiniMesh.end(), vertices['f'].begin(), vertices['f'].end());
  flatMiniMesh.insert(flatMiniMesh.end(), vertices['k'].begin(), vertices['k'].end());

  flatMiniMesh.insert(flatMiniMesh.end(), vertices['a'].begin(), vertices['a'].end());
  flatMiniMesh.insert(flatMiniMesh.end(), vertices['b'].begin(), vertices['b'].end());
  flatMiniMesh.insert(flatMiniMesh.end(), vertices['l'].begin(), vertices['l'].end());

  flatMiniMesh.insert(flatMiniMesh.end(), vertices['c'].begin(), vertices['c'].end());
  flatMiniMesh.insert(flatMiniMesh.end(), vertices['b'].begin(), vertices['b'].end());
  flatMiniMesh.insert(flatMiniMesh.end(), vertices['l'].begin(), vertices['l'].end());

  flatMiniMesh.insert(flatMiniMesh.end(), vertices['g'].begin(), vertices['g'].end());
  flatMiniMesh.insert(flatMiniMesh.end(), vertices['h'].begin(), vertices['h'].end());
  flatMiniMesh.insert(flatMiniMesh.end(), vertices['m'].begin(), vertices['m'].end());

  flatMiniMesh.insert(flatMiniMesh.end(), vertices['i'].begin(), vertices['i'].end());
  flatMiniMesh.insert(flatMiniMesh.end(), vertices['h'].begin(), vertices['h'].end());
  flatMiniMesh.insert(flatMiniMesh.end(), vertices['m'].begin(), vertices['m'].end());

  return flatMiniMesh;
}

/* The same as above, but with varying z values on each vertex. Doesn't seem to look any different,
 * but kept for testing purposes.
 * Fragment shader: fragmentShader_perVertexColor.glsl
 * Vertex shader:   vertexShader_perVertexNormalShading.glsl
 * Aspect ratio: 1.0
 * Coords:
 * float left = -7.0f;
 * float right = 7.0f;
 * float bottom = -7.0f;
 * float top = 7.0f;
 * float near = -10.0f;
 * float far = 10.0f;
*/
vector<float> MiniMesh()
{
  auto vertices = map<char, vector<float>>();
  vertices.emplace('a', vector<float>{ -3.0f, 3.0f, 0.0f, -0.707f, 0.707f, 0.0f });
  vertices.emplace('b', vector<float>{ 0.0f, 3.0f, -9.0f, 0.0f, 1.0f, 0.0f });
  vertices.emplace('c', vector<float>{ 3.0f, 3.0f, 0.0f, 0.707f, 0.707f, 0.0f });
  vertices.emplace('d', vector<float>{ -3.0f, 0.0f, -9.0f, -1.0f, 0.0f, 0.0f });
  vertices.emplace('e', vector<float>{ 0.0f, 0.0f, 9.0f, 0.0f, 0.0f, -1.0f });
  vertices.emplace('f', vector<float>{ 3.0f, 0.0f, -9.0f, 1.0f, 0.0f, 0.0f });
  vertices.emplace('g', vector<float>{ -3.0f, -3.0f, 0.0f, -0.707f, -0.707f, 0.0f });
  vertices.emplace('h', vector<float>{ 0.0f, -3.0f, -9.0f, 0.0f, -1.0f, 0.0f });
  vertices.emplace('i', vector<float>{ 3.0f, -3.0f, 0.0f, 0.707f, -0.707f, 0.0f });
  vertices.emplace('j', vector<float>{ -6.0f, 0.0f, 9.0f, 0.707f, 0.0f, -0.707f });
  vertices.emplace('k', vector<float>{ 6.0f, 0.0f, 9.0f, -0.707f, 0.0f, -0.707f });
  vertices.emplace('l', vector<float>{ 0.0f, 6.0f, 9.0f, 0.0f, -0.707f, -0.707f });
  vertices.emplace('m', vector<float>{ 0.0f, -6.0f, 9.0f, 0.0f, 0.707f, -0.707f });

  auto miniMesh = vector<float>();

  miniMesh.insert(miniMesh.end(), vertices['e'].begin(), vertices['e'].end());
  miniMesh.insert(miniMesh.end(), vertices['b'].begin(), vertices['b'].end());
  miniMesh.insert(miniMesh.end(), vertices['c'].begin(), vertices['c'].end());

  miniMesh.insert(miniMesh.end(), vertices['e'].begin(), vertices['e'].end());
  miniMesh.insert(miniMesh.end(), vertices['f'].begin(), vertices['f'].end());
  miniMesh.insert(miniMesh.end(), vertices['c'].begin(), vertices['c'].end());

  miniMesh.insert(miniMesh.end(), vertices['e'].begin(), vertices['e'].end());
  miniMesh.insert(miniMesh.end(), vertices['f'].begin(), vertices['f'].end());
  miniMesh.insert(miniMesh.end(), vertices['i'].begin(), vertices['i'].end());

  miniMesh.insert(miniMesh.end(), vertices['e'].begin(), vertices['e'].end());
  miniMesh.insert(miniMesh.end(), vertices['h'].begin(), vertices['h'].end());
  miniMesh.insert(miniMesh.end(), vertices['i'].begin(), vertices['i'].end());

  miniMesh.insert(miniMesh.end(), vertices['e'].begin(), vertices['e'].end());
  miniMesh.insert(miniMesh.end(), vertices['h'].begin(), vertices['h'].end());
  miniMesh.insert(miniMesh.end(), vertices['g'].begin(), vertices['g'].end());

  miniMesh.insert(miniMesh.end(), vertices['e'].begin(), vertices['e'].end());
  miniMesh.insert(miniMesh.end(), vertices['d'].begin(), vertices['d'].end());
  miniMesh.insert(miniMesh.end(), vertices['g'].begin(), vertices['g'].end());

  miniMesh.insert(miniMesh.end(), vertices['e'].begin(), vertices['e'].end());
  miniMesh.insert(miniMesh.end(), vertices['d'].begin(), vertices['d'].end());
  miniMesh.insert(miniMesh.end(), vertices['a'].begin(), vertices['a'].end());

  miniMesh.insert(miniMesh.end(), vertices['e'].begin(), vertices['e'].end());
  miniMesh.insert(miniMesh.end(), vertices['b'].begin(), vertices['b'].end());
  miniMesh.insert(miniMesh.end(), vertices['a'].begin(), vertices['a'].end());

  miniMesh.insert(miniMesh.end(), vertices['a'].begin(), vertices['a'].end());
  miniMesh.insert(miniMesh.end(), vertices['d'].begin(), vertices['d'].end());
  miniMesh.insert(miniMesh.end(), vertices['j'].begin(), vertices['j'].end());

  miniMesh.insert(miniMesh.end(), vertices['g'].begin(), vertices['g'].end());
  miniMesh.insert(miniMesh.end(), vertices['d'].begin(), vertices['d'].end());
  miniMesh.insert(miniMesh.end(), vertices['j'].begin(), vertices['j'].end());

  miniMesh.insert(miniMesh.end(), vertices['c'].begin(), vertices['c'].end());
  miniMesh.insert(miniMesh.end(), vertices['f'].begin(), vertices['f'].end());
  miniMesh.insert(miniMesh.end(), vertices['k'].begin(), vertices['k'].end());

  miniMesh.insert(miniMesh.end(), vertices['i'].begin(), vertices['i'].end());
  miniMesh.insert(miniMesh.end(), vertices['f'].begin(), vertices['f'].end());
  miniMesh.insert(miniMesh.end(), vertices['k'].begin(), vertices['k'].end());

  miniMesh.insert(miniMesh.end(), vertices['a'].begin(), vertices['a'].end());
  miniMesh.insert(miniMesh.end(), vertices['b'].begin(), vertices['b'].end());
  miniMesh.insert(miniMesh.end(), vertices['l'].begin(), vertices['l'].end());

  miniMesh.insert(miniMesh.end(), vertices['c'].begin(), vertices['c'].end());
  miniMesh.insert(miniMesh.end(), vertices['b'].begin(), vertices['b'].end());
  miniMesh.insert(miniMesh.end(), vertices['l'].begin(), vertices['l'].end());

  miniMesh.insert(miniMesh.end(), vertices['g'].begin(), vertices['g'].end());
  miniMesh.insert(miniMesh.end(), vertices['h'].begin(), vertices['h'].end());
  miniMesh.insert(miniMesh.end(), vertices['m'].begin(), vertices['m'].end());

  miniMesh.insert(miniMesh.end(), vertices['i'].begin(), vertices['i'].end());
  miniMesh.insert(miniMesh.end(), vertices['h'].begin(), vertices['h'].end());
  miniMesh.insert(miniMesh.end(), vertices['m'].begin(), vertices['m'].end());

  return miniMesh;
}

/* A single triangle in the center of the space, used for Lambertian tests.
 * Note that the light position is hard coded in the shader and needs to be changed there.
 * Fragment shader: fragmentShader_perVertexColor.glsl
 * Vertex shader:   vertexShader_perVertexLambertianShader.glsl
 * Aspect ratio: 1.0
 * Coords:
 * float left = -7.0f;
 * float right = 7.0f;
 * float bottom = -7.0f;
 * float top = 7.0f;
 * float near = -10.0f;
 * float far = 10.0f;
*/
vector<float> CentralTriangle{
  0.0f,// vertex 0
  3.9f,
  0.0f,
  1.0f,// vertex 0 color
  0.0f,
  0.0f,
  0.0f,// vertex 0 normal
  0.0f,
  -1.0f,
  -4.5,// vertex 1
  -3.9f,
  0.0f,
  0.0f,// vertex 1 color
  1.0f,
  0.0f,
  0.0f,// vertex 1 normal
  0.0f,
  -1.0f,
  4.5,// vertex 2
  -3.9f,
  0.0f,
  0.0f,// vertex 2 color
  0.0f,
  1.0f,
  0.0f,// vertex 2 normal
  0.0f,
  -1.0f
};