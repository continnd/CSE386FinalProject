#include "OpenGLApplicationBase.h"
#include "glutbase.h"
#include "FigureOne.h"
#include "InLvColoredThreeTriangleFigure.h"
#include "FourPointedStarFigure.h"

class continndLab4 : public OpenGLApplicationBase
{
public:
	continndLab4 ()
		: figure(1)
	{

		// Create array of ShaderInfo structs that specifies the vertex and
		// fragment shaders to be compiled and linked into a program.
		ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, "pcVS.vert" },
			{ GL_FRAGMENT_SHADER, "pcFS.frag"},
			{ GL_NONE, NULL } // signals that there are no more shaders
		};
		// Read the files and create the OpenGL shader program.
		GLuint shaderProgram = BuildShaderProgram(shaders);	
		fig1.setShader(shaderProgram);
		fig2.setShader(shaderProgram);
		fig3.setShader(shaderProgram);
	}
	virtual void initialize()
	{
		fig1.initialize();
		fig2.initialize();
		fig3.initialize();
		glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glEnable( GL_DEPTH_TEST );
		setUpMenus();
	} // end initialize


	// Render scene objects
	virtual void draw()
	{
		switch( figure ) {
		case 1:
			fig1.draw();
			break;
		case 2:
			fig2.draw();
			break;
		case 3:
			fig3.draw();
			break;
		default:
			cout << "Invalid figure selected." << endl;
			break;
		}
	} // end draw

	friend void figureMenu(int value);

	void setUpMenus()
	{
		// Create main menu
		topMenu = glutCreateMenu(mainMenu);
		glutAddMenuEntry("Quit", 1); // Specify identifier for "Quit"
		glutAttachMenu(GLUT_RIGHT_BUTTON); // Attach menu to right mouse button
		GLuint menu0id = createFigureMenu();
		GLuint menu1id = createPolygonMenu();
		GLuint menu2id = createPointSizeMenu();
		GLuint menu3id = createAntiAliasingMenu();
		GLuint menu4id = createFrontFacingMenu();
		GLuint menu5id = createLineWidthMenu();
		// Create main menu
		topMenu = glutCreateMenu(mainMenu);
		glutAddSubMenu("Figure", menu0id);
		glutAddSubMenu("Polygon Mode", menu1id); // Attach polygon Menu
		glutAddSubMenu("Point Size", menu2id); // Attach polygon 
		glutAddSubMenu("Anti-Aliasing", menu3id); // Attach polygon Menu
		glutAddSubMenu("Front Facing", menu4id);
		glutAddSubMenu("Line Width", menu5id);
		glutAddMenuEntry("Quit", 1); // Specify identifier for "Quit"
		glutAttachMenu(GLUT_RIGHT_BUTTON); // Attach menu to right mouse button
	} //end setUpMenus

protected:
	GLint figure;
	FigureOne fig1;
	InLvColoredThreeTriangleFigure fig2;
	FourPointedStarFigure fig3;

	GLuint createFigureMenu(){
		GLuint menuId = glutCreateMenu(figureMenu);
		// Specify menu items and their integer identifiers
		glutAddMenuEntry("Figure 1", 1);
		glutAddMenuEntry("Figure 2", 2);
		glutAddMenuEntry("Figure 3", 3);
		return menuId;
	}

}; // end continndLab4

continndLab4* classPointer;

void figureMenu(int value)
{
	(classPointer)->figure = value;
	cout << "Drawing figure " << value << endl;
} // end figureMenu

int main(int argc, char** argv)
{
	GLUTBaseInit(argc, argv);
	GLUTBaseCreateWindow( "CSE 386 Lab 3" );
	continndLab4 pApp;
	classPointer = &pApp;
	GLUTBaseRunApplication(&pApp);
} // end main