#version 460 core
out vec4 FragColor;  
in vec2 TexCoords;

uniform sampler2D TextureInstance;

void main()
{
    FragColor = texture(TextureInstance, TexCoords);
}