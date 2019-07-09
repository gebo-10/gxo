#version 330 

layout(location = 0) in vec3 VertexPosition;
//layout(location = 1) in vec2 vertTexCoord;

out vec2 fragTexCoord;
void main(){
	fragTexCoord=vec2(0.0);
	gl_Position =vec4(VertexPosition,1.0);;
}