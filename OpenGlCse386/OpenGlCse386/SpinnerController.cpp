#include "SpinnerController.h"
GLfloat rotation;

SpinnerController::SpinnerController(glm::vec3 pos,glm::vec3 ax, GLfloat r)
	:position(pos),
	axis(ax),
	rate(r)
{
	rotation=0;
}

void SpinnerController::update(float elapsedTimeSeconds){
	rotation+=elapsedTimeSeconds*rate;
	target->modelMatrix = glm::translate(glm::mat4(1.0f), 
		position)*glm::rotate(glm::mat4(1.0f),rotation,axis);
}