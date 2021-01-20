#version 450 core 
out vec4 fColor;
in vec4 outColor;
in vec2 texcoord;
in float e_id;
in vec3 norf;
in vec3 dirf;
in float f_i_marked1;
in float f_i_marked2;
uniform vec2 iResolution;

uniform sampler2D ourTexture;
uniform sampler2D Faces_Vertices;
uniform sampler2D Face_colors;
uniform sampler2D Faces_Index;

struct Pickup_intera{
	float is_pick;
};
uniform Pickup_intera p_intera;
uniform vec2 iMouse;
vec3 trans_code(float a)
{
    //a=a*10000;
    vec3 re;
    re.z=mod(a,255);
    re.y=mod(floor(a/255),255);
    re.x=mod(floor(a/(255*255)),255);
    return re;
}
vec3  chuli_f_i_marked()
{
    float lambda1=-(f_i_marked1-2)*3.0/2.0+(f_i_marked2-4)/2.0;
    float lambda2=(f_i_marked1-2)*2-(f_i_marked2-4);
    vec3 re;
    re.x=lambda1;re.y=lambda2;re.z=1-lambda1-lambda2;
    return re; 

}
void set_fColor(vec2 uv,vec2 coord_uv)
{
	//float st=step(length(norf),0);
	//vec4 temp_color=st*outColor+(1-st)*max(-dot(norf,dirf),0)*outColor;
	float a=length(texcoord);
	a=sign(a);
	vec4 temp_color1=max(-dot(norf,dirf),0)*texture(ourTexture,texcoord);
	vec4 temp_fColor=temp_color1*a+(1-a)*outColor;
	//float is_pick=step(abs(coord_uv.x-uv.x),6/(2*iResolution.x));
	//is_pick=step(2,is_pick+step(abs(coord_uv.y-uv.y),6/(2*iResolution.y)));
	//is_pick=step(2,is_pick+p_intera.is_pick);
    //float is_pick1=step(abs(coord_uv.x-uv.x),4/(2*iResolution.x));
    //is_pick1=step(2,is_pick1+step(abs(coord_uv.y-uv.y),4/(2*iResolution.y)));

	//fColor=(1-is_pick)*temp_fColor+is_pick*((is_pick1)*vec4(trans_code(e_id)/255.0,1)+(1-is_pick1)*vec4(chuli_f_i_marked(),1));
	fColor=(1-p_intera.is_pick)*temp_fColor+p_intera.is_pick*vec4(trans_code(e_id)/255.0,1);
	
	//fColor=vec4(e_id/255.0,0,0,1);
}

void main()
{
	vec2 uv=gl_FragCoord.xy/iResolution.xy;
	vec2 coord_uv=iMouse.xy/iResolution.xy;
	coord_uv.y=1-coord_uv.y;
	set_fColor(uv,coord_uv);
	
	//fColor=vec4(outColor,1.0);   
}
//0 1 2 -> 0
// 0 2 1 -> 1
// 1 0 2 -> 2
// 1 2 0 -> 3
//2 0 1-> 4
//2 1 0 -> 5
