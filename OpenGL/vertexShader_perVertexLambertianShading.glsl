#version 330 core

layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Color;   // the color is now in attribute 1
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
  
 // hardcoded light position
  vec3 light = vec3( 0, 0, -10); // straight out from center
  //vec3 light = vec3( 10, 0, 0); // far to the right
  //vec3 light = vec3( 0, 0, -0.1); // juuuuust above the center
  //vec3 light = vec3( -4.5, -3.9, -10); // straight out from bottom left vertex
  //vec3 light = vec3( 0, 0, -1); // a bit further above the center
  vec3 lightDir = normalize(light - in_Position);

  float lambert = dot(normalize(in_Normal), lightDir);
  vColor = in_Color * lambert;
  gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0);
}