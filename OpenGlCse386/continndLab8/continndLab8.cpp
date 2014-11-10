#include "OpenGLApplicationBase.h"
#include "glutbase.h"
#include "Floor2.h"
#include "Pyramid.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Cube.h"
#include "Cone.h"
#include "SpinnerController.h"
#include "OrbitController.h"
#include "WaypointController.h"

GLfloat x=-3.5f;
GLfloat z=-3.5f;
int leg=0;

class continndLab8 : public OpenGLApplicationBase
{
public:
	continndLab8 ()
		: figure(1)
	{
		view=0;
		rotationX=0;
		rotationY=0;
		zTrans=-12;
		vector<glm::vec3> waypoints; 
		waypoints.push_back(glm::vec3(-3.5f, -2.5f, -3.5));
		waypoints.push_back(glm::vec3(-3.5f, -2.5f, 3.5));
		waypoints.push_back(glm::vec3(3.5f, -2.5f, 3.5));
		waypoints.push_back(glm::vec3(3.5f, -2.5f, -3.5));

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

		floor = new Floor2();
		pyramid = new Pyramid();
		sphere = new Sphere();
		cylinder = new Cylinder();
		cube = new Cube();
		cone = new Cone();

		floor -> setShader(shaderProgram);
		pyramid -> setShader(shaderProgram);
		sphere -> setShader(shaderProgram);
		cylinder -> setShader(shaderProgram);
		cube -> setShader(shaderProgram);
		cone -> setShader(shaderProgram);

		pyramid -> material.setAmbientAndDiffuseMat( glm::vec4( 0.0f, 0.9f, 0.40f, 1.0f ) );
		sphere -> material.setAmbientAndDiffuseMat( glm::vec4( 0.9f, 0.1f, 0.1f, 1.0f ) );
		cylinder -> material.setAmbientAndDiffuseMat( glm::vec4( 0.0f, 0.0f, 0.9f, 1.0f ) );
		cube -> material.setAmbientAndDiffuseMat( glm::vec4( 0.0f, 0.9f, 0.0f, 1.0f ) );
		cone -> material.setAmbientAndDiffuseMat( glm::vec4( 0.9f, 0.9f, 0.0f, 1.0f ) );

		pyramid -> material.setSpecularMat( glm::vec4( 0.1f, 0.1f, 0.1f, 1.0f ) );
		//sphere -> material.setSpecularMat( glm::vec4( 0.1f, 0.1f, 0.1f, 1.0f ) );
		cylinder -> material.setSpecularMat( glm::vec4( 0.1f, 0.1f, 0.1f, 1.0f ) );
		cube -> material.setSpecularMat( glm::vec4( 0.1f, 0.1f, 0.1f, 1.0f ) );
		cone -> material.setSpecularMat( glm::vec4( 0.1f, 0.1f, 0.1f, 1.0f ) );

		//pyramid -> material.setEmissiveMat( glm::vec4( 0.1f, 0.1f, 0.1f, 1.0f ) );
		//sphere -> material.setEmissiveMat( glm::vec4( 0.1f, 0.1f, 0.1f, 1.0f ) );
		//cylinder -> material.setEmissiveMat( glm::vec4( 0.1f, 0.1f, 0.1f, 1.0f ) );
		//cube -> material.setEmissiveMat( glm::vec4( 0.1f, 0.1f, 0.1f, 1.0f ) );
		//cone -> material.setEmissiveMat( glm::vec4( 0.1f, 0.1f, 0.1f, 1.0f ) );

		addChild(floor);
		addChild(cone);
		addChild(sphere);
		addChild(cylinder);
		addChild(pyramid);
		addChild(cube);

		pyramid -> addController(new SpinnerController(
			glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 25.0f));
		sphere -> addController(new SpinnerController(
			glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), 25.0f));
		cylinder -> addController(new SpinnerController(
			glm::vec3(-3.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 25.0f));
		cone -> addController(new OrbitController(
			glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 25.0f, 100.0f));
		cube -> addController(new WaypointController(glm::vec3(-3.5f, -2.5f, -3.5f), waypoints, 5.0f));

		setupLighting(shaderProgram);
	}

