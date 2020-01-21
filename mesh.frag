#version 450 core
out vec4 fColor;
in vec3 outColor;
in vec2 texcoord;
uniform vec2 iResolution;
uniform sampler2D Faces_Vertices;
uniform sampler2D Faces_Index;
uniform sampler2D ourTexture;

void set_fColor()
{
	float a=length(texcoord);
	a=sign(a);
	fColor=(texture(ourTexture,texcoord)*a+(1-a)*vec4(outColor,1.0));	
}
void main()
{
	set_fColor();

	//fColor=vec4(outColor,1.0);   
}
