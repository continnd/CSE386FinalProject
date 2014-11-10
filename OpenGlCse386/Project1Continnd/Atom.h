#ifndef ___ATOM_H___
#define ___ATOM_H___

#include "GlutObject.h"
#include "glutSphere.h"
#include "Torus.h"


class Atom : public GlutObject
{
public:
	Atom(float r = 0.5f);
	void setShader( GLuint shaderProgram );
	float getZone();
	virtual void draw();

protected:
	float radius;
	glutSphere* center;
	glutSphere* prot1;
	glutSphere* prot2;
	glutSphere* prot3;
	glutSphere* prot4;
	glutSphere* prot5;
	glutSphere* prot6;
	glutSphere* prot7;
	glutSphere* prot8;
	glutSphere* prot9;
	glutSphere* prot10;
	glutSphere* electron1;
	glutSphere* electron2;
	glutSphere* electron3;
	Torus* ring1;
	Torus* ring2;
	Torus* ring3;
};

#endif /* ___ATOM_H___ */