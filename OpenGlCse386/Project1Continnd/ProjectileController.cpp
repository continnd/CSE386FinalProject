#include "ProjectileController.h"

#define GRAV vec3(0.0f, -1.0f, 0.0f)
#define M_PI 3.1415926535897932384626433832795f

ProjectileController::ProjectileController(glm::vec3 pos, GLfloat* gAngle, GLfloat* tAngle, GLfloat v)
	:position(pos)
{
	vVector = v*vec3(-sin(*tAngle*M_PI/180), sin(*gAngle*M_PI/180), -cos(*gAngle*M_PI/180)*cos(*tAngle*M_PI/180));
}

void ProjectileController::update(float elapsedTimeSeconds){
	vVector = vVector + elapsedTimeSeconds*GRAV;
	position = position + vVector * elapsedTimeSeconds;
	target->modelMatrix = glm::translate(glm::mat4(1.0f), position);
}