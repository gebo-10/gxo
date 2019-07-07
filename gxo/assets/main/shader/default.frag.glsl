#version 330 
uniform sampler2D texture;
in vec2 fragTexCoord;
out vec4 FragColor;
 
void main(){
	//vec2 pos=vec2(0.5,0.9);
	//FragColor = texture(texture,fragTexCoord );
	//FragColor = texture2D(texture,fragTexCoord.st);
	FragColor=vec4(0.5,0.6,0.9,1.0);
}