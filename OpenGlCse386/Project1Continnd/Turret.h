#ifndef ___TURRET_H___
#define ___TURRET_H___

#include "GlutObject.h"
#include "glutCylinder.h"
#include "glutSphere.h"

#define RAD 0.1f
#define HGHT 0.5f
#define SLC 16
#define STK 32
#define M_PI 3.1415926535897932384626433832795f

class Turret : public GlutObject
{
	public:
		Turret(GLfloat* gA = 0);

		virtual void draw();
		void setShader(GLuint shaderProgram);

	protected:
		glutCylinder* body;
		glutCylinder* gun;
		glutSphere* top;
		GLfloat* gAngle;
};

#endif /* ___TURRET_H___ */