#ifndef ___TORUS_H___
#define ___TORUS_H___

#include "GlutObject.h"


class Torus : public GlutObject
{
	public:
		Torus( glm::vec4 color = glm::vec4( 0.0f, 1.0f, 0.0f, 1.0f), 
			   float innerRadius= 0.25f, float outerRadius = 1.0f, 
			   int sides = 8, int rings = 16);
		float getZone();

		virtual void draw();

	protected:
		
		GLdouble dInnerRadius, dOuterRadius;
		GLint nSides, nRings;
};

#endif /* ___TORUS_H___ */

