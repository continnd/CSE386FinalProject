#include "Pig.h"
#include "LegController.h"


Pig::Pig() {
	float radius = .2f;
	flLeg = new Cylinder(.5f, radius);
	frLeg = new Cylinder(.5f, radius);
	blLeg = new Cylinder(.5f, radius);
	brLeg = new Cylinder(.5f, radius);
	body = new Sphere(1.0f);
	face = new Sphere(0.5f);
	leftEye = new Sphere(.1f);
	rightEye = new Sphere(.1f);
	leftNostril = new Sphere(.1f);
	rightNostril = new Sphere(.1f);


	flLeg->fixedTransformation = translate(mat4(1.0f), vec3(.5f, -.5f, .5f)) * rotate(mat4(1.0f), 90.f, vec3(1, 0, 0));
	frLeg->fixedTransformation = translate(mat4(1.0f), vec3(-.5f, -.5f, .5f)) * rotate(mat4(1.0f), 90.f, vec3(1, 0, 0));
	blLeg->fixedTransformation = translate(mat4(1.0f), vec3(.5f, -.5f, -.5f)) * rotate(mat4(1.0f), 90.f, vec3(1, 0, 0));
	brLeg->fixedTransformation = translate(mat4(1.0f), vec3(-.5f, -.5f, -.5f))* rotate(mat4(1.0f), 90.f, vec3(1, 0, 0));
	face->fixedTransformation = translate(mat4(1.0f), vec3(0, 0, .75));
	rightEye->fixedTransformation = translate(mat4(1.0f), vec3(.11, .3, 1.00f));
	leftEye->fixedTransformation = translate(mat4(1.0f), vec3(-.11, .3, 1.00f));
	leftNostril->fixedTransformation = translate(mat4(1.0f), vec3(.11, 0, 1.25f));
	rightNostril->fixedTransformation = translate(mat4(1.0f), vec3(-.11, 0, 1.25f));

	addChild(flLeg);
	addChild(frLeg);
	addChild(blLeg);
	addChild(brLeg);
	addChild(body);
	addChild(face);
	addChild(rightEye);
	addChild(leftEye);
	addChild(leftNostril);
	addChild(rightNostril);

	frLeg->addController(new LegController(true));
	flLeg->addController(new LegController(false));
	brLeg->addController(new LegController(false));
	blLeg->addController(new LegController(true));

}


Pig::~Pig() {
}

void Pig::setAmbientAndDiffuseMat(vec4 mat){
	flLeg->material.setAmbientAndDiffuseMat(mat);
	frLeg->material.setAmbientAndDiffuseMat(mat);
	brLeg->material.setAmbientAndDiffuseMat(mat);
	blLeg->material.setAmbientAndDiffuseMat(mat);
	body->material.setAmbientAndDiffuseMat(mat);
	face->material.setAmbientAndDiffuseMat(mat);
	rightEye->material.setAmbientAndDiffuseMat(vec4(.5, 0, 0, 1));
	leftEye->material.setAmbientAndDiffuseMat(vec4(.5, 0, 0, 1));
	leftNostril->material.setAmbientAndDiffuseMat(vec4(0, 0, 0, 1));
	rightNostril->material.setAmbientAndDiffuseMat(vec4(0, 0, 0, 1));
}
void Pig::setEmissiveMat(vec4 mat) {
	flLeg->material.setEmissiveMat(mat);
	frLeg->material.setEmissiveMat(mat);
	brLeg->material.setEmissiveMat(mat);
	blLeg->material.setEmissiveMat(mat);
	body->material.setEmissiveMat(mat);
	face->material.setEmissiveMat(mat);
	rightEye->material.setEmissiveMat(vec4(0, 0, 0, 1));
	leftEye->material.setEmissiveMat(vec4(0, 0, 0, 1));
	rightNostril->material.setEmissiveMat(vec4(0, 0, 0, 1));
	leftNostril->material.setEmissiveMat(vec4(0, 0, 0, 1));
}

void Pig::setSpecularMat(vec4 mat) {
	flLeg->material.setSpecularMat(mat);
	frLeg->material.setSpecularMat(mat);
	brLeg->material.setSpecularMat(mat);
	blLeg->material.setSpecularMat(mat);
	body->material.setSpecularMat(mat);
	face->material.setSpecularMat(mat);
	rightEye->material.setSpecularMat(mat);
	leftEye->material.setSpecularMat(mat);
	rightNostril->material.setSpecularMat(mat);
	leftNostril->material.setSpecularMat(mat);
}

void Pig::setShader(GLuint shaderProgram) {
	flLeg->setShader(shaderProgram);
	frLeg->setShader(shaderProgram);
	brLeg->setShader(shaderProgram);
	blLeg->setShader(shaderProgram);
	body->setShader(shaderProgram);
	face->setShader(shaderProgram);
	rightEye->setShader(shaderProgram);
	leftEye->setShader(shaderProgram);
	leftNostril->setShader(shaderProgram);
	rightNostril->setShader(shaderProgram);
}

void Pig::setTextureMapped(bool isMapped) {
	flLeg->material.setTextureMapped(isMapped);
	frLeg->material.setTextureMapped(isMapped);
	brLeg->material.setTextureMapped(isMapped);
	blLeg->material.setTextureMapped(isMapped);
	body->material.setTextureMapped(isMapped);
	face->material.setTextureMapped(isMapped);
}

void Pig::setTexture(string texture) {
	flLeg->material.setupTexture(texture);
	frLeg->material.setupTexture(texture);
	brLeg->material.setupTexture(texture);
	blLeg->material.setupTexture(texture);
	body->material.setupTexture(texture);
	face->material.setupTexture(texture);
}

void Pig::draw() {
	VisualObject::draw();
}