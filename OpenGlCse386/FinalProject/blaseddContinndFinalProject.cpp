#include "OpenGLApplicationBase.h"
#include "glutbase.h"
#include "Floor3.h"
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
#include "font.h"

#define M_PI 3.1415926535897932384626433832795f
#define X 1
#define Z 2

using namespace glm;
int mouse_x, mouse_y;
float lookAtAngleYZ, lookAtAngleXZ;
vec3 playerPos;
bool playerLoses, playerWins;

class blaseddContinndFinalProject : public OpenGLApplicationBase
{
public:
	friend void viewMenu(int value);
	friend void SpecialKeyboardCB(int Key, int x, int y);
	friend void getMousePos(int x, int y);
	Floor3* floor;
	//Pig* pig;
	UFO* ufo;
	Cube* box;
	Pyramid* winningItem;
	int view;
	GLfloat rotationX, rotationY, zTrans;
	SharedGeneralLighting generalLighting;
	SoundSource* sound;
	bool soundOn;
	bool moveForward;
	bool moveBack;
	bool moveLeft;
	bool moveRight;
	bool pause;
	bool debug;
	vec3 direction;
	vector<Wall*>walls;
	vector<Pig*> pigs;
	GLuint shaderProgram;
	blaseddContinndFinalProject() : view(1), rotationX(0.0f), rotationY(0.0f), zTrans(-12.0f), debug(false), pause(false)
	{
		playerLoses = playerWins = false;
		moveForward = false;
		moveBack = false;
		moveLeft = false;
		moveRight = false;
		direction = vec3(0.0f, 0.0f, -1.0f);
		lookAtAngleYZ = 0.0;
		lookAtAngleXZ = 0.0;
		playerPos = vec3(0.0f, 0.0f, 12.0f);
		floor = new Floor3(90,90);
		floor->material.setTextureMapped(true);
		floor->material.setupTexture("brick.bmp");

		sound = new SoundSource("music.wav"); 
		sound->setLooping(true); 
		sound->play(); 

		ufo = new UFO();
		box = new Cube(3.75, 3, 3.75);
		ufo->addController(new TiltController(&view, &moveForward, &mouse_x, &mouse_y, &playerPos));

		winningItem = new Pyramid(3,3);

		addChild(floor);
		addChild(ufo);
		addChild(winningItem);
		addChild(box);
		// Create array of ShaderInfo structs that specifies the vertex and 
		// fragment shaders to be compiled and linked into a program. 
		ShaderInfo shaders[] = { 
			{ GL_VERTEX_SHADER, "pcVsUniViewProj.vert" }, 
			{ GL_FRAGMENT_SHADER, "pfixed-function-shared-lighting-phong.frag"}, 
			{ GL_NONE, NULL } // signals that there are no more shaders 
		};
		// Read the files and create the OpenGL shader program. 
		shaderProgram = BuildShaderProgram(shaders);
		projectionAndViewing.setUniformBlockForShader(shaderProgram);
		generalLighting.setUniformBlockForShader(shaderProgram);
		box->setShader(shaderProgram);
		floor->setShader(shaderProgram);
		floor->modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, 0.0f)) * rotate(mat4(1.0f), 90.f, vec3(-1,0,0));
		ufo->setShader(shaderProgram);
		winningItem->setShader(shaderProgram);
		winningItem->material.setTextureMapped(true);
		winningItem->material.setupTexture("test.bmp");
		winningItem->addController(new SpinnerController(vec3(-10, -1.5, -90), vec3(0,1,0)));



		setupLighting(shaderProgram);

		box->material.setAmbientAndDiffuseMat(vec4(0.1f, 0.1f, 0.5f, 0.5f));
		box->modelMatrix = translate(mat4(1.0f), vec3(-10, -1.5, -89.25));

		ufo->update(0);
		soundOn = true;

		//Build the maze
		makeWalls(vec3(-45.1f, 0.0f, 0.0f), 40.1f, X);
		makeWalls(vec3(5.0f, 0.0f, 0.0f), 40.0f, X);
		makeWalls(vec3(-45.0f, 0.0f, -90.0f), 90.1f, Z);
		makeWalls(vec3(45.0f, 0.0f, -90.0f), 90.1f, Z);
		makeWalls(vec3(-45.0f, 0.0f, -90.0f), 30.0f, X);
		makeWalls(vec3(-5.0f, 0.0f, -90.0f), 50.0f, X);
		makeWalls(vec3(35.0f, 0.0f, -90.0f), 30.0f, Z);
		makeWalls(vec3(25.0f, 0.0f, -70.0f), 30.0f, X);
		makeWalls(vec3(35.0f, 0.0f, -40.0f), 10.0f, X);
		makeWalls(vec3(15.0f, 0.0f, -30.0f), 30.0f, Z);
		makeWalls(vec3(15.0f, 0.0f, -30.0f), 10.0f, X);
		makeWalls(vec3(-45.0f, 0.0f, -20.0f), 40.0f, X);
		makeWalls(vec3(-25.0f, 0.0f, -70.0f), 60.0f, Z);
		makeWalls(vec3(-25.0f, 0.0f, -40.0f), 40.0f, X);
		makeWalls(vec3(-15,0,0), 30.f, Z);
		makeWalls(vec3(15,0,0), 30.f, Z);


		deployPig(vec3(0,0,-20));
		deployPig(vec3(-30,0,-40));
		deployPig(vec3(30,0,-85));
		deployPig(vec3(20,0,-15));
		deployPig(vec3(20,0,-65));
		deployPig(vec3(-45,0,-20));
	}

	void reset() {
		playerLoses = playerWins = false;
		moveForward = false;
		moveBack = false;
		moveLeft = false;
		moveRight = false;
		direction = vec3(0.0f, 0.0f, -1.0f);
		playerPos = vec3(0.0f, 0.0f, 12.0f);
		lookAtAngleYZ = 0.0;
		lookAtAngleXZ = 0.0;
		for (int i = 0; i < pigs.size(); i++) {
			Pig* temp = pigs.at(i);
			temp->detachFromParent();
			pigs.erase(pigs.begin()+i);
			removeChild(temp->getSerialNumber());
			delete temp;
			i--;
		}
		deployPig(vec3(0,0,-20));
		deployPig(vec3(-30,0,-40));
		deployPig(vec3(30,0,-85));
		deployPig(vec3(20,0,-15));
		deployPig(vec3(20,0,-65));

		playerPos = vec3(0.0f, 0.0f, 12.0f);
		ufo->update(0);
	}

	void makeWalls(vec3 startLocation, float length, int orientation) {
		Wall *wall = new Wall(6.0f, length);
		wall->material.setTextureMapped(true);
		wall->material.setupTexture("stone.bmp");
		wall->setShader(shaderProgram);
		vec3 midPoint = startLocation + (orientation == X ? vec3(length/2, -3.f, 0.f) :
			vec3(0.f, -3.f, length/2));
		if (orientation == Z) {
			wall->modelMatrix = translate(mat4(1.0f), midPoint) * rotate(mat4(1.0f), 90.f, vec3(0,1,0));
		}
		else wall->modelMatrix = translate(mat4(1.0f), midPoint);
		wall->update(0);
		wall->setOrientation(orientation == X ? vec3(1,0,0) : vec3(0,0,1));

		walls.push_back(wall);
		addChild(wall);
		//Back side of wall...
		wall = new Wall(6.0f, length);
		wall->material.setTextureMapped(true);
		wall->material.setupTexture("stone.bmp");
		wall->setShader(shaderProgram);
		if (orientation == Z) {
			wall->modelMatrix = translate(mat4(1.0f), midPoint) * rotate(mat4(1.0f), 270.f, vec3(0,1,0));
		}
		else wall->modelMatrix = translate(mat4(1.0f), midPoint) * rotate(mat4(1.0f), 180.f, vec3(0,1,0));;
		wall->update(0);
		wall->setOrientation(orientation == X ? vec3(1,0,0) : vec3(0,0,1));

		walls.push_back(wall);
		addChild(wall);
	}

	void deployPig(vec3 pos) {
		Pig *pig = new Pig();
		addChild(pig);
		pig->setShader(shaderProgram);
		pig->modelMatrix = translate(mat4(1.0f), pos) * translate(mat4(1.0f), vec3(0.0f, -2.0f, 0.0f));
		pig->setAmbientAndDiffuseMat(vec4(0.f, 0.0f, 0.0f, 1.f));
		pig->setEmissiveMat(vec4(0.f, 0.0f, .0f, 1.f));
		pig->setSpecularMat(vec4(0.f, 0.0f, .0f, 1.f));
		pig->setTextureMapped(true);
		pig->setTexture("metal.bmp");
		pig->initialize();
		pigs.push_back(pig);
	}

	void setupLighting(GLuint shaderProgram) {
		// ***** Ambient Light **************
		generalLighting.setEnabled( GL_LIGHT_ZERO, true );
		generalLighting.setAmbientColor( GL_LIGHT_ZERO,
			vec4(0.2f, 0.2f, 0.2f, 1.0f));
		// ***** Directional Light ****************
		generalLighting.setEnabled( GL_LIGHT_ONE, true );
		generalLighting.setDiffuseColor( GL_LIGHT_ONE,
			vec4(0.5f, 0.5f, 0.5f, 1.0f) );
		generalLighting.setSpecularColor( GL_LIGHT_ONE,
			vec4(1.0f, 1.0f, 1.0f, 1.0f) );
		generalLighting.setPositionOrDirection( GL_LIGHT_ONE,
			vec4(1.0f, 1.0f, 1.0f, 0.0f) );
		// ***** Positional Light ***************
		generalLighting.setEnabled( GL_LIGHT_TWO, false );
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
			vec4(-10.0f, 20.0f, -90.0f, 1.0f) );
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
		case 'r':
			reset();
			break;
		case 'w' :
			moveForward = true;
			break;
		case 's':
			moveBack = true;
			break;
		case 'a':
			moveLeft = true;
			break;
		case 'd':
			moveRight = true;
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
		case 'v': 
			soundOn = !sound->isPlaying(); 
			if (soundOn) { sound->play(); } 
			else { sound->pause(); } 
			break;
		case 'o':
			if (debug)
				pause = !pause;
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
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		setupMenus();
		VisualObject::initialize();
		glutSpecialFunc(SpecialKeyboardCB);
	} // end initialize

	// Update scene objects inbetween frames 
	virtual void update( float elapsedTimeSec ) 
	{ 
		if (!pause) {
			if (!playerWins && !playerLoses) {
				for (int i = 0; i < pigs.size(); i++) {
					Pig* pig = pigs.at(i);
					vec3 pigFacing = playerPos - pig->getWorldPosition();
					pigFacing = vec3(pigFacing.x, 0.0f, pigFacing.z);
					GLfloat pigRot = atan(pigFacing.x/(pigFacing.z))*180/M_PI;
					if(length(pig->getWorldPosition()-playerPos) < 10.0f && !pig->soundPlaying())
						pig->playPigSound();
					else if (length(pig->getWorldPosition()-playerPos) >= 10.0f && pig->soundPlaying())
						pig->pausePigSound();
					if(pigFacing.z < 0)
						pigRot += 180;
					pigFacing = 0.05f*normalize(pigFacing);
					checkWalls(&pigFacing, pig->getWorldPosition(), 1.5);
					pig->modelMatrix = translate(mat4(1.0f), pig->getWorldPosition()) *
						translate(mat4(1.0f), pigFacing) * rotate(mat4(1.0f), pigRot,
						vec3(0.0f, 1.0f, 0.0f));
					if(length(playerPos - pig->getWorldPosition()) <= 3.0f) {
						playerLoses = true;
						break;
					}
				}
				float windowWidth = float(glutGet(GLUT_WINDOW_WIDTH)/2);
				float windowHeight = float(glutGet(GLUT_WINDOW_HEIGHT)/2);
				glutPassiveMotionFunc(getMousePos);
				if(view == 2){
					glutWarpPointer((int)windowWidth, (int)windowHeight);
					lookAtAngleXZ += ((mouse_x)/(windowWidth)/2.0f)*M_PI/2.0f;
					lookAtAngleYZ -= ((mouse_y)/(windowHeight)/2.0f)*M_PI/2.0f;
				}
				else if(view == 1) {
					lookAtAngleXZ = acos(dot(vec3(0.0f, 0.0f, -1.0f),
						vec3(mouse_x, 0.0f, mouse_y))/(length(vec3(0.0f, 0.0f, -1.0f))
						*length(vec3(mouse_x, 0.0f, mouse_y))))*180/M_PI;
					lookAtAngleYZ = 0.0f;
				}
				else {
					lookAtAngleXZ = 0.0f;
					lookAtAngleYZ = 0.0f;
				}
				if(lookAtAngleYZ > 80.0f * M_PI/180)
					lookAtAngleYZ = 80.0f * M_PI/180;
				else if(lookAtAngleYZ < -80.0f * M_PI/180)
					lookAtAngleYZ = -80.0f * M_PI/180;
				setViewPoint();

				vec3 moveVec = vec3(0.0f, 0.0f, 0.0f);
				if(view == 2 && moveForward)
					moveVec += .25f*normalize(vec3(sin(lookAtAngleXZ), 0.0f, -cos(lookAtAngleXZ)));
				else if(view == 1 && moveForward)
					moveVec += .25f*normalize(vec3(mouse_x, 0.0f, mouse_y));
				if(view == 2 && moveBack)
					moveVec -= .25f*normalize(vec3(sin(lookAtAngleXZ), 0.0f, -cos(lookAtAngleXZ)));
				if(view == 2 && moveLeft)
					moveVec -= .25f*normalize(vec3(sin(lookAtAngleXZ + M_PI/2.0f), 0.0f, -cos(lookAtAngleXZ + M_PI/2.0f)));
				if(view == 2 && moveRight)
					moveVec += .25f*normalize(vec3(sin(lookAtAngleXZ + M_PI/2.0f), 0.0f, -cos(lookAtAngleXZ + M_PI/2.0f)));

				checkWalls(&moveVec, playerPos, 1.0f);

				playerPos += moveVec;
				VisualObject::update(elapsedTimeSec);

				if(length(playerPos - winningItem->getWorldPosition()) <= 3.5f)
					playerWins = true;
			}
		}
	} // end update

	void checkWalls(vec3* moveVec, vec3 objPos, float objRad) {
		// demo of wall detection... should be easy to make this work on a vector of walls.
		for (unsigned int i = 0; i < walls.size(); i += 2) {
			Wall* wall = walls[i];
			if (wall->getOrientation().x == 1) {
				// Facing wall head-on
				if ((objPos.x + objRad > wall->getStartPoint().x &&
					objPos.x + objRad < wall->getEndPoint().x) || 
					(objPos.x - objRad > wall->getStartPoint().x &&
					objPos.x - objRad < wall->getEndPoint().x)) {
						// check proximity to wall
						if (abs(wall->getStartPoint().z - (objPos.z + objRad)) <= 1.1f ||
							abs(wall->getStartPoint().z - (objPos.z - objRad)) <= 1.1f) {
								// Coming from front of wall.
								if (objPos.z - objRad > wall->getStartPoint().z && 
									(objPos + *moveVec).z - objRad < wall->getStartPoint().z) {
										*moveVec = vec3(moveVec->x, 0.0f, 0.0f);
								}
								// Coming from behind wall
								else if (objPos.z + objRad < wall->getStartPoint().z &&
									(objPos + *moveVec).z + objRad > wall->getStartPoint().z) {
										*moveVec = vec3(moveVec->x, 0.0f, 0.0f);
								}
						}
				}
				// Coming from edge of wall
				else if (abs(wall->getStartPoint().x - objPos.x) <= 1.1f ||
					abs(objPos.x - wall->getEndPoint().x) <= 1.1f) {
						// -x side of wall
						if ( (objPos + *moveVec).z == wall->getStartPoint().z &&
							(objPos + *moveVec).x > wall->getStartPoint().x) {
								*moveVec = vec3(0.0f, 0.0f, moveVec->z);
						}
						else if ( (objPos + *moveVec).z == wall->getStartPoint().z &&
							(objPos + *moveVec).x < wall->getEndPoint().x) {
								*moveVec = vec3(0.0f, 0.0f, moveVec->z);
						}
				}
			}

			if (wall->getOrientation().z == 1) {
				// Facing wall head-on
				if ((objPos.z + objRad > wall->getStartPoint().z &&
					objPos.z + objRad < wall->getEndPoint().z) || 
					(objPos.z - objRad > wall->getStartPoint().z &&
					objPos.z - objRad < wall->getEndPoint().z)) {
						// check proximity to wall
						if (abs(wall->getStartPoint().x - (objPos.x + objRad)) <= 1.1f ||
							abs(wall->getStartPoint().x - (objPos.x - objRad)) <= 1.1f) {
								// Coming from front of wall.
								if (objPos.x - objRad > wall->getStartPoint().x && 
									(objPos + *moveVec).x - objRad < wall->getStartPoint().x) {
										*moveVec = vec3(0.0f, 0.0f, moveVec->z);
								}
								// Coming from behind wall
								else if (objPos.x + objRad < wall->getStartPoint().x &&
									(objPos + *moveVec).x + objRad > wall->getStartPoint().x) {
										*moveVec = vec3(0.0f, 0.0f, moveVec->z);
								}
						}
				}
				// Coming from edge of wall...is this even likely to happen?
				else if (wall->getStartPoint().z - objPos.z <= 1.1f ||
					objPos.z - wall->getEndPoint().z <= 1.1f ) {
						// -x side of wall
						if ( (objPos + .25f*normalize(vec3(mouse_x, 0.0f, mouse_y))).x == wall->getStartPoint().x &&
							(objPos + .25f*normalize(vec3(mouse_x, 0.0f, mouse_y))).z > wall->getStartPoint().z) {
								*moveVec = vec3(moveVec->x, 0.0f, 0.0f);
						}
						else if ( (objPos + .25f*normalize(vec3(mouse_x, 0.0f, mouse_y))).x == wall->getStartPoint().x &&
							(objPos + .25f*normalize(vec3(mouse_x, 0.0f, mouse_y))).z < wall->getEndPoint().z) {
								*moveVec = vec3(moveVec->x, 0.0f, 0.0f);
						}
				}
			}
		}
	}

	virtual void setViewPoint() 
	{
		glm::mat4 viewMatrix;
		switch (view) {
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
		if(playerLoses) {
			screenTextOutput(windowWidth/2 - 50, windowHeight/2, "YOU LOSE!", vec4(0.0f, 0.0f, 0.0f, 1.0f));
		} 
		else if(playerWins) {
			screenTextOutput(windowWidth/2 - 40, windowHeight/2, "YOU WIN!", vec4(0.0f, 0.0f, 0.0f, 1.0f));
		}else {
			if (view==1) {
				screenTextOutput(20,20, "Move by pressing the w key and steer with the mouse.", vec4(1,1,1,1));
			}
			else {
				screenTextOutput(20,20, "Use the mouse to look around. Movement is typical WASD key setup.", vec4(1,1,1,1));
			}
			VisualObject::draw();
		}
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
		float orientation[] = { viewDirection.x, viewDirection.y, viewDirection.z,
			viewUp.x, viewUp.y, viewUp.z }; alListenerfv(AL_ORIENTATION, orientation );
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
		//glutAddMenuEntry("Default", 0);
		glutAddMenuEntry("Overhead", 1);
		glutAddMenuEntry("First-person", 2);

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
	GLUTBaseCreateWindow( "Blase/Contini Final Project" );

	blaseddContinndFinalProject pApp;

	labClassPtr = &pApp;
	GLUTBaseRunApplication(&pApp);

}

void viewMenu (int value)
{
	labClassPtr-> view = value;
	cout << "View point " << value << endl;
	if(labClassPtr -> view == 2){
		glutSetCursor(GLUT_CURSOR_NONE);
		glutWarpPointer((int)glutGet(GLUT_WINDOW_WIDTH)/2, (int)glutGet(GLUT_WINDOW_HEIGHT)/2);
	}
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
