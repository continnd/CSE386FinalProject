#include "OpenGLApplicationBase.h"
#include "glutbase.h"
#include "Floor2.h"
#include "Pyramid.h"
#include "Sphere.h"
#include "SpinnerController.h"
#include "OrbitController.h"
#include "WaypointController.h"
#include "TiltController.h"
#include "Cylinder.h"
#include "Cube.h"
#include "Cone.h"
#include "SharedGeneralLighting.h"
#include "SpaceShip.h"
#include "Wall.h"
#include "SoundSource.h"
#include "Pig.h"
#include "UFO.h"

#define M_PI 3.1415926535897932384626433832795f

using namespace glm;
int mouse_x, mouse_y;
float lookAtAngleYZ, lookAtAngleXZ;
vec3 playerPos;

class blaseddContinndFinalProject : public OpenGLApplicationBase
{
public:
	friend void viewMenu(int value);
	friend void SpecialKeyboardCB(int Key, int x, int y);
	friend void getMousePos(int x, int y);
	Floor2* floor2;
	Wall* floor;
	Pig* pig;
	UFO* ufo;
	int view;
	GLfloat rotationX, rotationY, zTrans;
	SharedGeneralLighting generalLighting;
	SoundSource* sound;
	bool soundOn;
	bool moveForward;
	bool moveBack;
	bool moveLeft;
	bool moveRight;
	vec3 direction;
	vector<Wall*>walls;
	blaseddContinndFinalProject() : view(0), rotationX(0.0f), rotationY(0.0f), zTrans(-12.0f)
	{
		moveForward = false;
		moveBack = false;
		moveLeft = false;
		moveRight = false;
		direction = vec3(0.0f, 0.0f, -1.0f);
		lookAtAngleYZ = 0.0;
		lookAtAngleXZ = 0.0;
		playerPos = vec3(0.0f, 0.0f, 12.0f);
		floor = new Wall();
		floor->material.setTextureMapped(true);
		floor->material.setupTexture("stone.bmp");

		//sound = new SoundSource("Footsteps.wav"); 
		//sound->setLooping(true); 

		pig = new Pig();
		ufo = new UFO();

		ufo->addController(new TiltController(&view, &moveForward, &mouse_x, &mouse_y, &playerPos));


		addChild(floor);
		addChild(pig);
		addChild(ufo);
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
		floor->setShader(shaderProgram);
		ufo->setShader(shaderProgram);
		pig->setShader(shaderProgram);
		pig->setAmbientAndDiffuseMat(vec4(0.f, 0.0f, 0.0f, 1.f));
		pig->setEmissiveMat(vec4(0.f, 0.0f, .0f, 1.f));
		pig->setSpecularMat(vec4(0.f, 0.0f, .0f, 1.f));
		pig->setTextureMapped(true);
		pig->setTexture("metal.bmp");
		setupLighting(shaderProgram);
		makeWalls();		
		ufo->update(0);
		soundOn = false;
	}

