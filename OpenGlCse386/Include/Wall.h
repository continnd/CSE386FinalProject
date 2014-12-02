#ifndef ___WALL_H___
#define ___WALL_H___


#include "visualobject.h"
 
class Wall : public VisualObject
{
	public:
		Wall( float height = 6.0f, float width = 8.0f, 
			  int rows = 1, int columns = 1 );

		virtual ~Wall(void);
			
		virtual void initialize();

		virtual void draw();

		float getHeight () const { return height; }
		float getWidth () const { return width; }

		void setOrientation(vec3 pOrientation);

		vec3 getStartPoint() const { return startPoint; }
		vec3 getEndPoint() const { return endPoint; }

	protected:
	
		void setShaderValues();

		int rows, columns;
		float height, width;

		int indiceCount;

		// Doug's modifications for determining the end points of the wall.
		vec3 endPoint, startPoint, center;
		vec3 orientation;

private:
	void applyOrientation();
};

#endif // ___WALL_H___

