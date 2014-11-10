#include "visualobject.h"
class FigureOne :
	public VisualObject
{
public:
	FigureOne(void);
	~FigureOne(void);
	void initialize();
	void draw();
};