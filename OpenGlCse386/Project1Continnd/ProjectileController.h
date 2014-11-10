#include "Controller.h"
class ProjectileController : public Controller{
public:
	// Constructor sets the position of the object,
	// the axis about which it will rotate, and the rate and direction
	// of rotation.
	ProjectileController(vec3 pos, GLfloat* gAngle, GLfloat* tAngle, GLfloat v = 1.0f);
	virtual void update(float elapsedTimeSeconds);
protected:
	// Position at which the object is spinning in place
	vec3 position; 
	vec3 vVector; 
	vec3 destVector;
};