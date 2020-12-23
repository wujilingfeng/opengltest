#version 450 core
out vec4 fColor;
in vec4 outColor;
in vec2 texcoord;

uniform sampler2D ourTexture;
uniform float is_text;
void main()
{
    float a=length(texcoord); 

    vec4 textc=vec4(1.0,1.0,1.0,texture(ourTexture,texcoord).r)*vec4(outColor.xyz,1.0);
    vec4 rectc=texture(ourTexture,texcoord);
    vec4 texc=textc*is_text+(1-is_text)*rectc;
    a=sign(a);
    fColor=texc*a+(1-a)*outColor;
    //fColor=textc;
    
}