	GLuint enabledLoc, directOnLoc, posOnLoc, spOnLoc;
	bool ambOn, directOn, posOn, spOn;

	void setupLighting(GLuint shaderProgram) {
		GLuint colorIntensityLoc = getUniformLocation( shaderProgram, "ambLight.colorIntensity");
		enabledLoc = getUniformLocation(shaderProgram, "ambLight.enabled");

		ambOn=true;

		glUniform4fv(colorIntensityLoc, 1, value_ptr(vec4(0.3f, 0.3f, 0.3f, 1.0f)));
		glUniform1i(enabledLoc, ambOn);

		// Get directional light locations
		GLuint directLightColorLoc = getUniformLocation( shaderProgram, "directLight.colorIntensity");
		GLuint directLightDirectLoc = getUniformLocation( shaderProgram, "directLight.direction");
		GLuint directLightSpecLoc = getUniformLocation( shaderProgram, "directLight.specularIntensity");
		directOnLoc = getUniformLocation( shaderProgram, "directLight.enabled");

		glUniform4fv(directLightColorLoc, 1, value_ptr(glm::vec4(0.75f, 0.75f, 0.75f, 1.0f)));
		glUniform3fv(directLightDirectLoc, 1, value_ptr(normalize(glm::vec3(1.0f, 1.0f, 1.0f))));
		glUniform4fv(directLightSpecLoc, 1, value_ptr(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
		directOn = true;
		glUniform1i(directOnLoc, directOn);

		// Get positional light locations
		GLuint posLightColorLoc = getUniformLocation( shaderProgram, "posLight.colorIntensity");
		GLuint posLightDirectLoc = getUniformLocation( shaderProgram, "posLight.direction");
		GLuint posLightSpecLoc = getUniformLocation( shaderProgram, "posLight.specularIntensity");
		posOnLoc = getUniformLocation( shaderProgram, "posLight.enabled");

		glUniform4fv(posLightColorLoc, 1, value_ptr(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)));
		glUniform3fv(posLightDirectLoc, 1, value_ptr(glm::vec3(0.0f, 0.2f, 0.0f)));
		glUniform4fv(posLightSpecLoc, 1, value_ptr(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
		posOn = true;
		glUniform1i(posOnLoc, posOn);

		// Get spotlight locations
		GLuint spLightColorLoc = getUniformLocation( shaderProgram, "spLight.colorIntensity");
		GLuint spLightDirectLoc = getUniformLocation( shaderProgram, "spLight.spotDirection");
		GLuint spLightPositionLoc = getUniformLocation( shaderProgram, "spLight.position");
		GLuint spLightSpecLoc = getUniformLocation( shaderProgram, "spLight.specularIntensity");
		GLuint spLightCutoffCos = getUniformLocation( shaderProgram, "spLight.spotCutoffCos");
		spOnLoc = getUniformLocation( shaderProgram, "spLight.enabled");

		glUniform4fv(spLightColorLoc, 1, value_ptr(vec4(0.05f, 0.05f, 0.05f, 1.0f)));
		glUniform3fv(spLightDirectLoc, 1, value_ptr(vec3(0.0f, -2.0f, 0.0f)));
		glUniform3fv(spLightPositionLoc, 1, value_ptr(vec3(0.0f, 2.0f, 0.0f)));
		glUniform4fv(spLightSpecLoc, 1, value_ptr(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
		glUniform1f(spLightCutoffCos, cos(glm::radians(15.0f)));
		spOn = true;
		glUniform1i(spOnLoc, spOn);
	}

	int view;
	GLfloat rotationX, rotationY, zTrans;

	void KeyboardCB(unsigned char Key, int x, int y) {
		switch(Key) {
		case 'w':
			zTrans += 0.5f;
			break;
		case 's':
			zTrans -= 0.5f;
			break;
		case '1':
			if (pyramid -> getParent() == NULL ) {
				this -> addChild(pyramid);
			}
			else {
				pyramid -> detachFromParent();
			}
			break;
		case '2':
			if (sphere -> getParent() == NULL ) {
				this -> addChild(sphere);
			}
			else {
				sphere -> detachFromParent();
			}
			break;
		case '3':
			if (cylinder -> getParent() == NULL ) {
				this -> addChild(cylinder);
			}
			else {
				cylinder -> detachFromParent();
			}
			break;
		case '4':
			if (cube -> getParent() == NULL ) {
				this -> addChild(cube);
			}
			else {
				cube -> detachFromParent();
			}
			break;
		case '5':
			if (cone -> getParent() == NULL ) {
				this -> addChild(cone);
			}
			else {
				cone -> detachFromParent();
			}
			break;
		case 'a':
			ambOn=!ambOn;
			glUniform1i(enabledLoc, ambOn);
			break;
		case 'd':
			directOn=!directOn;
			glUniform1i(directOnLoc, directOn);
			break;
		case 'p':
			posOn=!posOn;
			glUniform1i(posOnLoc, posOn);
			break;
		case 'l':
			spOn = !spOn;
			glUniform1i(spOnLoc, spOn);
		default:
			OpenGLApplicationBase::KeyboardCB(Key, x, y);
		}
	}

	virtual void initialize()
	{
		glutSpecialFunc(SpecialKeyboardCB);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glEnable( GL_DEPTH_TEST );
		setUpMenus();

		floor -> modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, 0.0f));
		cube -> modelMatrix = glm::mat4(1.0f);
		cone -> modelMatrix = glm::mat4(1.0f);
		VisualObject::initialize();
	} // end initialize

	void draw()
	{
		GLuint windowWidth = glutGet(GLUT_WINDOW_WIDTH);
		GLuint windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
		GLfloat aspect = (GLfloat)windowWidth/(GLfloat)windowHeight;
		projectionAndViewing.setProjectionMatrix(glm::perspective(45.0f, aspect, 0.1f, 100.0f));
		glViewport(0, 0, windowWidth, windowHeight);
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
				45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			projectionAndViewing.setViewMatrix(viewMatrix);
			break;
		case 3:
			viewMatrix = glm::translate(glm::mat4(1.0f), 
				glm::vec3( 0.0f, 0.0f, -10))*
				glm::rotate(glm::mat4(1.0f), 
				90.0f, glm::vec3(1.0f, 0.0f, 0.0f))*
				glm::rotate(glm::mat4(1.0f), 
				90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			projectionAndViewing.setViewMatrix(viewMatrix);
			break;
		case 4:
			viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			projectionAndViewing.setViewMatrix(viewMatrix);
			break;
		case 5:
			viewMatrix = glm::lookAt(glm::vec3(0.0f, 7.07f, 7.07f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			projectionAndViewing.setViewMatrix(viewMatrix);
			break;
		case 6:
			viewMatrix = glm::lookAt(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			projectionAndViewing.setViewMatrix(viewMatrix);
			break;
		case 7:
			glm::mat4 transView = glm::translate(glm::mat4(1.0f), glm::vec3( 0.0f, 0.0f, zTrans ));
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

	void continndLab8::setUpMenus()
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

	Floor2* floor;
	Pyramid* pyramid;
	Sphere* sphere;
	Cylinder* cylinder;
	Cube* cube;
	Cone* cone;
	GLuint createViewMenu() {
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

}; // end continndLab8

continndLab8* classPointer;

void SpecialKeyboardCB(int Key, int x, int y) {
	switch (Key) {
	case GLUT_KEY_RIGHT:
		classPointer -> rotationY += 0.5f;
		break;
	case GLUT_KEY_LEFT:
		classPointer -> rotationY -= 0.5f;
		break;
	case GLUT_KEY_UP:
		classPointer -> rotationX += 0.5f;
		break;
	case GLUT_KEY_DOWN:
		classPointer -> rotationX -= 0.5f;
		break;
	}
}

void viewMenu(int value) {
	classPointer ->  view =value;
	cout << "View point " << value << endl;
}

int main(int argc, char** argv)
{
	GLUTBaseInit(argc, argv);
	GLUTBaseCreateWindow( "CSE 386 Lab 7" );
	continndLab8 pApp;
	classPointer = &pApp;
	GLUTBaseRunApplication(&pApp);
} // end main