#version 330 core
layout (location = 0) out vec4 gPosition;
layout (location = 1) out vec4 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

in vec2 texture_coord;
in vec3 FragPos;
in vec3 normal_lerped;


//uniform sampler2D texture_diffuse1;
//uniform sampler2D texture_specular1;

uniform sampler2D texture0;

void main()
{    
    // 存储第一个G缓冲纹理中的片段位置向量
    gPosition = vec4(FragPos,1.0);
    // 同样存储对每个逐片段法线到G缓冲中
    gNormal = vec4(normalize(normal_lerped),1.0);
    // 和漫反射对每个逐片段颜色
    gAlbedoSpec.rgb = texture(texture0, texture_coord).rgb;
    //gAlbedoSpec= vec4(0.2,0.8,0.6,1.0);
    // 存储镜面强度到gAlbedoSpec的alpha分量
    //gAlbedoSpec.a = texture(texture_specular1, texture_coord).r;
    gAlbedoSpec.a=1.0;
}  