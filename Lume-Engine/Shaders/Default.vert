#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexPos;

out vec2 TexCoords;

uniform mat4 Transform;

void main()
{
    gl_Position = Transform * vec4(aPos, 1.0);
    TexCoords = aTexPos;
}