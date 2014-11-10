#pragma once
#include "VisualObject.h"
#include "BuildShaderProgram.h"

class GlutObject : public VisualObject
{
	public:
	
		GlutObject( glm::vec4 color );

		virtual void initialize();

		virtual void draw();

		virtual float getZone();

	protected:
	
		void setShaderValues();

		GLuint solidColorLocation;
		glm::vec4 objectColor;

};

