#version 450 core
out vec4 fColor;

uniform vec2 iResolution;
uniform sampler2D Faces_Vertices;
uniform sampler2D Faces_Index;
uniform sampler2D Face_colors;
uniform sampler2D ourTexture;
uniform float Faces_len;
uniform float Faces_Vertices_rows;
uniform float iTime;
uniform vec2 iMouse;
uniform mat4 Proj;
uniform mat4 Camera_Matrix;
struct Ambientlight{
    float intensity;
    vec3 color;
};
struct shoot_information
{
	float distance;
	float face_id;
	

};
shoot_information s_info;
Ambientlight ambientlight;
//uniform Ambient_light ambient_light;
float det(mat3 m)
{
	float sum=0;
	sum+=m[0][0]*m[1][1]*m[2][2];
	sum+=m[0][1]*m[1][2]*m[2][0];
	sum+=m[0][2]*m[1][0]*m[2][1];
	sum-=m[2][0]*m[1][1]*m[0][2];
	sum-=m[2][1]*m[1][2]*m[0][0];
	sum-=m[2][2]*m[1][0]*m[0][1];
	return sum;
}
mat3 inverse(mat3 m)
{
   mat3 re,re1;
   re[0][0]=m[1][1]*m[2][2]-m[2][1]*m[1][2];
   re[1][0]=-m[0][1]*m[2][2]+m[2][1]*m[0][2];
   re[2][0]=m[0][1]*m[1][2]-m[1][1]*m[0][2];
   re[0][1]=-m[1][0]*m[2][2]+m[1][2]*m[2][0];
   re[1][1]=m[0][0]*m[2][2]-m[2][0]*m[0][2];
   re[2][1]=-m[0][0]*m[1][2]+m[1][0]*m[0][2];
   re[0][2]=m[1][0]*m[2][1]-m[2][0]*m[1][1];
   re[1][2]=-m[0][0]*m[2][1]+m[2][0]*m[0][1];
   re[2][2]=m[0][0]*m[1][1]-m[1][0]*m[0][1];
   for(int i=0;i<3;i++)
   {
        for(int j=0;j<3;j++)
        {
            re1[i][j]=re[j][i];
    
        }
   }
   float temp=det(m);
   return re1/temp;

}

float from_Faces_Index_get_value(float temp_i)
{
	float x=mod(temp_i,1000);
	float y=floor(temp_i/1000.0);
	return texture(Faces_Index,vec2(x/1000.0,y/(floor(Faces_len/1000.0)+1))).x;
}
vec3 from_Faces_Vertices_get_value(float temp_i)
{
	float x=mod(temp_i,1000);
	float y=floor(temp_i/1000.0);
 	return texture(Faces_Vertices,vec2(x/1000.0,y/(floor(Faces_Vertices_rows/1000.0)+1))).xyz;
}
void set_fColor(float te)
{

	//vec2 uv=gl_FragCoord.xy/iResolution.xy;
	//uv=2.0*(uv-0.5);
    //float near=-1.0/(1.0/Proj[3][2]+Proj[2][2]/Proj[3][2]);
	//float halfh=near/Proj[1][1],halfw=near/Proj[0][0];
//	s_info.face_id=s_info.face_id+1.5;
    //mat3 m,m_inverse;
    //m[0][0]=1;m[1][0]=0;m[2][0]=3;
    //m[0][1]=1;m[1][1]=-5;m[2][1]=6;
    //m[0][2]=11;m[1][2]=0;m[2][2]=9;
	//m_inverse=inverse(m);
	//if(uv.x>0.5&&uv.y>0.5)
	//{   
        //fColor=vec4(1.0,0.0,0.0,1.0); 
    	//}
	//else
	//{
	//    float x=texture(Faces_Index,vec2(48.0/1000.0,0.0)).x;
	//fColor=vec4(from_Faces_Vertices_get_value(5),1.0);
	//    fColor=vec4(s_info.face_id,from_Faces_Index_get_value(48)/255.0,te/255.0,1.0);	
	//}
	fColor=vec4(te/255.0,s_info.face_id+1,s_info.face_id+1,1.0);
	
}
float chuli_coord(vec3 coord)
{
	float state=step(2,step(2,step(0,coord.x)+step(0,coord.y))+step(0,-coord.z));
	state=step(2,state+step(coord.x+coord.y,1));
	state=step(2,state+step(-coord.z,s_info.distance));
	return state;
//s_info.distance=state*(-coord.z)+(1-state)*s_info.distance;

}
vec3 get_affine_coord(vec3 a,vec3 b,vec3 c,vec3 origin,vec3 e3)
{
    mat3 m;vec3 b1;
    vec3 e1=b-a;
    vec3 e2=c-a;
    vec3 temp1=origin-a;
    
    m[0][0]=dot(e1,e1);
    m[1][0]=dot(e2,e1);
    m[2][0]=dot(e3,e1);
    m[1][1]=dot(e2,e2);
    m[2][1]=dot(e3,e2);
    m[2][2]=dot(e3,e3);
    m[0][1]=m[1][0];
    m[0][2]=m[2][0];
    m[1][2]=m[2][1];
    b1[0]=dot(temp1,e1);
    b1[1]=dot(temp1,e2);
    b1[2]=dot(temp1,e3);
    
	return inverse(m)*b1;
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
	int temp_num=0;
	while(num>=1)
	{
		for(int i=0;i<num-2;i++)
		{
         	  	vec3 a=from_Faces_Vertices_get_value(from_Faces_Index_get_value(temp_i+1));
           	 	vec3 b=from_Faces_Vertices_get_value(from_Faces_Index_get_value(temp_i+1+i+1));
           	 	vec3 c=from_Faces_Vertices_get_value(from_Faces_Index_get_value(temp_i+1+i+2));
			vec4 a1=Camera_Matrix*vec4(a,1);
			vec4 b1=Camera_Matrix*vec4(b,1);
			vec4 c1=Camera_Matrix*vec4(c,1);
           	 	vec3 coord=get_affine_coord(a1.xyz,b1.xyz,c1.xyz,origin,dir);
			float state=chuli_coord(coord);
			s_info.distance=state*(-coord.z)+(1-state)*s_info.distance;
			s_info.face_id=state*(temp_num)+(1-state)*s_info.face_id;
		}		
		temp_i=temp_i+num+1;
		num=from_Faces_Index_get_value(temp_i);
		temp_num++;
	}
	
	set_fColor(step(0.2,0.3));
}
void init()
{
	s_info.distance=10000;
	s_info.face_id=-1;
	ambientlight.color=vec3(0.2,0.3,0.3);
	ambientlight.intensity=0.5;

}	
void main()
{
	init();
	vec3 dir;
	get_origin_radial(dir);
   	shoot(vec3(0,0,0),dir);
}
//float near=-1.0/(1.0/Proj[3][2]+Proj[2][2]/Proj[3][2]);
//float far=1.0/(1.0/Proj[3][2]-Proj[2][2]/Proj[3][2]);
//h=2*near/Proj[1][1]
//w=2*near*/Proj[0][0]
