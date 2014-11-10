#include "Controller.h"
class shiftController : public Controller{
public:
	// Constructor sets the position of the object,
	// the axis about which it will rotate, and the rate and direction
	// of rotation.
	shiftController(glm::vec3 pos, GLfloat* xpos, GLfloat* angle);
	virtual void update(float elapsedTimeSeconds);
protected:
	// Position at which the object is spinning in place
	glm::vec3 position; 
	GLfloat* x;
	GLfloat* a;
};