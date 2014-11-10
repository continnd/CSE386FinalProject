#version 330

layout (std140) uniform projectionViewBlock
{
	mat4 projectionMatrix;
	mat4 viewMatrix;
};

uniform mat4 modelMatrix;

layout (location = 0) in vec3 vertexPosition; 

// There can only be one main function for each shader stage
void main()
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPosition, 1.0f);

}