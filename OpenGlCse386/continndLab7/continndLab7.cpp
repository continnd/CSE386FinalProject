#include "OpenGLApplicationBase.h"
#include "glutbase.h"
#include "Floor.h"
#include "Pyramid.h"
#include "SpinnerController.h"
#include "OrbitController.h"
#include "WaypointController.h"

GLfloat x=-3.5f;
GLfloat z=-3.5f;
int leg=0;

class continndLab7 : public OpenGLApplicationBase
{
public:
	continndLab7 ()
		: figure(1)
	{
		view=0;
		rotationX=0;
		rotationY=0;
		zTrans=-12;
		vector<glm::vec3> waypoints; 
		waypoints.push_back(glm::vec3(-3.5f,-2.5f,-3.5));
		waypoints.push_back(glm::vec3(-3.5f,-2.5f,3.5));
		waypoints.push_back(glm::vec3(3.5f,-2.5f,3.5));
		waypoints.push_back(glm::vec3(3.5f,-2.5f,-3.5));

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

		pyramid->addController(new SpinnerController(
			glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f),25.0f));
		pyramid0->addController(new SpinnerController(
			glm::vec3(3.0f,0.0f,0.0f),glm::vec3(1.0f,0.0f,0.0f),25.0f));
		pyramid1->addController(new SpinnerController(
			glm::vec3(-3.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,1.0f),25.0f));
		pyramid2->addController(new OrbitController(
			glm::vec3(0.0f,0.0f,10.0f),glm::vec3(0.0f,-1.0f,0.0f),glm::vec3(0.0f,0.0f,1.0f),25.0f,100.0f));
		pyramid3->addController(new WaypointController(glm::vec3(-3.5f,-2.5f,-3.5f),waypoints,5.0f));
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
		case '1':
			if (pyramid->getParent() == NULL ) {
				this->addChild(pyramid);
			}
			else {
				pyramid->detachFromParent();
			}
			break;
		case '2':
			if (pyramid0->getParent() == NULL ) {
				this->addChild(pyramid0);
			}
			else {
				pyramid0->detachFromParent();
			}
			break;
		case '3':
			if (pyramid1->getParent() == NULL ) {
				this->addChild(pyramid1);
			}
			else {
				pyramid1->detachFromParent();
			}
			break;
		case '4':
			if (pyramid2->getParent() == NULL ) {
				this->addChild(pyramid2);
			}
			else {
				pyramid2->detachFromParent();
			}
			break;
		case '5':
			if (pyramid3->getParent() == NULL ) {
				this->addChild(pyramid3);
			}
			else {
				pyramid3->detachFromParent();
			}
			break;
		default:
			OpenGLApplicationBase::KeyboardCB(Key,x,y);
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
		pyramid2->modelMatrix = glm::mat4(1.0f);
		pyramid3->modelMatrix = glm::mat4(1.0f);
		VisualObject::initialize();
	} // end initialize
	
	void draw()
	{
		GLuint windowWidth = glutGet(GLUT_WINDOW_WIDTH);
		GLuint windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
		GLfloat aspect = (GLfloat)windowWidth/(GLfloat)2/(GLfloat)windowHeight;
		projectionAndViewing.setProjectionMatrix(glm::perspective(45.0f, aspect, 0.1f, 100.0f));
		glViewport(0,0, windowWidth/2, windowHeight);
		VisualObject::draw();
		projectionAndViewing.setProjectionMatrix(glm::ortho(-3.5f, 3.5f, -5.0f, 5.0f, 0.1f, 100.0f));
		glViewport(windowWidth/2, 0, windowWidth/2, windowHeight);
		VisualObject::draw();
	}

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
		VisualObject::update(elapsedTimeSec);
	} // end update

	friend void viewMenu(int value);
	friend void SpecialKeyboardCB(int Key, int x, int y);

	void continndLab7::setUpMenus()
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

}; // end continndLab7

continndLab7* classPointer;

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
	GLUTBaseCreateWindow( "CSE 386 Lab 7" );
	continndLab7 pApp;
	classPointer = &pApp;
	GLUTBaseRunApplication(&pApp);
} // end main