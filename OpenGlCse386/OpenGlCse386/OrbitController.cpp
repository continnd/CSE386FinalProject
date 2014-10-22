#include "OrbitController.h"

OrbitController::OrbitController(glm::vec3 pos, glm::vec3 oAx, glm::vec3 rAx, GLfloat oR, GLfloat rR)
	:position(pos),
	orbitAxis(oAx),
	rotationAxis(rAx),
	oRate(oR),
	rRate(rR),
	rotation(0),
	revolution(0)
{
}

void OrbitController::update(float elapsedTimeSeconds){
	rotation+=elapsedTimeSeconds*rRate;
	revolution+=elapsedTimeSeconds*oRate;
	target->modelMatrix = glm::rotate(glm::mat4(1.0f),revolution,orbitAxis)*glm::translate(glm::mat4(1.0f), 
		position)*glm::rotate(glm::mat4(1.0f),rotation,rotationAxis);
}