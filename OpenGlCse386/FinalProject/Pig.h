#pragma once
#include "Cylinder.h"
#include "Sphere.h"
#include "VisualObject.h"
#include "SoundSource.h"
class Pig : public VisualObject
{
public:
	Pig();
	~Pig();

	void setAmbientAndDiffuseMat(vec4 mat);
	void setEmissiveMat(vec4 mat);
	void setSpecularMat(vec4 mat);
	void setShader(GLuint shaderProgram);
	void setTextureMapped(bool isMapped);
	void setTexture(string fileName);
	void pausePigSound();
	void playPigSound();
	bool soundPlaying();

	void draw();

private:
	Cylinder *flLeg, *frLeg, *blLeg, *brLeg;
	Sphere* body, *face, *leftEye, *rightEye, *leftNostril, *rightNostril;
	SoundSource* pigSound;
	bool soundOn;
};

