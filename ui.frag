#version 450 core
out vec4 fColor;
in vec4 outColor;
in vec2 texcoord;
in float e_id;
in float f_i_marked1;
in float f_i_marked2;
uniform sampler2D ourTexture;
uniform float is_text;

struct Pickup_intera{
    float is_pick;
};

uniform Pickup_intera p_intera;
vec3 trans_code(float a)
{

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
void main()
{
    float a=length(texcoord); 


    vec4 textc=vec4(outColor.xyz,texture(ourTexture,texcoord).r);
    vec4 rectc=texture(ourTexture,texcoord);
    vec4 texc=textc*is_text+(1-is_text)*rectc;
    a=sign(a);
    vec4 temp_fColor=texc*a+(1-a)*outColor;
    fColor=(1-p_intera.is_pick)*temp_fColor;
    //fColor=textc;
    
}
