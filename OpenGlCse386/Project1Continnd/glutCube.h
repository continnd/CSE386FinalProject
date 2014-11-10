#ifndef ___GLUTCUBE_H___
#define ___GLUTCUBE_H___

#include "GlutObject.h"


class glutCube : public GlutObject
{
	public:
		glutCube( glm::vec4 color = glm::vec4( 0.0f, 1.0f, 0.0f, 1.0f), float h = 1.0f);
		float getZone();

		virtual void draw();

	protected:
		float height;
};

#endif /* ___GLUTCUBE_H___ */