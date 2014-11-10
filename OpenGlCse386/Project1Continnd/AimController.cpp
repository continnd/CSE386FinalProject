#include "AimController.h"

AimController::AimController(glm::vec3 pos, GLfloat* a)
	:position(pos),
	angle(a)
{
}

void AimController::update(float elapsedTimeSeconds){
	target->modelMatrix = rotate(mat4(1.0f), *angle, vec3(1.0f, 0.0f, 0.0f))*translate(mat4(1.0f), position);
}