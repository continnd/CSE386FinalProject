#include "GlutObject.h"


GlutObject::GlutObject(glm::vec4 color)
	:VisualObject(), objectColor(color)
{
}

void GlutObject::initialize()
{
	setShaderValues();

	VisualObject::initialize();

} // end initialize

float GlutObject::getZone() {
	return 0;
}

void GlutObject::setShaderValues()
{
	// This program will stay in effect for all draw calls until it is 
	// replaced with another or explicitly disabled (and the 
	// fixed function pipeline is enabld) by calling glUseProgram with NULL
    glUseProgram(shaderProgram);

	modelLocation = glGetUniformLocation(shaderProgram, "modelMatrix");
	assert(modelLocation != 0xFFFFFFFF);

	solidColorLocation = glGetUniformLocation(shaderProgram, "objectColor");
	assert(solidColorLocation != 0xFFFFFFFF);
}

// Preform drawing operations
void GlutObject::draw()
{
	// Draw all children
	VisualObject::draw();

	glUseProgram(shaderProgram);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelAndFixed));
	glUniform4fv(solidColorLocation, 1, glm::value_ptr(objectColor));

} // end draw
