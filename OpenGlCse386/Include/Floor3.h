#ifndef ___FLOOR3_H___
#define ___FLOOR3_H___


#include "visualobject.h"
 
class Floor3 : public VisualObject
{
	public:
		Floor3( float height = 6.0f, float width = 8.0f, 
			  int rows = 1, int columns = 1 );

		virtual ~Floor3(void);
			
		virtual void initialize();

		virtual void draw();

		float getHeight () const { return height; }
		float getWidth () const { return width; }

		void setOrientation(vec3 pOrientation);

		vec3 getStartPoint() const { return startPoint; }
		vec3 getEndPoint() const { return endPoint; }
		vec3 getOrientation() const { return orientation; }

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

#endif // ___FLOOR3_H___

