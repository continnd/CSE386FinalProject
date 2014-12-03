#include "Controller.h"

class LegController :
	public Controller
{
public:
	LegController(bool forward);
	virtual void update(float elapsedTimeSeconds);
protected:
	// Position at which the object is spinning in place
	GLfloat ang;
	bool forw;
};