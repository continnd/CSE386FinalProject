#pragma once
#include "Controller.h"
class WaypointController :
	public Controller
{
public:
	WaypointController(vector<glm::vec3> wp, GLfloat r = 1.0f);
	virtual void update(float elapsedTimeSeconds);
protected:
	// Position at which the object is spinning in place
	glm::vec3 position;
	// axis of rotation
	glm::vec3 velocity;
	// rate and direction of rotationakd
	GLfloat rate;
	int currentWaypoint;

	vector<glm::vec3> waypoints;

	void checkWaypoint(float ets);
};

