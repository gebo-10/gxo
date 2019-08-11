#version 330 core
in vec2 texture_coord;
out vec4 color;
uniform sampler2D texture0;
void main()
{
	const float exposure = 1.0;
    const float gamma = 2.2;
    vec3 hdrColor = texture(texture0, texture_coord).rgb;
    // 曝光色调映射
    vec3 mapped = vec3(1.0) - exp(-hdrColor * exposure);
    // Gamma校正 
    //mapped = pow(mapped, vec3(1.0 / gamma));

    color = vec4(mapped, 1.0);
}