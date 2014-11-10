#include "Atom.h"
#include <vector>
#include <math.h>
#include "OrbitController.h"

#define M_PI 3.1415926535897932384626433832795f

Atom::Atom(float r)
	:GlutObject(vec4(0.0f, 0.0f, 0.0f, 1.0f)),
	radius(r)
{
	center=new glutSphere(vec4(0.5f, 0.0f, 0.5f, 1.0f), radius/6, 16, 32);
	prot1=new glutSphere(vec4(0.5f, 0.5f, 0.5f, 1.0f), radius/6, 16, 32);
	prot2=new glutSphere(vec4(0.5f, 0.5f, 0.5f, 1.0f), radius/6, 16, 32);
	prot3=new glutSphere(vec4(0.5f, 0.5f, 0.5f, 1.0f), radius/6, 16, 32);
	prot4=new glutSphere(vec4(0.5f, 0.5f, 0.5f, 1.0f), radius/6, 16, 32);
	prot5=new glutSphere(vec4(0.5f, 0.0f, 0.5f, 1.0f), radius/6, 16, 32);
	prot6=new glutSphere(vec4(0.5f, 0.5f, 0.5f, 1.0f), radius/6, 16, 32);
	prot7=new glutSphere(vec4(0.5f, 0.0f, 0.5f, 1.0f), radius/6, 16, 32);
	prot8=new glutSphere(vec4(0.5f, 0.0f, 0.5f, 1.0f), radius/6, 16, 32);
	prot9=new glutSphere(vec4(0.5f, 0.0f, 0.5f, 1.0f), radius/6, 16, 32);
	prot10=new glutSphere(vec4(0.5f, 0.0f, 0.5f, 1.0f), radius/6, 16, 32);
	electron1=new glutSphere(vec4(0.5f, 0.5f, 0.0f, 1.0f), radius/7, 16, 32);
	electron2=new glutSphere(vec4(0.5f, 0.5f, 0.0f, 1.0f), radius/7, 16, 32);
	electron3=new glutSphere(vec4(0.5f, 0.5f, 0.0f, 1.0f), radius/7, 16, 32);
	ring1=new Torus(vec4(0.0f, 0.0f, 0.0f, 1.0f), 0.05f, radius, 8, 16);
	ring2=new Torus(vec4(0.0f, 0.0f, 0.0f, 1.0f), 0.05f, radius, 8, 16);
	ring3=new Torus(vec4(0.0f, 0.0f, 0.0f, 1.0f), 0.05f, radius, 8, 16);
	electron1->addController(new OrbitController(radius*vec3(1/sqrt(2.0), 1/sqrt(2.0), 0.0f), vec3(-1.0f, 1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), 300.0f, 1.0f));
	electron2->addController(new OrbitController(radius*vec3(-1/sqrt(2.0), 1/sqrt(2.0), 0.0f), vec3(-1.0f, -1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), 320.0f, 1.0f));
	electron3->addController(new OrbitController(radius*vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), 350.0f, 1.0f));
	prot1->fixedTransformation = translate(mat4(1.0f), vec3(0.0f, 1.0/4.0*radius, 0.0f));
	prot2->fixedTransformation = translate(mat4(1.0f), vec3(0.0f, -1.0/4.0*radius, 0.0f));
	prot3->fixedTransformation = translate(mat4(1.0f), vec3(1.0/4.0*radius, 0.0f, 0.0f));
	prot4->fixedTransformation = translate(mat4(1.0f), vec3(-1.0/4.0*radius, 0.0f, 0.0f));
	prot5->fixedTransformation = translate(mat4(1.0f), vec3(0.0f, 0.0f, 1.0/4.0*radius));
	prot6->fixedTransformation = translate(mat4(1.0f), vec3(0.0f, 0.0f, -1.0/4.0*radius));
	prot7->fixedTransformation = translate(mat4(1.0f), vec3((1/sqrt(2.0f))/3.0*radius, (1/sqrt(2.0f))/4.0*radius, 0.0f));
	prot8->fixedTransformation = translate(mat4(1.0f), vec3((1/sqrt(2.0f))/3.0*radius, -(1/sqrt(2.0f))/4.0*radius, 0.0f));
	prot9->fixedTransformation = translate(mat4(1.0f), vec3(-(1/sqrt(2.0f))/3.0*radius, -(1/sqrt(2.0f))/4.0*radius, 0.0f));
	prot10->fixedTransformation = translate(mat4(1.0f), vec3(-(1/sqrt(2.0f))/3.0*radius, (1/sqrt(2.0f))/4.0*radius, 0.0f));
	ring1->fixedTransformation = rotate(mat4(1.0f), 90.0f, vec3(1.0f, 0.0f, 0.0f))*rotate(mat4(1.0f), 45.0f, vec3(0.0f, 1.0f, 0.0f));
	ring2->fixedTransformation = rotate(mat4(1.0f), 90.0f, vec3(1.0f, 0.0f, 0.0f))*rotate(mat4(1.0f), -45.0f, vec3(0.0f, 1.0f, 0.0f));
    ring3->fixedTransformation = rotate(mat4(1.0f), 90.0f, vec3(1.0f, 0.0f, 0.0f));
	addChild(center);
	addChild(ring1);
	addChild(ring2);
	addChild(ring3);
	addChild(prot1);
	addChild(prot2);
	addChild(prot3);
	addChild(prot4);
	addChild(prot5);
	addChild(prot6);
	addChild(prot7);
	addChild(prot8);
	addChild(prot9);
	addChild(prot10);
	addChild(electron1);
	addChild(electron2);
	addChild(electron3);
}

void Atom::setShader( GLuint shaderProgram ) 
{ 
	for (unsigned int i = 0; i < children.size(); i++) {
		children[i]->setShader(shaderProgram);
	}
}

float Atom::getZone() {
	return radius;
}

// Preform drawing operations
void Atom::draw()
{
	VisualObject::draw();
} // end draw