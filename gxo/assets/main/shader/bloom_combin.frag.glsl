#version 330 core
in vec2 texture_coord;
out vec4 color;
uniform sampler2D texture0;
uniform sampler2D texture1;
void main()
{

    //color =texture2D(texture0,texture_coord);

	const float exposure = 1.0;
    const float gamma = 2.2;
   // vec3 hdrColor = vec3(0.0);
    vec3 hdrColor = texture(texture0, texture_coord).rgb;      
    vec3 bloomColor = texture(texture1, texture_coord).rgb;
    hdrColor += bloomColor*0.8; // additive blending
    // tone mapping
    vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
    // also gamma correct while we're at it       
    //result = pow(result, vec3(1.0 / gamma));
    color = vec4(result, 1.0f);
//    color=vec4(bloomColor, 1.0f);;
}