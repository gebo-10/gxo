#version 330 core

uniform sampler2D texture0;

uniform float kzTextureWidth0;
uniform  float kzTextureHeight0;

uniform  vec2 BlurDirection;

uniform  float BlurRadius;


in vec2 texture_coord;

out vec4 color;
vec4 gaussianBlur( vec2 coord,  vec2 dir)
{

    // Defines the one-dimensional Gaussian Kernel with 9 samples.
    float GAUSSIAN_KERNEL[9];
    GAUSSIAN_KERNEL[0] = 0.028532;
    GAUSSIAN_KERNEL[1] = 0.067234;
    GAUSSIAN_KERNEL[2] = 0.124009;
    GAUSSIAN_KERNEL[3] = 0.179044;
    GAUSSIAN_KERNEL[4] = 0.20236;
    GAUSSIAN_KERNEL[5] = 0.179044;
    GAUSSIAN_KERNEL[6] = 0.124009;
    GAUSSIAN_KERNEL[7] = 0.067234;
    GAUSSIAN_KERNEL[8] = 0.028532;

    vec2 texel = vec2(1.0/kzTextureWidth0, 1.0/kzTextureHeight0);
    vec4 sum = vec4(0.0);
    // Get the original texture coordinate for this fragment.
    vec2 tc = coord;
    // Get the amount to blur.
    float blur = BlurRadius;
    // Set the amount of blur in the horizontal direction.
    float hstep = dir.x*texel.x;
    // Set the amount of blur in the vertical direction.
    float vstep = dir.y*texel.y;
    
    // Sample the texture 9 times for every fragment.
    for(int i = 0; i < 9; i++)
    {
        float pixelOffset = (float(i) - floor(9.0 * 0.5));
         vec2 coord = vec2(tc.x + pixelOffset * blur * hstep, tc.y + pixelOffset * blur * vstep);
        sum += texture2D(texture0, coord) * GAUSSIAN_KERNEL[i];
    }

    return sum;
    //return vec4(0.9,0.4,0.2,1.0);
}

void main()
{
    color = gaussianBlur(texture_coord, BlurDirection) ;
    //gl_FragColor =texture2D(texture0, texture_coord);
    color.a=1.0;
}