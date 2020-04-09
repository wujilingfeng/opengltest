#version 450 core
out vec4 fColor;
in vec4 outColor;
in vec2 texcoord;
in float e_id;

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
void set_fColor(vec2 uv,vec2 coord_uv)
{
	float a=length(texcoord);
	a=sign(a);
	fColor=(texture(ourTexture,texcoord)*a+(1-a)*outColor);
	
	float is_pick=step(abs(coord_uv.x-uv.x),6/(2*iResolution.x));
	is_pick=step(2,is_pick+step(abs(coord_uv.y-uv.y),6/(2*iResolution.y)));
	is_pick=step(2,is_pick+p_intera.is_pick);
	fColor=(1-is_pick)*fColor+is_pick*vec4(trans_code(e_id)/255.0,0.5);
}

void main()
{
	vec2 uv=gl_FragCoord.xy/iResolution.xy;
	vec2 coord_uv=iMouse.xy/iResolution.xy;
	coord_uv.y=1-coord_uv.y;
	set_fColor(uv,coord_uv);
	
	//fColor=vec4(outColor,1.0);   
}
