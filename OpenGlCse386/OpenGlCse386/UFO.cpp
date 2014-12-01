#include "UFO.h"


UFO::UFO(GLfloat radius)
	:r(radius)
{
	top = new Cone(r*.1, r, 8, 16);
	bottom = new Cone(r*.1, r, 8, 16);
	cockpit = new Sphere(r*.2, 16, 16);
	top->fixedTransformation = rotate(mat4(1.0f), 90.0f, vec3(1.0f, 0.0f, 0.0f));
	bottom->fixedTransformation = rotate(mat4(1.0f), 90.0f, vec3(-1.0f, 0.0f, 0.0f));
	cockpit->fixedTransformation = translate(mat4(1.0f), vec3(0.0f, r*.05, 0.0f));
	addChild(top);
	addChild(bottom);
	addChild(cockpit);
}


UFO::~UFO() {
}

void UFO::setShader(GLuint shaderProgram) {
	top->setShader(shaderProgram);
	bottom->setShader(shaderProgram);
	cockpit->setShader(shaderProgram);
	top->material.setAmbientMat(vec4(0.0f,0.0f,0.0f,1.0f));
	top->material.setDiffuseMat(vec4(0.0f,0.0f,0.0f,1.0f));
	top->material.setEmissiveMat(vec4(0.0f,0.0f,0.0f,1.0f));
	top->material.setSpecularMat(vec4(0.0f,0.0f,0.0f,1.0f));
	bottom->material.setAmbientMat(vec4(0.0f,0.0f,0.0f,1.0f));
	bottom->material.setDiffuseMat(vec4(0.0f,0.0f,0.0f,1.0f));
	bottom->material.setEmissiveMat(vec4(0.0f,0.0f,0.0f,1.0f));
	bottom->material.setSpecularMat(vec4(0.0f,0.0f,0.0f,1.0f));
	cockpit->material.setAmbientMat(vec4(0.5f,0.0f,0.0f,0.2f));
	cockpit->material.setDiffuseMat(vec4(0.5f,0.0f,0.0f,0.2f));
	cockpit->material.setEmissiveMat(vec4(0.5f,0.0f,0.0f,0.2f));
	cockpit->material.setSpecularMat(vec4(0.5f, 0.0f,0.0f,0.2f));
}

void UFO::draw() {
	VisualObject::draw();
}