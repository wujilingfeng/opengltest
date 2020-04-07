#version 330 core
layout (location = 0) in vec3 aPos;
uniform mat4 Proj;
uniform mat4 Object_Matrix;

void main()
{
	gl_Position = Proj*Object_Matrix*vec4(aPos, 1.0);
}
