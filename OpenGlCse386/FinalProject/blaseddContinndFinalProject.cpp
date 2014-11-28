#include "OpenGLApplicationBase.h"
#include "glutbase.h"
#include "Floor2.h"
#include "Pyramid.h"
#include "Sphere.h"
#include "SpinnerController.h"
#include "OrbitController.h"
#include "WaypointController.h"
#include "Cylinder.h"
#include "Cube.h"
#include "Cone.h"
#include "SharedGeneralLighting.h"
#include "SpaceShip.h"
#include "Wall.h"
#include "SoundSource.h"

using namespace glm;

class blaseddContinndFinalProject : public OpenGLApplicationBase
{
public:
	friend void viewMenu(int value);
	friend void SpecialKeyboardCB(int Key, int x, int y);
	Floor2* floor2;
	Pyramid* pyramid0;
	Cone *cone;
	Cube  *cube, *cube2;
	Sphere* sphere;
	Cylinder  *cylinder;
	SpaceShip* ss;
	Wall* wall;
	int view;
	GLfloat rotationX, rotationY, zTrans;
	SharedGeneralLighting generalLighting;
	SoundSource* sound;
	bool soundOn;
	blaseddContinndFinalProject() : view(0), rotationX(0.0f), rotationY(0.0f), zTrans(-12.0f)
	{
		wall = new Wall();
		wall->fixedTransformation = translate(mat4(1.0f), vec3(0.0f, -3.0f, -4.0f));
		floor2 = new Floor2();
		pyramid0 = new Pyramid();
		pyramid0->addController(new SpinnerController(glm::vec3(0.0f, 0.f, 0.f), glm::vec3(0.0f, 1.0f, 0.0f)));
		//pyramid0->material.setAmbientAndDiffuseMat( vec4( 0.80f, 0.10f, 0.80f, 1.0f ) );
		pyramid0->material.setAmbientAndDiffuseMat(vec4(1.0f, 0.0f, 0.0f, 1.0f));
		pyramid0->material.setEmissiveMat(vec4(0.2f, 0.0f, 0.0f, 1.0f));
		pyramid0->material.setTextureMapped(true);
		pyramid0->material.setupTexture("test.bmp");
		sphere = new Sphere();
		sphere->fixedTransformation = (rotate(mat4(1.0f), -90.0f, vec3(1,0,0)));
		sphere->material.setAmbientAndDiffuseMat(vec4(0.9f, 0.1f, 0.1f, 1.0f));
		sphere->material.setTextureMapped(true);
		sphere->material.setupTexture("earth.bmp");
		sphere->addController(new SpinnerController(glm::vec3(3.0f, 0.f, 0.f), glm::vec3(0.0f, 1.0f, 0.0f)));
		cylinder = new Cylinder();
		cylinder->material.setTextureMapped(true);
		cylinder->material.setupTexture("test.bmp");
		cylinder->material.setAmbientAndDiffuseMat(vec4(0.1f, 0.3f, 0.9f, 1.0f));
		cylinder->addController(new SpinnerController(glm::vec3(-3.0f, 0.0f, 0.0f),  glm::vec3(0.0f, 0.0f, 1.0f)));
		cone = new Cone();
		cone->material.setTextureMapped(true);
		cone->material.setupTexture("test.bmp");
		cone->material.setAmbientAndDiffuseMat(vec4(0.1f, 0.9f, 0.9f, 1.0f));
		cone->addController(new OrbitController(glm::vec3(10.f, 0.f, 0.f), glm::vec3(0.f, -1.f, 0.f), glm::vec3(1.f, 0.f, 0.f),35));
		cube = new Cube();
		cube->material.setAmbientAndDiffuseMat(vec4(0.1f, 0.9f, 0.1f, 1.0f));
		cube->material.setTextureMapped(true);
		cube->material.setupTexture("face.bmp");
		vector<glm::vec3> waypoints;
		waypoints.push_back(glm::vec3(-3.5f, -2.5f, 3.5f));
		waypoints.push_back(glm::vec3(3.5f, -2.5f, 3.5f));
		waypoints.push_back(glm::vec3(3.5f, -2.5f, -3.5f));
		waypoints.push_back(glm::vec3(-3.5f, -2.5f, -3.5f));
		cube->addController(new WaypointController(waypoints, 1.5f));

		cube2 = new Cube(2.0,2.0,2.0);

		cube2->material.setAmbientAndDiffuseMat(vec4(0.1f, 0.9f, 0.1f, 0.5f));
		cube2->modelMatrix = translate(mat4(1.0f), vec3(3.0f, 0.f, 0.f));


		wall->material.setTextureMapped(true);
		wall->material.setupTexture("stone.bmp");

		sound = new SoundSource("Footsteps.wav"); 
		sound->setLooping(true); 


		addChild(floor2);
		addChild(pyramid0);
		addChild(sphere);
		addChild(cylinder);
		addChild(cone);
		addChild(cube);
		addChild(wall);
		addChild(cube2);
		cone->addChild(sound);
		//sound->play();
		// Create array of ShaderInfo structs that specifies the vertex and 
		// fragment shaders to be compiled and linked into a program. 
		ShaderInfo shaders[] = { 
			{ GL_VERTEX_SHADER, "pcVsUniViewProj.vert" }, 
			{ GL_FRAGMENT_SHADER, "pfixed-function-shared-lighting-phong.frag"}, 
			{ GL_NONE, NULL } // signals that there are no more shaders 
		};
		// Read the files and create the OpenGL shader program. 
		GLuint shaderProgram = BuildShaderProgram(shaders);
		projectionAndViewing.setUniformBlockForShader(shaderProgram);
		generalLighting.setUniformBlockForShader(shaderProgram);
		floor2->setShader(shaderProgram);
		wall->setShader(shaderProgram);
		pyramid0->setShader(shaderProgram);
		sphere->setShader(shaderProgram);
		cylinder->setShader(shaderProgram);
		cone->setShader(shaderProgram);
		cube->setShader(shaderProgram);
		cube2->setShader(shaderProgram);
		setupLighting(shaderProgram);
		soundOn = false;
	}

