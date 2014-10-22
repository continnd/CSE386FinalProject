#pragma once

#include <iostream>

using namespace std;
 
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

vec3 findUnitNormal (vec3 v0, vec3 v1, vec3 v2);

GLint getUniformLocation(GLuint const m_shaderProg, char* pUniformName);

struct Material
{
	Material( GLint ambientMatLoc = 0xFFFFFFFF,  GLint diffuseMatLoc = 0xFFFFFFFF, 
			  GLint specularMatLoc = 0xFFFFFFFF, GLint specularExpMatLoc= 0xFFFFFFFF, 
			  GLint emissiveMatLoc = 0xFFFFFFFF, GLint textureMappedLoc =  0xFFFFFFFF )
	{
		this->ambientMatLoc = ambientMatLoc;  
		this->diffuseMatLoc =  diffuseMatLoc;
		this->specularMatLoc = specularMatLoc;
		this->specularExpMatLoc = specularExpMatLoc;
		this->emissiveMatLoc = emissiveMatLoc;
		this->textureMappedLoc = textureMappedLoc;

		ambientMat = vec4( 0.75f, 0.75f, 0.75f, 1.0f );
		diffuseMat = vec4( 0.75f, 0.75f, 0.75f, 1.0f );
		specularMat = vec4( 1.0f, 1.0f, 1.0f, 1.0f );
		specularExpMat = 64.0f;
		emissiveMat = vec4( 0.0f, 0.0f, 0.0f, 1.0f );
		textureMapped = false;
		
	}

	void setShaderMaterialProperties()
	{
		setAmbientMat( ambientMat );
		setDiffuseMat( diffuseMat );
		setSpecularMat( specularMat );
		setSpecularExponentMat( specularExpMat );
		setEmissiveMat( emissiveMat );
		setTextureMapped(textureMapped);
	}

	void setAmbientMat( vec4 ambientMat )
	{
		this->ambientMat = ambientMat;
		if (ambientMatLoc != 0xFFFFFFFF) {
			glUniform4fv( ambientMatLoc, 1, value_ptr(ambientMat));
		}
		else {
			cout << "ambient material location not set." << endl;
		}
	}

	void setDiffuseMat( vec4 diffuseMat )
	{
		this->diffuseMat = diffuseMat;
		if (diffuseMatLoc != 0xFFFFFFFF) {
			glUniform4fv( diffuseMatLoc, 1, value_ptr(diffuseMat));
		}
		else {
			cout << "Diffuse material location not set." << endl;
		}
	}

	void setSpecularMat( vec4 specularMat )
	{
		this->specularMat = specularMat;
		if (specularMatLoc != 0xFFFFFFFF) {
			glUniform4fv( specularMatLoc, 1, value_ptr(specularMat) );
		}
		else {
			cout << "Specular material location not set." << endl;
		}
	}

	void setSpecularExponentMat( float specularExpMat )
	{
		this->specularExpMat = specularExpMat;
		if (specularExpMatLoc != 0xFFFFFFFF) {
			glUniform1f( specularExpMatLoc, specularExpMat );

		}
		else {
			cout << "Specular exponent material location not set." << endl;
		}
	}

	void setEmissiveMat( vec4 emissiveMat )
	{
		this->emissiveMat = emissiveMat;
		if (emissiveMatLoc != 0xFFFFFFFF) {
			glUniform4fv( emissiveMatLoc, 1, value_ptr(emissiveMat) );
		}
		else {
			cout << "Emmissive material location not set." << endl;
		}
	}

	void setAmbientAndDiffuseMat( vec4 objectColor )
	{
		setAmbientMat( objectColor );
		setDiffuseMat( objectColor );

	}
	
	bool getTextureMapped() {return textureMapped; }


	void setTextureMapped(bool on)
	{
		this->textureMapped = on;
		if (textureMappedLoc != 0xFFFFFFFF) {
			glUniform1i(textureMappedLoc, textureMapped);
		}
		else {
			cout << "Texture mapped enabled location not set." << endl;
		}
	}

	protected: 

	GLint ambientMatLoc;
	vec4 ambientMat;

	GLint diffuseMatLoc;
	vec4 diffuseMat;
	
	GLint specularMatLoc;
	vec4 specularMat;
	
	GLint specularExpMatLoc;
	float specularExpMat;
	
	GLint emissiveMatLoc;
	vec4 emissiveMat;

	GLint textureMappedLoc;
	bool textureMapped;
};