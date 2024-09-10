#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexPos;
layout (location = 2) in vec3 aNor;

out vec2 TexCoords;

uniform mat4 Transform;
uniform mat4 Projection;
uniform mat4 View;

void main()
{
    gl_Position = Projection * View * Transform * vec4(aPos, 1.0);
    TexCoords = aTexPos;
}