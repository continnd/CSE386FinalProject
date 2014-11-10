#include "glutCone.h"

#include <vector>
#include <math.h>

#include "vertexStructs.h"

#define M_PI 3.1415926535897932384626433832795f

glutCone::glutCone( glm::vec4 color, float radius, float height, int slices, int stacks)
	:GlutObject(color),
	cRadius(radius),
	cHeight(height),
	cSlices(slices),
	cStacks(stacks)
{
}

float glutCone::getZone() {
	return cRadius*2.0/3.0;
}

// Preform drawing operations
void glutCone::draw()
{
	GlutObject::draw();

	// Rings are divisions of the donut. 
	// 2 rings would theoritically cut the dont in half. 4 in would make quaters
	// sides are cuts which are perpendicular to the hole. 
	// 2 sides would theoritically be like slicing a bagel so you could make a sandwich 
	glutSolidCone(cRadius, cHeight, cSlices, cStacks);

} // end draw