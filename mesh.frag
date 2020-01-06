#version 450 core
out vec4 fColor;
uniform vec2 iResolution;
uniform sampler2D ourTexture;
uniform sampler2D Faces_Vertices;
uniform sampler2D Faces_Index;
void main()
{

	fColor=vec4(1.0,0.0,0.0,1.0);   
}
