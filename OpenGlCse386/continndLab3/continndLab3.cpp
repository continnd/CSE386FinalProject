#include "OpenGLApplicationBase.h"
#include "glutbase.h"
#include "FigureOne.h"
#include "FigureTwo.h"
#include "FigureThree.h"
#include "FigureFour.h"
#include "FigureFive.h"
#include "FigureSix.h"
#include "FigureSeven.h"
class continndLab3 : public OpenGLApplicationBase
{
public:
	continndLab3 ()
		: figure(1)
	{

		// Create array of ShaderInfo structs that specifies the vertex and
		// fragment shaders to be compiled and linked into a program.
		ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, "pVS.vert" },
			{ GL_FRAGMENT_SHADER, "pFS.frag"},
			{ GL_NONE, NULL } // signals that there are no more shaders
		};
		// Read the files and create the OpenGL shader program.
		GLuint shaderProgram = BuildShaderProgram(shaders);	
		fig1.setShader(shaderProgram);
		fig2.setShader(shaderProgram);
		fig3.setShader(shaderProgram);
		fig4.setShader(shaderProgram);
		fig5.setShader(shaderProgram);
		fig6.setShader(shaderProgram);
		fig7.setShader(shaderProgram);
	}
	virtual void initialize()
	{
		fig1.initialize();
		fig2.initialize();
		fig3.initialize();
		fig4.initialize();
		fig5.initialize();
		fig6.initialize();
		fig7.initialize();
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
		case 4:
			fig4.draw();
			break;
		case 5:
			fig5.draw();
			break;
		case 6:
			fig6.draw();
			break;
		case 7:
			fig7.draw();
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
		//	GLuint menu2id = createFrontFaceMenu();
		GLuint menu3id = createPointSizeMenu();
		//	GLuint menu4id = createLineWidthMenu();
		GLuint menu5id = createAntiAliasingMenu();
		GLuint menu6id = createFrontFacingMenu();
		GLuint menu7id = createLineWidthMenu();
		// Create main menu
		topMenu = glutCreateMenu(mainMenu);
		glutAddSubMenu("Figure", menu0id);
		glutAddSubMenu("Polygon Mode", menu1id); // Attach polygon Menu
		glutAddSubMenu("Point Size", menu3id); // Attach polygon 
		glutAddSubMenu("Anti-Aliasing", menu5id); // Attach polygon Menu
		glutAddSubMenu("Front Facing", menu6id);
		glutAddSubMenu("Line Width", menu7id);
		glutAddMenuEntry("Quit", 1); // Specify identifier for "Quit"
		glutAttachMenu(GLUT_RIGHT_BUTTON); // Attach menu to right mouse button
	} //end setUpMenus

protected:
	GLint figure;
	FigureOne fig1;
	FigureTwo fig2;
	FigureThree fig3;
	FigureFour fig4;
	FigureFive fig5;
	FigureSix fig6;
	FigureSeven fig7;

	GLuint createFigureMenu(){
		GLuint menuId = glutCreateMenu(figureMenu);
		// Specify menu items and their integer identifiers
		glutAddMenuEntry("Figure 1", 1);
		glutAddMenuEntry("Figure 2", 2);
		glutAddMenuEntry("Figure 3", 3);
		glutAddMenuEntry("Figure 4", 4);
		glutAddMenuEntry("Figure 5", 5);
		glutAddMenuEntry("Figure 6", 6);
		glutAddMenuEntry("Figure 7", 7);
		return menuId;
	}

}; // end continndLab3

continndLab3* classPointer;

void figureMenu(int value)
{
	(classPointer)->figure = value;
	cout << "Drawing figure " << value << endl;
} // end figureMenu

int main(int argc, char** argv)
{
	GLUTBaseInit(argc, argv);
	GLUTBaseCreateWindow( "CSE 386 Lab 3" );
	continndLab3 pApp;
	classPointer = &pApp;
	GLUTBaseRunApplication(&pApp);
} // end main