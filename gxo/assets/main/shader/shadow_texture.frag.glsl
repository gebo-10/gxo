#version 330 core

in vec2 texture_coord;
in vec4 frag_light_pos;

out vec4 color;
uniform sampler2D texture0;
uniform sampler2D texture1;



float ShadowCalculation(vec4 fragPosLightSpace)
{
    // 执行透视除法
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // 变换到[0,1]的范围
    projCoords = projCoords * 0.5 + 0.5;
    // 取得最近点的深度(使用[0,1]范围下的fragPosLight当坐标)
    float closestDepth = texture(texture1, projCoords.xy).r; 
    // 取得当前片元在光源视角下的深度
    float currentDepth = projCoords.z;
    // 检查当前片元是否在阴影中
    // float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;

    // return shadow;

    float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(texture1, 0);
	for(int x = -5; x <= 5; ++x)
	{
	    for(int y = -5; y <= 5; ++y)
	    {
	        float pcfDepth = texture(texture1, projCoords.xy + vec2(x, y) * texelSize).r; 
	        shadow += currentDepth  > pcfDepth ? 1.0 : 0.0;        
	    }    
	}
	shadow /= 121.0;
	 return shadow;
}

void main()
{
    //color = vec4(0.8,0.5,0.8, 1.0);

    color =texture2D(texture0,texture_coord);
    float shadow=ShadowCalculation(frag_light_pos);
   
    if(shadow>0.0){
    	 color=color*(1.0-shadow+0.5)*0.5;
    }
    color.a=1.0;
}