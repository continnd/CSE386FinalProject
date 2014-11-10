#include "Projectile.h"

#include <vector>
#include <math.h>

#include "vertexStructs.h"
#include "AimController.h"

Projectile::Projectile(vec3 pos, GLfloat* gA)
{

}

void Projectile::setShader(GLuint shaderProgram) {
	body->setShader(shaderProgram);
	gun->setShader(shaderProgram);
	top->setShader(shaderProgram);
}

// Preform drawing operations
void Projectile::draw()
{
	GlutObject::draw();
	VisualObject::draw();
} // end draw
