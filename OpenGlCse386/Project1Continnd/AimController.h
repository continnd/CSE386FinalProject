#include "Controller.h"
class AimController : public Controller{
public:
	// Constructor sets the position of the object,
	// the axis about which it will rotate, and the rate and direction
	// of rotation.
	AimController(glm::vec3 pos, GLfloat* angle);
	virtual void update(float elapsedTimeSeconds);
protected:
	// Position at which the object is spinning in place
	glm::vec3 position; 
	GLfloat* angle;
};