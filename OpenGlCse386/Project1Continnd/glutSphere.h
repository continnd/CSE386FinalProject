#ifndef ___GLUTSPHERE_H___
#define ___GLUTSPHERE_H___

#include "GlutObject.h"


class glutSphere : public GlutObject
{
	public:
		glutSphere( glm::vec4 color = glm::vec4( 0.0f, 1.0f, 0.0f, 1.0f), 
			   float radius= 0.25f, int slices = 8, int stacks = 16);
		float getZone();
		virtual void draw();

	protected:
		
		GLdouble cRadius;
		GLint cSlices, cStacks;
};

#endif /* ___GLUTSPHERE_H___ */