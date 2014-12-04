#include "WaypointController.h"


WaypointController::WaypointController(vector<glm::vec3> wp, GLfloat r)
{
	waypoints = wp;
	position = waypoints.at(0);
	currentWaypoint = 1;
	rate = r;
	velocity = glm::normalize(waypoints.at(currentWaypoint) - position) *rate;
}




void
WaypointController::update(float elapsedTimeSec) {
	checkWaypoint(elapsedTimeSec);
	position = position + velocity * elapsedTimeSec;

	target->modelMatrix = glm::translate(glm::mat4(1.0f), position);
}

void
	WaypointController::checkWaypoint(float ets) {

		if (glm::distance(position, waypoints.at(currentWaypoint)) < rate * ets) {
			position = waypoints.at(currentWaypoint);
			currentWaypoint = (currentWaypoint + 1) % waypoints.size();

			velocity = rate * glm::normalize(waypoints.at(currentWaypoint) - position);
		}
}


