#version 450 core

layout( location = 0 ) in vec3 vPosition;
layout(location=1) in vec3 aColor;
layout(location=2) in vec2 aTexCoord;
uniform mat4 Proj;
uniform mat4 Matrix;
out vec3 ourColor;
out vec2 TexCoord;
void main()
{ //vPosition[3]=1.0f;
//vPosition[2]=0.5f;
    gl_Position =vec4(vPosition,1.0f)*Matrix*Proj;
    ourColor=aColor;
    TexCoord=aTexCoord;
}
