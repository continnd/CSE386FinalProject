#pragma once
#include "visualobject.h"
class FourPointedStarFigure :
	public VisualObject
{
public:
	FourPointedStarFigure(void);
	~FourPointedStarFigure(void);
	void initialize();
	void draw();
protected:
	int numberOfIndices;
};
