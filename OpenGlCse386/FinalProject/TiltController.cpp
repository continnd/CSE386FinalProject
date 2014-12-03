#include "TiltController.h"

#define M_PI 3.1415926535897932384626433832795f

TiltController::TiltController(int* view, bool* moveForward, int* mouse_x, int* mouse_y, vec3* playerPos)
	:mf(moveForward),
	v(view),
	vertAngle(0.0f),
	mx(mouse_x),
	my(mouse_y),
	pp(playerPos)
{
}

void
TiltController::update(float elapsedTimeSec) {
	mat4 trans, rot;
	trans= translate(mat4(1.0f), *pp);
	rot = mat4(0.0f);
	if(*v == 1) {
		GLfloat angle = acos(dot(vec3(0.0f, 0.0f, -1.0f),
			vec3(*mx, 0.0f, *my))/(length(vec3(0.0f, 0.0f, -1.0f))
			*length(vec3(*mx, 0.0f, *my))))*180/M_PI;
		if(*mf && vertAngle < 45.0f)
			vertAngle += 1.0f;
		else if(!*mf && vertAngle > 0.0f)
			vertAngle -= 1.0f;
		if(*mx < 0.0f)
			angle = -angle;
		rot = rotate(mat4(1.0f), angle, vec3(0.0f, -1.0, 0.0f));
		rot *= rotate(mat4(1.0f), vertAngle, vec3(-1.0f, 0.0, 0.0f));
	}
	target->modelMatrix=trans*rot;
}