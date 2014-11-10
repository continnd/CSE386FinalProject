#pragma once
#include "visualobject.h"
class InLvColoredThreeTriangleFigure :
	public VisualObject
{
public:
	InLvColoredThreeTriangleFigure(void);
	~InLvColoredThreeTriangleFigure(void);
	void initialize();
	void draw();
};

