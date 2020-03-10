#version 330 core

layout (location=0) in vec3 aPos;

uniform mat4 model;
uniform mat4 projection;

out mat4 projMat;

void main()
{
 projMat=projection;
 gl_Position = vec4(aPos.x, aPos.y, 0.f, 1.f);
}