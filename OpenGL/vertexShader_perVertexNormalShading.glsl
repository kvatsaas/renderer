#version 330 core

layout(location=0) in vec3 in_Position;
layout(location=2) in vec3 in_Normal;   // the normal is now in attribute 2

out vec3 vColor;

uniform mat4 projMatrix;

void main(void)
{
  mat4 modelMatrix;
  modelMatrix[0] = vec4( 1.0, 0.0, 0.0, 0.0 );
  modelMatrix[1] = vec4( 0.0, 1.0, 0.0, 0.0 );
  modelMatrix[2] = vec4( 0.0, 0.0, 1.0, 0.0 );
  modelMatrix[3] = vec4( 0.0, 0.0, 0.0, 1.0 );

  mat4 viewMatrix;
  viewMatrix[0] = vec4( 1.0, 0.0, 0.0, 0.0 );
  viewMatrix[1] = vec4( 0.0, 1.0, 0.0, 0.0 );
  viewMatrix[2] = vec4( 0.0, 0.0, 1.0, 0.0 );
  viewMatrix[3] = vec4( 0.0, 0.0, 0.0, 1.0 );

  vec3 offset = vec3( 1.0, 1.0, 1.0);
  vColor = (normalize(in_Normal) + offset) * 0.5;
  gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0);
}