	void setupLighting(GLuint shaderProgram) {
		// ***** Ambient Light **************
		generalLighting.setEnabled( GL_LIGHT_ZERO, true );
		generalLighting.setAmbientColor( GL_LIGHT_ZERO,
			vec4(0.2f, 0.2f, 0.2f, 1.0f));
		// ***** Directional Light ****************
		generalLighting.setEnabled( GL_LIGHT_ONE, true );
		generalLighting.setDiffuseColor( GL_LIGHT_ONE,
			vec4(0.75f, 0.75f, 0.75f, 1.0f) );
		generalLighting.setSpecularColor( GL_LIGHT_ONE,
			vec4(1.0f, 1.0f, 1.0f, 1.0f) );
		generalLighting.setPositionOrDirection( GL_LIGHT_ONE,
			vec4(1.0f, 1.0f, 1.0f, 0.0f) );
		// ***** Positional Light ***************
		generalLighting.setEnabled( GL_LIGHT_TWO, true );
		generalLighting.setDiffuseColor( GL_LIGHT_TWO,
			vec4(0.8f, 0.8f, 0.8f, 1.0f) );
		generalLighting.setSpecularColor( GL_LIGHT_TWO,
			vec4(1.0f, 1.0f, 1.0f, 1.0f) );
		generalLighting.setPositionOrDirection( GL_LIGHT_TWO,
			vec4(1.0f, 3.0f, 1.0f, 1.0f) );
		// ***** Spot Light **************
		generalLighting.setEnabled( GL_LIGHT_THREE, true );
		generalLighting.setIsSpot( GL_LIGHT_THREE, true );
		generalLighting.setDiffuseColor( GL_LIGHT_THREE,
			vec4(1.0f, 1.0f, 1.0f, 1.0f) );
		generalLighting.setSpecularColor( GL_LIGHT_THREE,
			vec4(1.0f, 1.0f, 1.0f, 1.0f) );
		generalLighting.setPositionOrDirection( GL_LIGHT_THREE,
			vec4(0.0f, 8.0f, 0.0f, 1.0f) );
		generalLighting.setSpotDirection( GL_LIGHT_THREE,
			vec3(0.0f, -1.0f, 0.0f) );
		generalLighting.setSpotCutoffCos( GL_LIGHT_THREE,
			cos(glm::radians(15.0f)) );

	}
	bool lightOn;
	void KeyboardCB(unsigned char Key, int x, int y) 
	{
		GLfloat rotationValue = 0.5f;
		switch (Key) {
		case '1':
			if (pyramid0->getParent() == NULL)
				this->addChild(pyramid0);
			else pyramid0->detachFromParent();
			break;
		case '2':
			if (sphere->getParent() == NULL)
				this->addChild(sphere);
			else sphere->detachFromParent();
			break;
		case '3':
			if (cylinder->getParent() == NULL)
				this->addChild(cylinder);
			else cylinder->detachFromParent();
			break;
		case '4':
			if (cone->getParent() == NULL)
				this->addChild(cone);
			else cone->detachFromParent();
			break;
		case '5':
			if (cube->getParent() == NULL)
				this->addChild(cube);
			else cube->detachFromParent();
			break;
		case 'w' :
			zTrans += rotationValue;
			break;
		case 's':
			zTrans -= rotationValue;
			break;
		case 'a':
			lightOn = generalLighting.getEnabled( GL_LIGHT_ZERO );
			generalLighting.setEnabled( GL_LIGHT_ZERO, !lightOn );
			break;
		case 'd':
			lightOn = generalLighting.getEnabled( GL_LIGHT_ONE );
			generalLighting.setEnabled( GL_LIGHT_ONE, !lightOn );
			break;
		case 'p':
			lightOn = generalLighting.getEnabled( GL_LIGHT_TWO );
			generalLighting.setEnabled( GL_LIGHT_TWO, !lightOn );
			break;
		case 'm':
			lightOn = generalLighting.getEnabled( GL_LIGHT_THREE );
			generalLighting.setEnabled( GL_LIGHT_THREE, !lightOn );
			break;
		case 'f': 
			soundOn = !sound->isPlaying(); 
			if (soundOn) { sound->play(); } 
			else { sound->pause(); } 
			break;
		default:
			OpenGLApplicationBase::KeyboardCB(Key, x, y);
		}
	}

