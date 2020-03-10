#version 330 core
//#extension GL_ARB_gpu_shader_fp64 : enable

uniform int WIDTH;
uniform int HEIGHT;
uniform int maxIterations;
uniform vec2 areaWidth;
uniform vec2 areaHeight;
out vec4 Color;

const vec3 color_map[] = {
    {0.0,  0.0,  0.0},
    {0.26, 0.18, 0.06},
    {0.1,  0.03, 0.1},
    {0.04, 0.0,  0.18},
    {0.02, 0.02, 0.29},
    {0.0,  0.03, 0.39},
    {0.05, 0.17, 0.54},
    {0.09, 0.32, 0.69},
    {0.22, 0.49, 0.82},
    {0.52, 0.71, 0.9},
    {0.82, 0.92, 0.97},
    {0.94, 0.91, 0.75},
    {0.97, 0.79, 0.37},
    {1.0,  0.67, 0.0},
    {0.8,  0.5,  0.0},
    {0.6,  0.34, 0.0},
    {0.41, 0.2,  0.01}
};

void main() {
     
     vec2 C = vec2((gl_FragCoord.x*(areaWidth.y-areaWidth.x))/WIDTH+areaWidth.x,
     (gl_FragCoord.y*(areaHeight.y-areaHeight.x))/HEIGHT+areaHeight.x);
     vec2 Z = vec2(0.0);
     int iteration = 0;

     while(iteration < maxIterations){
        float x = Z.x * Z.x - Z.y * Z.y + C.x;
	float y = 2.0 * Z.x * Z.y       + C.y;

	if(x*x+y*y>4.0) break;

	Z.x = x;
	Z.y = y;
	
	++iteration;
     }


    int row_index = (iteration * 100 / maxIterations % 17);
    Color = vec4((iteration == maxIterations ? vec3(0.0) : color_map[row_index]), 1.0);
}
	