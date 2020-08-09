#version 330 core
out vec4 FragColor;
in vec2 texture_coord;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

struct Light {
    vec3 Position;
    vec3 Color;
};
const int NR_LIGHTS = 32;
uniform Light lights[NR_LIGHTS];
uniform vec3 viewPos;

void main()
{             

     vec3 FragPos = texture(gPosition, texture_coord).rgb;
     vec3 Normal = texture(gNormal, texture_coord).rgb;
     vec3 Albedo = texture(gAlbedoSpec, texture_coord).rgb;
     float Specular = texture(gAlbedoSpec, texture_coord).a;


    vec3 lighting = Albedo * 0.1; // 硬编码环境光照分量
    vec3 viewDir = normalize(viewPos - FragPos);
    for(int i = 0; i < NR_LIGHTS; ++i)
    {
        // 漫反射
        vec3 lightDir = normalize(lights[i].Position - FragPos);
        vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Albedo * lights[i].Color;
        lighting += diffuse;
    }

    FragColor = vec4(lighting, Specular);
    //FragColor = vec4(Albedo, 0.2);
}  