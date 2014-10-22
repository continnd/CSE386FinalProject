#include "WaypointController.h"

WaypointController::WaypointController(glm::vec3 pos, vector<glm::vec3> wp, GLfloat v, int r)
	:position(pos),
	waypoints(wp),
	rate(v),
	i(0),
	repeat(repeat)
{
	findVelocityVector(position, waypoints[0]);
}

void WaypointController::update(float elapsedTimeSeconds){
	if ( glm::distance(destVector,position) < (rate * elapsedTimeSeconds) ) {
			findVelocityVector(waypoints[(i+1)%waypoints.size()],waypoints[i]);
			i=(i+1)%waypoints.size();
	}
	position = position + rate * vVector * elapsedTimeSeconds;
	target->modelMatrix = glm::translate(glm::mat4(1.0f), position);
}

void WaypointController::findVelocityVector(glm::vec3 next, glm::vec3 cur){
	position=cur;
	destVector=next;
	vVector=glm::normalize(next-cur);
}