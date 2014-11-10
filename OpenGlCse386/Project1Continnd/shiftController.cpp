#include "shiftController.h"

shiftController::shiftController(glm::vec3 pos, GLfloat* xpos, GLfloat* angle)
	:position(pos),
	x(xpos),
	a(angle)
{
}

void shiftController::update(float elapsedTimeSeconds){
	target->modelMatrix = glm::translate(glm::mat4(1.0f), vec3(*x, position.y, position.z))*rotate(mat4(1.0f), *a, vec3(0.0f, 1.0f, 0.0f));
}