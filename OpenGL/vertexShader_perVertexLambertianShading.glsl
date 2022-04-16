#version 330 core

layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Color;   // the color is now in attribute 1
layout(location=2) in vec3 in_Normal;   // the normal is now in attribute 2

out vec3 vColor;

uniform mat4 projMatrix;
uniform mat4 modelMatrix;
uniform vec3 light;

void main(void)
{
  mat4 viewMatrix;
  viewMatrix[0] = vec4( 1.0, 0.0, 0.0, 0.0 );
  viewMatrix[1] = vec4( 0.0, 1.0, 0.0, 0.0 );
  viewMatrix[2] = vec4( 0.0, 0.0, 1.0, 0.0 );
  viewMatrix[3] = vec4( 0.0, 0.0, 0.0, 1.0 );
  
  //update normal for rotation
  vec3 normal = normalize(in_Normal * transpose(inverse(mat3(modelMatrix))));

  vec3 lightDir = normalize(light - in_Position);

  float lambert = dot(normalize(normal), lightDir);
  vColor = in_Color * lambert;
  gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0);
}