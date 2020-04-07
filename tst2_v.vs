#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
uniform mat4 Proj;
uniform mat4 Object_Matrix;

//projection * view * model

void main()
{
	gl_Position =  Proj*Object_Matrix* vec4(aPos, 1.0f);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}
