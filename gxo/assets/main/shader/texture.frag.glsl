#version 330
in vec2 texture_coord;
out vec4 color;
uniform sampler2D texture0;
void main()
{
    //color = vec4(0.8,0.5,0.8, 1.0);
    color =texture2D(texture0,texture_coord);
}