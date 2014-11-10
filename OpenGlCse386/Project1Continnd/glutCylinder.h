#ifndef ___GLUTCYLINDER_H___
#define ___GLUTCYLINDER_H___

#include "GlutObject.h"


class glutCylinder : public GlutObject
{
	public:
		glutCylinder( glm::vec4 color = glm::vec4( 0.0f, 1.0f, 0.0f, 1.0f), 
			   float radius= 0.25f, float height= 1.0f, 
			   int slices = 8, int stacks = 16);

		virtual void draw();

	protected:
		
		GLdouble cRadius, cHeight;
		GLint cSlices, cStacks;
};

#endif /* ___GLUTCYLINDER_H___ */