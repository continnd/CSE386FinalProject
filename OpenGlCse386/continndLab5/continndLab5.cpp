#include "OpenGLApplicationBase.h"
#include "glutbase.h"
#include "Floor.h"
#include "Pyramid.h"

GLfloat x=-3.5f;
GLfloat z=-3.5f;
int leg=0;

class continndLab5 : public OpenGLApplicationBase
{
public:
	continndLab5 ()
		: figure(1)
	{

		// Create array of ShaderInfo structs that specifies the vertex and
		// fragment shaders to be compiled and linked into a program.
		ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, "pcVsUniViewProj.vert" },
			{ GL_FRAGMENT_SHADER, "pcFS.frag"},
			{ GL_NONE, NULL } // signals that there are no more shaders
		};
		// Read the files and create the OpenGL shader program.
		GLuint shaderProgram = BuildShaderProgram(shaders);	

		projectionAndViewing.setUniformBlockForShader(shaderProgram);

		floor = new Floor();
		pyramid = new Pyramid();
		pyramid0 = new Pyramid();
		pyramid1 = new Pyramid(2.0f,2.0f);
		pyramid2 = new Pyramid();
		pyramid3 = new Pyramid();
		floor->setShader(shaderProgram);
		pyramid->setShader(shaderProgram);
		pyramid0->setShader(shaderProgram);
		pyramid1->setShader(shaderProgram);
		pyramid2->setShader(shaderProgram);
		pyramid3->setShader(shaderProgram);
	}
	~continndLab5()
	{
		delete floor;
		delete pyramid;
		delete pyramid0;
		delete pyramid1;
		delete pyramid2;
		delete pyramid3;
	}

	virtual void initialize()
	{
		glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glEnable( GL_DEPTH_TEST );
		setUpMenus();
		floor->initialize();
		pyramid->initialize();
		pyramid0->initialize();
		pyramid1->initialize();
		pyramid2->initialize();
		pyramid3->initialize();
		floor->modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, 0.0f));
		pyramid->modelMatrix = glm::mat4(1.0f);
		pyramid0->modelMatrix = glm::mat4(1.0f);
		pyramid1->modelMatrix = glm::mat4(1.0f);
		pyramid2->modelMatrix = glm::mat4(1.0f);
		pyramid3->modelMatrix = glm::mat4(1.0f);
	} // end initialize


	// Render scene objects
	virtual void draw()
	{
		floor->draw();
		pyramid->draw();
		pyramid0->draw();
		pyramid1->draw();
		pyramid2->draw();
		pyramid3->draw();
	} // end draw

	// Update scene objects inbetween frames
	virtual void update( float elapsedTimeSec )
	{ 
		setViewPoint( );
		floor->update(elapsedTimeSec);

		switch(leg){
		case 0:
			x+=0.1f;
			if(x>=3.4)
				leg=1;
			break;
		case 1:
			z+=0.1f;
			if(z>=3.4)
				leg=2;
			break;
		case 2:
			x-=0.1f;
			if(x<=-3.5)
				leg=3;
			break;
		case 3:
			z-=0.1f;
			if(z<=-3.5)
				leg=0;
			break;
		default:
			leg=0;
		}

		static float rotation = 0.0f;
		rotation += elapsedTimeSec * 25.0f;
		pyramid->modelMatrix = glm::translate( glm::mat4(1.0f), 
			glm::vec3(0.0f, 0.0f, 0.0f))*glm::rotate( glm::mat4(1.0f), 
			fmod(rotation, 360.0f), 
			glm::vec3(0.0f, 1.0f, 0.0f)); 

		pyramid0->modelMatrix = glm::translate( glm::mat4(1.0f), 
			glm::vec3(3.0f, 0.0f, 0.0f))*glm::rotate( glm::mat4(1.0f), 
			fmod(rotation, 360.0f), 
			glm::vec3(1.0f, 0.0f, 0.0f)); 

		pyramid1->modelMatrix = glm::translate( glm::mat4(1.0f), 
			glm::vec3(-3.0f, 0.0f, 0.0f))*glm::rotate( glm::mat4(1.0f), 
			fmod(rotation, 360.0f), 
			glm::vec3(0.0f, 0.0f, 1.0f)); 

		pyramid2->modelMatrix = glm::rotate( glm::mat4(1.0f), 
			fmod(rotation, 360.0f), 
			glm::vec3(0.0f, -1.0f, 0.0f))*glm::translate( glm::mat4(1.0f), 
			glm::vec3(0.0f, 0.0f, 10.0f))*glm::rotate( glm::mat4(1.0f), 
			fmod(10*rotation, 360.0f), 
			glm::vec3(0.0f, 0.0f, 1.0f)); 

		pyramid3->modelMatrix = glm::translate( glm::mat4(1.0f), 
			glm::vec3(x, -2.5f, z)); 

		pyramid->update(elapsedTimeSec);
		pyramid0->update(elapsedTimeSec);
		pyramid1->update(elapsedTimeSec);
		pyramid2->update(elapsedTimeSec);
		pyramid3->update(elapsedTimeSec);
	} // end update

	friend void figureMenu(int value);

	void setUpMenus()
	{
		// Create main menu
		topMenu = glutCreateMenu(mainMenu);
		glutAddMenuEntry("Quit", 1); // Specify identifier for "Quit"
		glutAttachMenu(GLUT_RIGHT_BUTTON); // Attach menu to right mouse button
		GLuint menu1id = createPolygonMenu();
		GLuint menu2id = createPointSizeMenu();
		GLuint menu3id = createAntiAliasingMenu();
		GLuint menu4id = createFrontFacingMenu();
		GLuint menu5id = createLineWidthMenu();
		// Create main menu
		topMenu = glutCreateMenu(mainMenu);
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

	Floor* floor;
	Pyramid* pyramid;
	Pyramid* pyramid0;
	Pyramid* pyramid1;
	Pyramid* pyramid2;
	Pyramid* pyramid3;

}; // end continndLab5

continndLab5* classPointer;

int main(int argc, char** argv)
{
	GLUTBaseInit(argc, argv);
	GLUTBaseCreateWindow( "CSE 386 Lab 5" );
	continndLab5 pApp;
	classPointer = &pApp;
	GLUTBaseRunApplication(&pApp);
} // end main