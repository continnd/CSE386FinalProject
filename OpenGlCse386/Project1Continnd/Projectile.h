#ifndef ___PROJECTILE_H___
#define ___PROJECTILE_H___

#include "GlutObject.h"
#include "glutCylinder.h"
#include "glutSphere.h"

#define RAD 0.1f
#define HGHT 0.5f
#define SLC 8
#define STK 16
#define M_PI 3.1415926535897932384626433832795f

class Projectile : public GlutObject
{
	public:
		Projectile(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), GLfloat* gA = 0);

		virtual void draw();
		void setShader(GLuint shaderProgram);

	protected:
		glm::vec3 tpos;
		glutCylinder* body;
		glutCylinder* gun;
		glutSphere* top;
		GLfloat* gAngle;
};

#endif /* ___PROJECTILE_H___ */