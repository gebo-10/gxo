#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 coord;
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

uniform mat4 light_vp;
out vec2 texture_coord;
out vec4 frag_light_pos;
void main()
{
    gl_Position = P*V*M*vec4(position,1.0);
    texture_coord = coord;

    vec4 world_pos=vec4(M * vec4(position, 1.0));
    frag_light_pos= light_vp * world_pos;
}