	void setupMenus()
	{
		// Create polygon submenu
		GLuint menu0id = createViewMenu();
		GLuint menu1id = createPolygonMenu();
		GLuint menu2id = createFrontFaceMenu();
		GLuint menu3id = createPointSizeMenu();
		GLuint menu4id = createLineWidthMenu();
		GLuint menu5id = createAntiAliasingMenu();
		// Create main menu
		topMenu = glutCreateMenu(mainMenu);
		glutAddSubMenu("View", menu0id);
		glutAddSubMenu("Polygon Mode", menu1id);
		glutAddSubMenu("Rendered Polygon Face", menu2id);
		glutAddSubMenu("Point Size", menu3id);
		glutAddSubMenu("Line Width", menu4id);
		glutAddSubMenu("Anti-aliasing", menu5id);
		glutAddMenuEntry("Quit", 1); //Quit identifier.
		glutAttachMenu(GLUT_RIGHT_BUTTON);//Menu responds to right button
	}

	virtual void initialize()
	{
		glEnable(GL_DEPTH_TEST);
		glClearColor(.50f, 0.5f, 0.5f, 1.0f);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		setupMenus();
		floor2->initialize();
		floor2->modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, 0.0f));
		VisualObject::initialize();
		glutSpecialFunc(SpecialKeyboardCB);
	} // end initialize

	// Update scene objects inbetween frames 
	virtual void update( float elapsedTimeSec ) 
	{ 
		setViewPoint(); 
		VisualObject::update(elapsedTimeSec);
	} // end update

	virtual void setViewPoint() 
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
				glm::vec3( 0.0f, 0.0f, -10 ));
			projectionAndViewing.setViewMatrix(viewMatrix);
			break;
		case 2:
			viewMatrix = glm::translate(glm::mat4(1.0f),
				glm::vec3( 0.0f, 0.0f, -10 )) * glm::rotate(glm::mat4(1.0f), fmod(45.0f, 360.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			projectionAndViewing.setViewMatrix(viewMatrix);
			break;
		case 3:
			viewMatrix = glm::translate(glm::mat4(1.0f),
				glm::vec3( 0.0f, 0.0f, -10 )) * glm::rotate(glm::mat4(1.0f), fmod(90.0f, 360.0f), glm::vec3(1.0f, 0.0f, 0.0f))
				* glm::rotate(glm::mat4(1.0f), fmod(90.0f, 360.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			projectionAndViewing.setViewMatrix(viewMatrix);
			break;
		case 4:
			viewMatrix = glm::lookAt(glm::vec3(0.f, 0.f, 10), glm::vec3(0,0,0), glm::vec3(0, 1,0 ));
			projectionAndViewing.setViewMatrix(viewMatrix);
			break;
		case 5:
			viewMatrix = glm::lookAt(glm::vec3(0.f, 7.1f, 7.1f), glm::vec3(0,0,0), glm::vec3(0, 1,0 ));
			projectionAndViewing.setViewMatrix(viewMatrix);
			break;
		case 6:
			viewMatrix = glm::lookAt(glm::vec3(0.f, 10.f, 0), glm::vec3(0,0,0), glm::vec3(1,0, 0 ));
			projectionAndViewing.setViewMatrix(viewMatrix);
			break;
		case 7:
			glm::mat4 transView = glm::translate(glm::mat4(1.0f), glm::vec3( 0.0f, 0.0f, zTrans ));
			glm::mat4 rotateViewX = glm::rotate(glm::mat4(1.0f), rotationX, glm::vec3(1.0f, 0.0f, 0.0f));
			glm::mat4 rotateViewY = glm::rotate(glm::mat4(1.0f), rotationY, glm::vec3(0.0f, 1.0f, 0.0f));
			projectionAndViewing.setViewMatrix( transView * rotateViewX * rotateViewY );
		}

	}

	virtual void draw() {
		GLuint windowWidth = glutGet(GLUT_WINDOW_WIDTH);
		GLuint windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
		GLfloat aspect = (GLfloat)(windowWidth) / (GLfloat)windowHeight/2;

		//glViewport(0, 0, windowWidth / 2, windowHeight); 
		// Update the projection matrix in the shaders
		//projectionAndViewing.setProjectionMatrix(glm::perspective(45.0f, aspect, 0.1f, 100.f));
		VisualObject::draw();

		//glViewport(windowWidth/2, 0, windowWidth / 2, windowHeight); 
		//projectionAndViewing.setProjectionMatrix(glm::ortho(-3.5f,3.5f,-5.0f,5.0f,.1f,100.0f));
		//VisualObject::draw();
	}

	// Set the position, orientation and velocity of the listener 
	virtual void listenerUpdate( float elapsedTimeSec ) { 
		// Get the position of the viewpoint 
		mat4 viewMatrix = projectionAndViewing.getViewMatrix(); 
		vec3 viewPosition = inverse(viewMatrix)[3].xyz;
		// Initialize the "previous view position" for velocity calculations 
		static vec3 lastViewPosition = viewPosition;
		// Determine the orientation of the listener 
		vec3 viewDirection = (viewMatrix * vec4(0.0, 0.0, -1.0, 0.0)).xyz; 
		vec3 viewUp = (viewMatrix * vec4(0.0, 1.0, 0.0, 0.0)).xyz;
		// Set the listener postion 
		alListener3f(AL_POSITION, viewPosition.x, viewPosition.y, viewPosition.z );
		// Set the listener orientation 
		float orientation[] = { viewDirection.x, viewDirection.y, viewDirection.z, viewUp.x, viewUp.y, viewUp.z }; alListenerfv(AL_ORIENTATION, orientation );
		// Set listener velocity 
		if (elapsedTimeSec > 0) {
			vec3 speed = (viewPosition - lastViewPosition)/elapsedTimeSec;
			alListener3f(AL_VELOCITY, speed.x, speed.y, speed.z ); }
		// Save the position for the next listener update. 
		lastViewPosition = viewPosition;
	} // end listenerUpdate

protected:
	GLuint createViewMenu()
	{
		GLuint menuId = glutCreateMenu(viewMenu);
		// Specify menu items and their integer identifiers
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

};
blaseddContinndFinalProject* labClassPtr;
int main(int argc, char** argv) 
{
	GLUTBaseInit(argc, argv);
	GLUTBaseCreateWindow( "CSE 386 Lab 10" );

	blaseddContinndFinalProject pApp;

	labClassPtr = &pApp;
	GLUTBaseRunApplication(&pApp);

}

void viewMenu (int value)
{
	labClassPtr-> view = value;
	cout << "View point " << value << endl;
} // end viewMenu

void SpecialKeyboardCB(int Key, int x, int y)
{
	GLfloat rotationValue = 0.5f;
	switch (Key) {
	case GLUT_KEY_RIGHT:
		labClassPtr->rotationY +=rotationValue;
		break;
	case GLUT_KEY_LEFT:
		labClassPtr->rotationY -=rotationValue;
		break;
	case GLUT_KEY_UP:
		labClassPtr->rotationX += rotationValue;
		break;
	case GLUT_KEY_DOWN:
		labClassPtr->rotationX -= rotationValue;
		break;
	default:
		break;
	}
	cout << "key with ascii code " << x << " pressed." << endl;
}