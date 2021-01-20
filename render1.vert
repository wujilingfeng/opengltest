#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;


uniform mat4 Proj;

//camera_matrix_inverse
uniform mat4 Camera_Matrix;
uniform mat4 Object_Matrix;

void main()
{
    TexCoords = aTexCoords;    
    gl_Position = Proj*Camera_Matrix*Object_Matrix*vec4(aPos, 1.0);
}