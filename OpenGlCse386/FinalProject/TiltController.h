#include "Controller.h"
class TiltController :
	public Controller
{
public:
	TiltController(int* view, bool* moveForward, bool* moveBack, bool* moveLeft, bool* moveRight, int* mouse_x, int* mouse_y, vec3* playerPos);
	virtual void update(float elapsedTimeSeconds);
protected:
	// Position at which the object is spinning in place
	glm::vec3 vertAxes, horiAxes, *pp;
	float vertAngle, horiAngle;
	bool* mf, *mb, *ml, *mr;
	int* v, *mx, *my;
};