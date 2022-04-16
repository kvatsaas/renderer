#version 330 core

layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Color;

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

  vColor = in_Color;
  gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0);
}