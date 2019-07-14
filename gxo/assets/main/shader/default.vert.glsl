#version 330 
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out vec3 ourColor;

void main()
{
    gl_Position = P*V*M*vec4(position, 1.0f);
    ourColor = color;
}