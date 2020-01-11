#version 450 core
out vec4 fColor;

uniform vec2 iResolution;
uniform sampler2D ourTexture;
uniform sampler2D Faces_Vertices;
uniform sampler2D Faces_Index;
uniform sampler2D Face_colors;
uniform int Faces_rows;
uniform float iTime;
uniform vec2 iMouse;
uniform mat4 Proj;
uniform mat4 Camera_Matrix;
struct Ambientlight{
float intensity;
vec3 color;
};
Ambientlight ambientlight;
//uniform Ambient_light ambient_light;
float from_Faces_Index_get_value(float temp_i)
{
	float x=mod(temp_i,1000);
	float y=floor(temp_i/1000.0);
	return texture(Faces_Index,vec2(x,y)).x;
}
vec3 from_Faces_Vertices_get_value(float temp_i)
{
	float x=mod(temp_i,1000);
	float y=floor(temp_i/1000.0);
	
	return texture(Faces_Vertices,vec2(x,y)).xyz;
}
void set_fColor()
{

	//float a=length(texcoord);
	//a=sign(a);
	//fColor=(texture(ourTexture,texcoord)*a+(1-a)*vec4(outColor,1.0));
	vec2 uv=gl_FragCoord.xy/iResolution.xy;
	uv=2.0*(uv-0.5);
	if(uv.x>0.5&&uv.y>0.5)
	{fColor=vec4(1.0,0.0,0.0,1.0);}
	else
	{
	float x=texture(Faces_Index,vec2(0.0/1000.0,0.0)).x;
	fColor=vec4(x/255.0,0.0,0.0,1.0);	
	}
	
	
	//fColor=vec4(texture(Faces_Vertices,vec2(1.0/1000.0,0.0)).xyz/255.0,1.0);
}
void get_sanjiao_coord(vec3 a,vec3 b,vec3 c,out vec3 coord)
{

}
void get_origin_radial(out vec3 dir)
{
	vec2 uv=gl_FragCoord.xy/iResolution.xy;
	uv=2.0*(uv-0.5);
	float near=-1.0/(1.0/Proj[3][2]+Proj[2][2]/Proj[3][2]);
	float halfh=near/Proj[1][1],halfw=near/Proj[0][0];
	dir.x=halfw*uv.x;dir.y=halfh*uv.y;dir.z=near;
}
void shoot(vec3 origin,vec3 dir)
{
	float temp_i=0;
	float num=from_Faces_Index_get_value(temp_i);
	while(num>=1)
	{
		for(int i=0;i<num-2;i++)
		{
            from_Faces_Index_get_value(temp_i+1);
            from_Faces_Index_get_value(temp_i+1+i+1);
            from_Faces_Index_get_value(temp_i+1+i+2);
		
			//texture(Faces_Index,vec2())
		}		
		temp_i=temp_i+num+1;
		num=from_Faces_Index_get_value(temp_i);
	}

}
void init()
{
	ambientlight.color=vec3(0.2,0.3,0.3);
	ambientlight.intensity=0.5;

}	
void main()
{
	init();
	set_fColor();
	vec3 dir;
	get_origin_radial(dir);
	//fColor=vec4(outColor,1.0);   
}
//float near=-1.0/(1.0/Proj[3][2]+Proj[2][2]/Proj[3][2]);
	//float far=1.0/(1.0/Proj[3][2]-Proj[2][2]/Proj[3][2]);
//h=2*near/Proj[1][1]
//w=2*near*/Proj[0][0]
