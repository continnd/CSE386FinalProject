#include "Turret.h"

#include <math.h>

#include "AimController.h"

Turret::Turret(GLfloat* gA)
	:GlutObject(vec4(0.0f, 0.0f, 0.0f, 1.0f)),
	gAngle(gA)
{
	body = new glutCylinder(vec4(0.0f, 0.0f, 0.0f, 1.0f), RAD, HGHT, SLC, STK);
	gun = new glutCylinder(vec4(0.5f, 0.0f, 0.0f, 1.0f), RAD/4, RAD*2, SLC, STK);
	top = new glutSphere(vec4(0.0f, 0.0f, 0.0f, 0.5f), RAD, SLC, STK);
	body->fixedTransformation = rotate(mat4(1.0f), 90.0f, vec3(1.0f, 0.0f, 0.0f));
	top->fixedTransformation = translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f));
	gun->addController(new AimController(vec3(0.0f, RAD/4, -2*RAD), gAngle));
	addChild(body);
	addChild(gun);
	addChild(top);
}

void Turret::setShader(GLuint shaderProgram) {
	body->setShader(shaderProgram);
	gun->setShader(shaderProgram);
	top->setShader(shaderProgram);
}

// Preform drawing operations
void Turret::draw()
{
	VisualObject::draw();
} // end draw
