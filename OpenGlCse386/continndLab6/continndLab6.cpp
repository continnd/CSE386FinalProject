#include "OpenGLApplicationBase.h"
#include "glutbase.h"
#include "Floor.h"
#include "Pyramid.h"
#include "Controller.h"

GLfloat x=-3.5f;
GLfloat z=-3.5f;
int leg=0;

class continndLab6 : public OpenGLApplicationBase
{
public:
	continndLab6 ()
		: figure(1)
	{
		view=0;
		rotationX=0;
		rotationY=0;
		zTrans=-12;

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

		addChild(floor);
		addChild(pyramid);
		addChild(pyramid0);
		addChild(pyramid1);
		addChild(pyramid2);
		addChild(pyramid3);

		pyramid->addController( new Controller() );
	}
	int view;
	GLfloat rotationX, rotationY, zTrans;

	void KeyboardCB(unsigned char Key, int x, int y){
		switch(Key){
		case 'w':
			zTrans+=0.5f;
			break;
		case 's':
			zTrans-=0.5f;
			break;
		case 'q': case 'Q':
			glutLeaveMainLoop();
			break;
		case 'f': case 'F':
			glutFullScreenToggle();
			break;
		case 'c': case 'C':
			cout<<"Nick Contini"<<endl;
			break;
		default:
			break;
		}
	}

	virtual void initialize()
	{
		glutSpecialFunc(SpecialKeyboardCB);
		glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glEnable( GL_DEPTH_TEST );
		setUpMenus();
		floor->modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, 0.0f));
		pyramid->modelMatrix = glm::mat4(1.0f);
		pyramid0->modelMatrix = glm::mat4(1.0f);
		pyramid1->modelMatrix = glm::mat4(1.0f);
		pyramid2->modelMatrix = glm::mat4(1.0f);
		pyramid3->modelMatrix = glm::mat4(1.0f);
		VisualObject::initialize();
	} // end initialize

	void setViewPoint( ) 
	{
		glm::mat4 viewMatrix;
		switch (view) {
		case 0:
			viewMatrix = glm::translate(glm::mat4(1.0f), 
				glm::vec3( 0.0f, 0.0f, -12 ));
			projectionAndViewing.setViewMatrix(viewMatrix);
			break;
		case 1:
			viewMatrix = glm::translate(glm::mat4(1.0f),
				glm::vec3( 0.0f, 0.0f, -10));
			projectionAndViewing.setViewMatrix(viewMatrix);
			break;
		case 2:
			viewMatrix = glm::translate(glm::mat4(1.0f),
				glm::vec3( 0.0f, 0.0f, -10))*
				glm::rotate(glm::mat4(1.0f),
				45.0f, glm::vec3(1.0f,0.0f,0.0f));
			projectionAndViewing.setViewMatrix(viewMatrix);
			break;
		case 3:
			viewMatrix = glm::translate(glm::mat4(1.0f),
				glm::vec3( 0.0f, 0.0f, -10))*
				glm::rotate(glm::mat4(1.0f),
				90.0f, glm::vec3(1.0f,0.0f,0.0f))*
				glm::rotate(glm::mat4(1.0f),
				90.0f, glm::vec3(0.0f,1.0f,0.0f));
			projectionAndViewing.setViewMatrix(viewMatrix);
			break;
		case 4:
			viewMatrix = glm::lookAt(glm::vec3(0.0f,0.0f,10.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f));
			projectionAndViewing.setViewMatrix(viewMatrix);
			break;
		case 5:
			viewMatrix = glm::lookAt(glm::vec3(0.0f,7.07f,7.07f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f));
			projectionAndViewing.setViewMatrix(viewMatrix);
			break;
		case 6:
			viewMatrix = glm::lookAt(glm::vec3(0.0f,10.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(1.0f,0.0f,0.0f));
			projectionAndViewing.setViewMatrix(viewMatrix);
			break;
		case 7:
			glm::mat4 transView = glm::translate(glm::mat4(1.0f), glm::vec3( 0.0f, 0.0f,zTrans ));
			glm::mat4 rotateViewX = glm::rotate(glm::mat4(1.0f), rotationX, glm::vec3(1.0f, 0.0f, 0.0f)); 
			glm::mat4 rotateViewY = glm::rotate(glm::mat4(1.0f), rotationY, glm::vec3(0.0f, 1.0f, 0.0f));
			projectionAndViewing.setViewMatrix(transView*rotateViewX*rotateViewY);
			break;
		}
	}

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

		VisualObject::update(elapsedTimeSec);
	} // end update

	friend void viewMenu(int value);
	friend void SpecialKeyboardCB(int Key, int x, int y);

	void continndLab6::setUpMenus()
	{
		// Create main menu
		topMenu = glutCreateMenu(mainMenu);
		glutAddMenuEntry("Quit", 1); // Specify identifier for "Quit"
		glutAttachMenu(GLUT_RIGHT_BUTTON); // Attach menu to right mouse button
		GLuint menu1id = createPolygonMenu();
		GLuint menu2id = createPointSizeMenu();
		GLuint menu3id = createAntiAliasingMenu();
		GLuint menu4id = createViewMenu();
		GLuint menu6id = createFrontFacingMenu();
		GLuint menu7id = createLineWidthMenu();
		// Create main menu
		topMenu = glutCreateMenu(mainMenu);
		glutAddSubMenu("Polygon Mode", menu1id); // Attach polygon Menu
		glutAddSubMenu("Point Size", menu2id); // Attach polygon 
		glutAddSubMenu("Anti-Aliasing", menu3id); // Attach polygon Menu
		glutAddSubMenu("View", menu4id); // Attach polygon Menu
		glutAddSubMenu("Front Facing", menu6id);
		glutAddSubMenu("Line Width", menu7id);
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
	GLuint createViewMenu(){
		GLuint menuId = glutCreateMenu(viewMenu);
		glutAddMenuEntry("Default", 0);
		glutAddMenuEntry("View 1", 1);
		glutAddMenuEntry("View 2", 2);
		glutAddMenuEntry("View 3", 3);
		glutAddMenuEntry("View 4", 4);
		glutAddMenuEntry("View 5", 5);
		glutAddMenuEntry("View 6", 6);
		glutAddMenuEntry("View 7", 7);
		return menuId;
	}

}; // end continndLab6

continndLab6* classPointer;

void SpecialKeyboardCB(int Key, int x, int y){
	switch (Key) {
	case GLUT_KEY_RIGHT:
		classPointer->rotationY+=0.5f;
		break;
	case GLUT_KEY_LEFT:
		classPointer->rotationY-=0.5f;
		break;
	case GLUT_KEY_UP:
		classPointer->rotationX+=0.5f;
		break;
	case GLUT_KEY_DOWN:
		classPointer->rotationX-=0.5f;
		break;
	}
}

void viewMenu(int value){
	classPointer-> view =value;
	cout << "View point " << value << endl;
}

int main(int argc, char** argv)
{
	GLUTBaseInit(argc, argv);
	GLUTBaseCreateWindow( "CSE 386 Lab 5" );
	continndLab6 pApp;
	classPointer = &pApp;
	GLUTBaseRunApplication(&pApp);
} // end main