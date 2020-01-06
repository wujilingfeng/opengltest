#version 450 core
layout( location = 0 ) in vec3 vPosition;
layout(location=1) in vec3 aColor;
layout(location=2) in vec2 aTexCoord;
layout(location=3) in vec3 nor;
layout(location=4) in float vertices_id;
uniform mat4 Proj;
//camera_matrix_inverse
uniform mat4 Camera_Matrix;
void main()
{ 

	gl_Position =Proj*vec4(vPosition,1);
	
}
