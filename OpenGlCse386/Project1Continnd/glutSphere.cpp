#include "glutSphere.h"

#include <vector>
#include <math.h>

#include "vertexStructs.h"

#define M_PI 3.1415926535897932384626433832795f

glutSphere::glutSphere( glm::vec4 color, float radius, int slices, int stacks)
	:GlutObject(color),
	cRadius(radius),
	cSlices(slices),
	cStacks(stacks)
{
}

float glutSphere::getZone() {
	return cRadius;
}

// Preform drawing operations
void glutSphere::draw()
{
	GlutObject::draw();

	// Rings are divisions of the donut. 
	// 2 rings would theoritically cut the dont in half. 4 in would make quaters
	// sides are cuts which are perpendicular to the hole. 
	// 2 sides would theoritically be like slicing a bagel so you could make a sandwich 
	glutSolidSphere(cRadius, cSlices, cStacks);

} // end draw