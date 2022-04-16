#version 330 core

layout(location=0) in vec3 in_Position;
layout(location=2) in vec3 in_Normal;   // the normal is now in attribute 2

out vec3 vColor;

uniform mat4 projMatrix;
uniform mat4 modelMatrix;

void main(void)
{
  mat4 viewMatrix;
  viewMatrix[0] = vec4( 1.0, 0.0, 0.0, 0.0 );
  viewMatrix[1] = vec4( 0.0, 1.0, 0.0, 0.0 );
  viewMatrix[2] = vec4( 0.0, 0.0, 1.0, 0.0 );
  viewMatrix[3] = vec4( 0.0, 0.0, 0.0, 1.0 );

  //update normal for rotation
  vec3 normal = normalize(in_Normal * transpose(inverse(mat3(modelMatrix))));

  vec3 offset = vec3( 1.0, 1.0, 1.0);
  vColor = (normal + offset) * 0.5;
  gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0);
}