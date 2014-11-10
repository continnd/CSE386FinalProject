#include "OpenGLApplicationBase.h"
#include "glutbase.h"

void buttonMotion(int x, int y)
{
	cout << "mouse motion with button "
		<< "depressed at (" << x << ", "
		<< y << ")" << endl;
} // end buttonMotion

class continndLab2 : public OpenGLApplicationBase
{
public:
	/**
	* Responds to special key presses. Called by SpecialKeyboardCB in GLUTbase
	* which is registered with GLUT by calling glutSpecialFunc.
	* @param Key Generated ASCII character for the key whose press triggered the callback.
	* @param x x-coordinate of the mouse relative to the window when the key was pressed.
	* @param y y-coordinate of the mouse relative to the window when the key was pressed.
	*/
	static void SpecialKeyboardCB(int Key, int x, int y)
	{
		cout << "key with ascii code " << x << " pressed." << endl;
	} // end SpecialKeyboardCB
	continndLab2 ()
	{
	}
	virtual void initialize()
	{
		glutPassiveMotionFunc(buttonMotion);
		glutSpecialFunc(SpecialKeyboardCB);
		setUpMenus();
		glClearColor(1.0f, 1.0f, 0.0f, 0.0f);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glEnable( GL_DEPTH_TEST );
	} // end initialize
	// Render scene objects
	virtual void draw()
	{
	} // end draw
}; // end continndLab2

int main(int argc, char** argv)
{
	GLUTBaseInit(argc, argv);
	GLUTBaseCreateWindow( "CSE 386 Lab2" );
	continndLab2 pApp;
	GLUTBaseRunApplication(&pApp);
} // end main