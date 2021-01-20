#version 450 core
out vec4 fColor;

in vec2 TexCoords;

uniform sampler2D ourTexture;

void main()
{
    vec3 col = texture(ourTexture, TexCoords).xyz;
    fColor = vec4(col, 1.0);
 //   fColor=vec4(1,0,0,1);
} 