#version 450 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 coord;
layout (location = 3) in vec4 boneid;
layout (location = 4) in vec4 weights;
uniform mat4 bones[50];
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
out vec2 texture_coord;
out vec3 normal_lerped;
out vec3 FragPos;
void main()
{
	int index=int(boneid.x);
	mat4 BoneTransform = weights.x *bones[index] ;
	index=int(boneid.y);
    BoneTransform += weights.y *bones[index];
    index=int(boneid.z);
    BoneTransform += weights.z *bones[index];
    index=int(boneid.w);
    BoneTransform += weights.w *bones[index];

    vec4 PosL = BoneTransform * vec4(position, 1.0);
    //vec4 PosL = vec4(position, 1.0);

    gl_Position = P*V*M*PosL;
    texture_coord = coord;

     vec4 word_pos=M*vec4(position,1.0);
    FragPos=word_pos.xyz;

    vec4 world_normal=M*vec4(normal,1.0);
    normal_lerped = world_normal.xyz;
}