#ifndef ___GLUTCONE_H___
#define ___GLUTCONE_H___

#include "GlutObject.h"


class glutCone : public GlutObject
{
	public:
		glutCone( glm::vec4 color = glm::vec4( 0.0f, 1.0f, 0.0f, 1.0f), float radius=0.5f, float height= 1.0f, int slices = 8, int stacks = 16);
		float getZone();

		virtual void draw();

	protected:
		
		GLfloat cRadius, cHeight;
		GLint cSlices, cStacks;
};

#endif /* ___GLUTCONE_H___ */