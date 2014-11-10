#version 330

uniform vec4 objectColor;

out vec4 FragColor;

void main()
{
	// Set the fragment color.
    FragColor = objectColor; 
}