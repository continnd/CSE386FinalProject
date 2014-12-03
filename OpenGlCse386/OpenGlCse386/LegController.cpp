#include "LegController.h"

#define M_PI 3.1415926535897932384626433832795f

LegController::LegController(bool forward)
	:ang(0.0f),
	forw(forward)
{
}

void
LegController::update(float elapsedTimeSec) {
	if(ang > 45.0f)
		forw= !forw;
	else if(ang < -45.0f)
		forw= !forw;
	if(forw)
		ang++;
	else
		ang--;

	target->modelMatrix = translate(mat4(1.0f), vec3(0.0f, 0.25f, 0.0f))*
		rotate(mat4(1.0f), ang, vec3(1.0f, 0.0f, 0.0f))*translate(mat4(1.0f),
		vec3(0.0f, -0.25f, 0.0f));
}