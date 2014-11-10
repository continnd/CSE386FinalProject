// Targeting version 3.3 of GLSL. If the compiler does not support 
// 3.3 it will cause an error.
#version 330

// The rasterizer runs over all the pixels that are inside
// the point, line, or triangle. For each pixel the fragment shader is executed. 

// Usually the job of the fragment shader is to determine the 
// color of the fragment (pixel). In addition, the fragment shader 
// can discard the pixel altogether or change its Z value (which will
// impact the result of subsequent Z test).
out vec4 FragColor;
in vec4 vertexColor0;

void main()
{
	// Set the fragment color to red.
    FragColor = vertexColor0;
}
