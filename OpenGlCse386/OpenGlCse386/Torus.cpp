#include "Torus.h"

#include <vector>
#include <math.h>

#include "vertexStructs.h"

#define M_PI 3.1415926535897932384626433832795f

Torus::Torus( glm::vec4 color, float innerRadius, float outerRadius,  int sides, int rings)
	:GlutObject(color)
{
	dInnerRadius =  innerRadius;
	dOuterRadius = outerRadius;
	nSides = sides; 
	nRings = rings;
}

float Torus::getZone() {
	return dOuterRadius;
}

// Preform drawing operations
void Torus::draw()
{
	GlutObject::draw();

	// Rings are divisions of the donut. 
	// 2 rings would theoritically cut the dont in half. 4 in would make quaters
	// sides are cuts which are perpendicular to the hole. 
	// 2 sides would theoritically be like slicing a bagel so you could make a sandwich 
	glutSolidTorus( dInnerRadius, dOuterRadius, nSides, nRings);

} // end draw

