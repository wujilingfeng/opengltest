#version 450 core
layout( location = 0 ) in vec3 vPosition;
layout(location=1) in vec3 aColor;
layout(location=2) in vec2 aTexCoord;
layout(location=3) in vec3 nor;
layout(location=4) in float element_id;
out vec3 outColor;
out vec2 texcoord;
out float e_id;
uniform mat4 Proj;

//camera_matrix_inverse
uniform mat4 Camera_Matrix;
uniform mat4 Object_Matrix;
//gl_Pointsize
void set_color()
{
	float st=step(length(nor),0);

	vec3 temp_nor=normalize(nor);
	temp_nor=(Camera_Matrix*vec4(temp_nor,0.0)).xyz;
	vec3 dir=normalize(vec3(0,0,1));
	outColor=st*aColor+(1-st)*max(-dot(temp_nor,dir),0)*aColor;

}
void main()
{ 
	gl_PointSize=10.0f;
	texcoord=aTexCoord;
	set_color();	
//outColor=aColor;
	gl_Position =Proj*Camera_Matrix*Object_Matrix*vec4(vPosition,1);
	e_id=element_id;
	
	
}
