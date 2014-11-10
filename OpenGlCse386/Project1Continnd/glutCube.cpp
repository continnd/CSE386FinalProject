#include "glutCube.h"

#include <vector>
#include <math.h>

#include "vertexStructs.h"

#define M_PI 3.1415926535897932384626433832795f

glutCube::glutCube( glm::vec4 color, float h)
	:GlutObject(color),
	height(h)
{
}

float glutCube::getZone() {
	return height*sqrt(2.0);
}

// Preform drawing operations
void glutCube::draw()
{
	GlutObject::draw();

	// Rings are divisions of the donut. 
	// 2 rings would theoritically cut the dont in half. 4 in would make quaters
	// sides are cuts which are perpendicular to the hole. 
	// 2 sides would theoritically be like slicing a bagel so you could make a sandwich 
	glutSolidCube(height);

} // end draw