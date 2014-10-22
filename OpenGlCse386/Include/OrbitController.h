#include "Controller.h"
class OrbitController : public Controller{
public:
	// Constructor sets the position of the object,
	// the axis about which it will rotate, and the rate and direction
	// of rotation.
	OrbitController( glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), 
		glm::vec3 oAx = glm::vec3(1.0, 0.0f, 0.0f), glm::vec3 rAx = glm::vec3(0.0, 0.0f, 1.0f), GLfloat oR = 10.0f, GLfloat rR = 10.0f);
	virtual void update(float elapsedTimeSeconds);
protected:
	// Position at which the object is spinning in place
	glm::vec3 position; 
	// axis of orbit
	glm::vec3 orbitAxis; 
	// axis of rotation
	glm::vec3 rotationAxis; 
	// rate and direction of rotation
	GLfloat oRate; 
	GLfloat rRate; 
	GLfloat revolution;
	GLfloat rotation;
};