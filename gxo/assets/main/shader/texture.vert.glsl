#version 330 
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 coord;
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
out vec2 texture_coord;
void main()
{
    gl_Position = P*V*M*vec4(position,1.0);
    texture_coord = coord;
}