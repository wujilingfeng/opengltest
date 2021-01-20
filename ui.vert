#version 450 core
layout (location = 0) in vec3 vPosition;

layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout(location=3) in float element_id;
layout(location=4) in float face_index_marked;

uniform mat4 Object_Matrix;
uniform mat4 Proj;
out vec4 outColor;
out vec2 texcoord;
out float e_id;
out float f_i_marked1;
out float f_i_marked2;

void main()
{
    gl_Position=  Proj*Object_Matrix*vec4(vPosition.xyz,1.0);
    outColor=aColor;
    texcoord=aTexCoord;
    f_i_marked1=face_index_marked;
    f_i_marked2=face_index_marked*face_index_marked;
}