	void makeWalls() {
		Wall *wall = new Wall();
		wall->setShader(shaderProgram);
		wall->modelMatrix = translate(mat4(1.0f), vec3(0.0f, -3.0f, -4.0f));
		wall->update(0);
		wall->setOrientation(vec3(1,0,0));
		addChild(wall);
		walls.push_back(wall);
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
			break;
		case '2':
			break;
		case '3':
			break;
		case '4':
			break;
		case '5':
			break;
		case 'w' :
			moveForward = true;
			if (checkWalls())
				if(view == 2)
					playerPos += .25f*normalize(vec3(sin(lookAtAngleXZ), 0.0f, -cos(lookAtAngleXZ)));
				else if(view == 1)
					playerPos += .25f*normalize(vec3(mouse_x, 0.0f, mouse_y));
			break;
		case 's':
			moveBack = true;
			if (checkWalls())
				if(view == 2)
					playerPos -= .25f*normalize(vec3(sin(lookAtAngleXZ), 0.0f, -cos(lookAtAngleXZ)));
			break;
		case 'a':
			moveLeft = true;
			if (checkWalls())
				if(view == 2)
					playerPos -= .25f*normalize(vec3(sin(lookAtAngleXZ + M_PI/2.0f), 0.0f, -cos(lookAtAngleXZ + M_PI/2.0f)));
			break;
		case 'd':
			moveRight = true;
			if (checkWalls())
				if(view == 2)
					playerPos += .25f*normalize(vec3(sin(lookAtAngleXZ + M_PI/2.0f), 0.0f, -cos(lookAtAngleXZ + M_PI/2.0f)));
			break;
		case 'j':
			lightOn = generalLighting.getEnabled( GL_LIGHT_ZERO );
			generalLighting.setEnabled( GL_LIGHT_ZERO, !lightOn );
			break;
		case 'l':
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

	void KeyboardUpCB(unsigned char Key, int x, int y) 
	{
		switch (Key) {
		case 'w' :
			moveForward = false;
			break;
		case 's':
			moveBack = false;
			break;
		case 'a':
			moveLeft = false;
			break;
		case 'd':
			moveRight = false;
			break;
		default:
			OpenGLApplicationBase::KeyboardUpCB(Key, x, y);
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
		vec3 pigFacing = playerPos - pig->getWorldPosition();
		GLfloat pigRot = atan(pigFacing.x/(pigFacing.z))*180/M_PI;
		pig->modelMatrix = rotate(mat4(1.0f), pigRot, vec3(0.0f, 1.0f, 0.0f)) * translate(mat4(1.0f), pig->getWorldPosition() + vec3(0.0f, 0.0f, 0.15f));
		float windowWidth = float(glutGet(GLUT_WINDOW_WIDTH)/2);
		float windowHeight = float(glutGet(GLUT_WINDOW_HEIGHT)/2);
		glutPassiveMotionFunc(getMousePos);
		if(view == 2)
			glutWarpPointer((int)windowWidth, (int)windowHeight);
		lookAtAngleXZ += ((mouse_x)/(windowWidth)/2.0f)*M_PI/2.0f;
		lookAtAngleYZ -= ((mouse_y)/(windowHeight)/2.0f)*M_PI/2.0f;
		if(lookAtAngleYZ > 80.0f * M_PI/180)
			lookAtAngleYZ = 80.0f * M_PI/180;
		else if(lookAtAngleYZ < -80.0f * M_PI/180)
			lookAtAngleYZ = -80.0f * M_PI/180;
		setViewPoint();
		if (checkWalls()) {
			if(view == 2 && moveForward)
				playerPos += .25f*normalize(vec3(sin(lookAtAngleXZ), 0.0f, -cos(lookAtAngleXZ)));
			else if(view == 1 && moveForward)
				playerPos += .25f*normalize(vec3(mouse_x, 0.0f, mouse_y));
			if(view == 2 && moveBack)
				playerPos -= .25f*normalize(vec3(sin(lookAtAngleXZ), 0.0f, -cos(lookAtAngleXZ)));
			if(view == 2 && moveLeft)
				playerPos -= .25f*normalize(vec3(sin(lookAtAngleXZ + M_PI/2.0f), 0.0f, -cos(lookAtAngleXZ + M_PI/2.0f)));
			if(view == 2 && moveRight)
				playerPos += .25f*normalize(vec3(sin(lookAtAngleXZ + M_PI/2.0f), 0.0f, -cos(lookAtAngleXZ + M_PI/2.0f)));
		}
		VisualObject::update(elapsedTimeSec);
	} // end update

	bool checkWalls() {
		for (int i = 0; i < walls.size(); i++) {
			Wall* wall = walls.at(i);
			// demo of wall detection... should be easy to make this work on a vector of walls.
			if (wall->getOrientation().x == 1) {
				// Facing wall head-on
				if (ufo->getWorldPosition().x > wall->getStartPoint().x &&
					ufo->getWorldPosition().x < wall->getEndPoint().x) {
						// check proximity to wall
						if (abs(wall->getStartPoint().z - ufo->getWorldPosition().z) <= 1.1f) {
							// Coming from front of wall.
							if (playerPos.z > wall->getStartPoint().z && 
								(playerPos + .25f*normalize(vec3(mouse_x, 0.0f, mouse_y))).z < wall->getStartPoint().z) {
									return false;
							}
							// Coming from behind wall
							if (playerPos.z < wall->getStartPoint().z &&
								(playerPos + .25f*normalize(vec3(mouse_x, 0.0f, mouse_y))).z > wall->getStartPoint().z) {
									return false;
							}
						}
				}
				// Coming from edge of wall...is this even likely to happen?
				else if (wall->getStartPoint().x - ufo->getWorldPosition().x <= 1.1f ||
					ufo->getWorldPosition().x - wall->getEndPoint().x <= 1.1f ) {
						// -x side of wall
						if ( (playerPos + .25f*normalize(vec3(mouse_x, 0.0f, mouse_y))).z == wall->getStartPoint().z &&
							(playerPos + .25f*normalize(vec3(mouse_x, 0.0f, mouse_y))).x > wall->getStartPoint().x) {
								return false;
						}
						if ( (playerPos + .25f*normalize(vec3(mouse_x, 0.0f, mouse_y))).z == wall->getStartPoint().z &&
							(playerPos + .25f*normalize(vec3(mouse_x, 0.0f, mouse_y))).x < wall->getEndPoint().x) {
								return false;
						}
				}
			}


			if (wall->getOrientation().z == 1) {
				// Facing wall head-on
				if (ufo->getWorldPosition().z > wall->getStartPoint().z &&
					ufo->getWorldPosition().z < wall->getEndPoint().z) {
						// check proximity to wall
						if (abs(wall->getStartPoint().x - ufo->getWorldPosition().x) <= 1.1f) {
							// Coming from front of wall.
							if (playerPos.x > wall->getStartPoint().x && 
								(playerPos + .25f*normalize(vec3(mouse_x, 0.0f, mouse_y))).x < wall->getStartPoint().x) {
									return false;
							}
							// Coming from behind wall
							if (playerPos.x < wall->getStartPoint().x &&
								(playerPos + .25f*normalize(vec3(mouse_x, 0.0f, mouse_y))).x > wall->getStartPoint().x) {
									return false;
							}
						}
				}
				// Coming from edge of wall...is this even likely to happen?
				else if (wall->getStartPoint().z - ufo->getWorldPosition().z <= 1.1f ||
					ufo->getWorldPosition().z - wall->getEndPoint().z <= 1.1f ) {
						// -x side of wall
						if ( (playerPos + .25f*normalize(vec3(mouse_x, 0.0f, mouse_y))).x == wall->getStartPoint().x &&
							(playerPos + .25f*normalize(vec3(mouse_x, 0.0f, mouse_y))).z > wall->getStartPoint().z) {
								return false;
						}
						if ( (playerPos + .25f*normalize(vec3(mouse_x, 0.0f, mouse_y))).x == wall->getStartPoint().x &&
							(playerPos + .25f*normalize(vec3(mouse_x, 0.0f, mouse_y))).z < wall->getEndPoint().z) {
								return false;
						}
				}
			}
		}
		return true;
	}

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
			viewMatrix = glm::lookAt(glm::vec3(playerPos.x, 20.f, playerPos.z), playerPos, glm::vec3(0,0,-1));
			projectionAndViewing.setViewMatrix(viewMatrix);
			break;
		case 2:
			vec3 direction = glm::vec3(sin(lookAtAngleXZ)*cos(lookAtAngleYZ), sin(lookAtAngleYZ),
				-(cos(lookAtAngleXZ) * cos(lookAtAngleYZ)));
			vec3 right = vec3(sin(lookAtAngleXZ + M_PI / 2.0f), 0.0f, -cos(lookAtAngleXZ + M_PI / 2.0f));
			viewMatrix = glm::lookAt(playerPos, playerPos + direction, vec3(0.0f, 1.0f, 0.0f));
			projectionAndViewing.setViewMatrix(viewMatrix);
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

		return menuId;
	}

};

void getMousePos(int x, int y) {
	mouse_x=x-glutGet(GLUT_WINDOW_WIDTH)/2;
	mouse_y=y-glutGet(GLUT_WINDOW_HEIGHT)/2;
}

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
	if(labClassPtr -> view == 2)
		glutSetCursor(GLUT_CURSOR_NONE);
	else {
		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	}
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
