#version 330 core
out vec4 FragColor;

uniform float color;

void main()
{
    FragColor = vec4(0.5,color,0,1.0);
} 