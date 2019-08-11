#version 330 core
precision mediump float;
varying vec2 vTextureCoord;

uniform sampler2D texture0;
uniform int blurRadius;
uniform float blurStep;
uniform vec2 maskOffset;
uniform float kernel[30*31];

out vec4 color;
vec4 GaussBlur(int radius,vec2 maskOffset)
{
  vec4 curvalue;
  float weight =0.0;
  int idx = 0,j = 0;
  vec4  gaussvalue = vec4(0.0);
  int index =radius*31-31;
  weight     = kernel[index];
  curvalue = texture2D(texture0, vTextureCoord);
  gaussvalue += curvalue*weight;
  for(j = 1;j<=radius;j++)
  {
    idx = index+j;
    weight     = kernel[idx];
    curvalue = texture2D(texture0, vTextureCoord+float(j)*maskOffset);
    gaussvalue += curvalue*weight;
    curvalue = texture2D(texture0, vTextureCoord-float(j)*maskOffset);
    gaussvalue += curvalue*weight;
  }
  return gaussvalue;
}
void main() {
  color = GaussBlur(blurRadius,maskOffset);
  color.a = 1.0;
  color=vec4(0.2,0.6,0.1,0.5);
}