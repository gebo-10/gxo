#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 coord;
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
out vec2 texture_coord;
out vec3 normal_lerped;
out vec3 FragPos;
void main()
{
    gl_Position = P*V*M*vec4(position,1.0);
    texture_coord = coord;

    vec4 word_pos=M*vec4(position,1.0);
    FragPos=word_pos.xyz;

    vec4 world_normal=M*vec4(normal,1.0);
    normal_lerped = world_normal.xyz;
}