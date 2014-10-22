#include "Controller.h"
class WaypointController : public Controller{
public:
	// Constructor sets the position of the object,
	// the axis about which it will rotate, and the rate and direction
	// of rotation.
	WaypointController(glm::vec3 pos, 
		vector<glm::vec3> wp, GLfloat v = 1.0f, int r=1);
	virtual void update(float elapsedTimeSeconds);
	void findVelocityVector(glm::vec3 next, glm::vec3 cur);
protected:
	// Position at which the object is spinning in place
	glm::vec3 position; 
	vector <glm::vec3> waypoints;
	GLfloat rate;
	glm::vec3 vVector; 
	glm::vec3 destVector;
	int i;
	int repeat;
};