#version 330 core

layout(location=0) out vec4 fragmentColor;
in vec3 vColor;

void main(void)
{
  fragmentColor = vec4(vColor, 1.0);
}