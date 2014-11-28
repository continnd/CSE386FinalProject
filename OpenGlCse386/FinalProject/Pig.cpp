#include "Pig.h"


Pig::Pig() {
	float radius = .2f;
	flLeg = new Cylinder(.5f, radius);
	frLeg = new Cylinder(.5f, radius);
	blLeg = new Cylinder(.5f, radius);
	brLeg = new Cylinder(.5f, radius);
	body = new Sphere(1.0f);


	flLeg->fixedTransformation = translate(mat4(1.0f), vec3(.5f, -.5f, .5f)) * rotate(mat4(1.0f), 90.f, vec3(1, 0, 0));
	frLeg->fixedTransformation = translate(mat4(1.0f), vec3(-.5f, -.5f, .5f)) * rotate(mat4(1.0f), 90.f, vec3(1, 0, 0));
	blLeg->fixedTransformation = translate(mat4(1.0f), vec3(.5f, -.5f, -.5f)) * rotate(mat4(1.0f), 90.f, vec3(1, 0, 0));
	brLeg->fixedTransformation = translate(mat4(1.0f), vec3(-.5f, -.5f, -.5f))* rotate(mat4(1.0f), 90.f, vec3(1, 0, 0));


	addChild(flLeg);
	addChild(frLeg);
	addChild(blLeg);
	addChild(brLeg);
	addChild(body);
}


Pig::~Pig() {
}

void Pig::setAmbientAndDiffuseMat(vec4 mat){
	flLeg->material.setAmbientAndDiffuseMat(mat);
	frLeg->material.setAmbientAndDiffuseMat(mat);
	brLeg->material.setAmbientAndDiffuseMat(mat);
	blLeg->material.setAmbientAndDiffuseMat(mat);
	body->material.setAmbientAndDiffuseMat(mat);
}
void Pig::setEmissiveMat(vec4 mat) {
	flLeg->material.setEmissiveMat(mat);
	frLeg->material.setEmissiveMat(mat);
	brLeg->material.setEmissiveMat(mat);
	blLeg->material.setEmissiveMat(mat);
	body->material.setEmissiveMat(mat);
}
void Pig::setShader(GLuint shaderProgram) {
	flLeg->setShader(shaderProgram);
	frLeg->setShader(shaderProgram);
	brLeg->setShader(shaderProgram);
	blLeg->setShader(shaderProgram);
	body->setShader(shaderProgram);
}

void Pig::draw() {
	VisualObject::draw();
}