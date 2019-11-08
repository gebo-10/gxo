#version 450

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 coord;
layout (location = 3) in vec2 coord1;
layout (location = 4) in vec4 inJoint0;
layout (location = 5) in vec4 inWeight0;

#define MAX_NUM_JOINTS 128

layout (set = 2, binding = 1) uniform UBONode {
    mat4 matrix;
    mat4 jointMatrix[MAX_NUM_JOINTS];
    float jointCount;
} node;


uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
out vec2 texture_coord;
out vec3 normal_lerped;
out vec3 FragPos;

void main()
{

    mat4 skinMat = 
            inWeight0.x * node.jointMatrix[int(inJoint0.x)] +
            inWeight0.y * node.jointMatrix[int(inJoint0.y)] +
            inWeight0.z * node.jointMatrix[int(inJoint0.z)] +
            inWeight0.w * node.jointMatrix[int(inJoint0.w)];


    vec4 PosL = skinMat * vec4(position, 1.0);
    //vec4 PosL = vec4(position, 1.0);

    gl_Position = P*V*M*PosL;
    texture_coord = coord;

     vec4 word_pos=M*vec4(position,1.0);
    FragPos=word_pos.xyz;

    vec4 world_normal=M*vec4(normal,1.0);
    normal_lerped = world_normal.xyz;
}