#version 450 core
layout (location = 0) in vec3 vPosition;

layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
uniform mat4 Object_Matrix;
out vec4 outColor;
out vec2 texcoord;

void main()
{
    gl_Position=   Object_Matrix*vec4(vPosition.xyz,1.0);
    outColor=aColor;
    texcoord=aTexCoord;
}