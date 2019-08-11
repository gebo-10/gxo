#version 330 core

uniform sampler2D texture0;
uniform vec3 light_direction;

in vec2 texture_coord;
in vec3 normal_lerped;
in vec3 FragPos;


layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;
void main()
{
	vec3 viewPos=vec3(0.0,0.0,3.0);
	vec3 lightPos=vec3(1.0,2.0,3.0);
	vec3 lightColor=vec3(1.0,1.0,1.0)*3.0;

	vec3 objectColor =texture2D(texture0,texture_coord).xyz;
	//vec3 objectColor=vec3(1.0,1.0,1.0);

	float ambient_strength =0.2;
	vec3 ambient=vec3(1.0,1.0,1.0)* ambient_strength;



	vec3 norm = normalize(normal_lerped);
	vec3 lightDir = normalize(lightPos - FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;


	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 100);
	vec3 specular = 1.0 * spec * lightColor;



    vec3 result = (ambient + diffuse +specular) * objectColor;
	FragColor = vec4(result, 1.0f);
    
    BrightColor = vec4(0.,0.0,0.0, 0.0);
    float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0)
        BrightColor = vec4(FragColor.rgb, 1.0);
    //BrightColor = vec4(0.3,1.0,1.0, 1.0);
}