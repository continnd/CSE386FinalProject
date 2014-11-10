#include "OpenGLApplicationBase.h"
#include "glutbase.h"
#include "Floor.h"
#include "Pyramid.h"
#include "glutCube.h"
#include "glutCone.h"
#include "Torus.h"
#include "SpinnerController.h"
#include "OrbitController.h"
#include "WaypointController.h"
#include "shiftController.h"
#include "ProjectileController.h"
#include "Turret.h"
#include "font.h"
#include <string>
#include <math.h>
#include "Atom.h"

GLfloat* turrX=new GLfloat(0.0);
GLfloat* tAngle=new GLfloat(0.0);
GLfloat* gAngle=new GLfloat(0.0);
GLuint glutShaderProgram;
int breaches = 0;
int hits = 0;
bool gameOver = false;
float t = 0;
float countdown = 5;
float lastShot = 0.5;

class Project1continnd : public OpenGLApplicationBase
{
public:
	Project1continnd ()
	{
		// Create array of ShaderInfo structs that specifies the vertex and
		// fragment shaders to be compiled and linked into a program.
		ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, "pcVsUniViewProj.vert" },
			{ GL_FRAGMENT_SHADER, "pcFS.frag"},
			{ GL_NONE, NULL } // signals that there are no more shaders
		};
		ShaderInfo glutShaders[] = {
			{ GL_VERTEX_SHADER, "glutObjectUniViewProj.vert" },
			{ GL_FRAGMENT_SHADER, "glutObjectSolidColor.frag"},
			{ GL_NONE, NULL } // signals that there are no more shaders
		};
		// Read the files and create the OpenGL shader program.
		GLuint shaderProgram = BuildShaderProgram(shaders);	
		glutShaderProgram = BuildShaderProgram(glutShaders);	

		projectionAndViewing.setUniformBlockForShader(shaderProgram);
		projectionAndViewing.setUniformBlockForShader(glutShaderProgram);

		floor = new Floor();
		turret = new Turret(gAngle);
		
		floor->setShader(shaderProgram);
		turret->setShader(glutShaderProgram);

		addChild(floor);
		addChild(turret);

		turret->addController(new shiftController(vec3(0.0f, -0.7f, 10.0f), turrX, tAngle));
	}

	void shootGun() {
		glutSphere* sph;
		sph = new glutSphere(vec4(0.5f,0.5f,0.5f,1.0f),0.1f,16,32);
		sph->setShader(glutShaderProgram);
		sph->initialize();
		sph->addController(new ProjectileController(turret->getWorldPosition() + vec3(0.0f,2*RAD*sin(*gAngle*M_PI/180),-2*RAD*cos(*gAngle*M_PI/180)),gAngle,tAngle,5.0f));
		sph->update(0);
		addChild(sph);
		projectiles.push_back(sph);
	}

	void KeyboardCB(unsigned char Key, int x, int y){
		switch(Key){
		case ' ':
			if(lastShot>0.3) {
				shootGun();
				lastShot=0;
			}
			break;
		case 's':
			if(*tAngle<90)
				*tAngle+=5.0f;
			break;
		case 'd':
			if(*tAngle>-90)
				*tAngle-=5.0f;
			break;
		case 'r':
			for(unsigned int i = 0; i < projectiles.size(); i++) {
				projectiles.at(i)->detachFromParent();
			}
			projectiles.erase(projectiles.begin(), projectiles.end());
			for(unsigned int i = 0; i < enemies.size(); i++) {
				enemies.at(i).first->detachFromParent();
			}
			enemies.erase(enemies.begin(), enemies.end());
			gameOver=false;
			enemies = vector<pair<GlutObject*, bool>>();
			projectiles = vector<glutSphere*>();
			hits = 0;
			breaches = 0;
			t=0;
			countdown=5;
			*turrX=0;
			*gAngle=0;
			*tAngle=0;
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

		floor->modelMatrix = translate(mat4(1.0f), vec3(0.0f, -3.0f, 0.0f));
		VisualObject::initialize();
	} // end initialize

	void draw()
	{
		GLuint windowWidth = glutGet(GLUT_WINDOW_WIDTH);
		GLuint windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
		GLfloat aspect = (GLfloat)windowWidth/(GLfloat)windowHeight;
		projectionAndViewing.setProjectionMatrix(perspective(45.0f, aspect, 0.1f, 100.0f));
		glViewport(0,0, windowWidth, windowHeight);
		if(gameOver) {
			screenTextOutput(4*windowWidth/9, 2*windowHeight/3, "Game Over", vec4(1.0f, 0.0f, 0.0f, 1.0f), GLUT_BITMAP_TIMES_ROMAN_24);
			screenTextOutput((int)(windowWidth*((float).414)), windowHeight/2, "Enemies defeated: " + std::to_string(hits), vec4(1.0f, 0.0f, 0.0f, 1.0f), GLUT_BITMAP_TIMES_ROMAN_24);
			screenTextOutput(4*windowWidth/9, windowHeight/4, "'r' to reset", vec4(1.0f, 0.0f, 0.0f, 1.0f), GLUT_BITMAP_TIMES_ROMAN_24);
		}
		else {
			VisualObject::draw();
			screenTextOutput(0, 40, "Enemies defeated: " + std::to_string(hits), vec4(1.0f, 0.0f, 0.0f, 1.0f), GLUT_BITMAP_TIMES_ROMAN_24);
			screenTextOutput(0, windowHeight-40, "Breaches: " + std::to_string(breaches), vec4(1.0f, 0.0f, 0.0f, 1.0f), GLUT_BITMAP_TIMES_ROMAN_24);
		}
	}

	void setViewPoint( ) 
	{
		mat4 viewMatrix;
		viewMatrix = translate(mat4(1.0f), 
			vec3(-*turrX, 0.0f, -12 ));
		projectionAndViewing.setViewMatrix(viewMatrix);
	}

	void spawnEnemy() {
		GlutObject* enemy;
		int type = rand() % 4;
		float v;
		float size = (rand()%10)/((float)10.0);
		float xpos = (float)((rand()%70)/10.0-3.5);
		vector<vec3> dest;
		dest.push_back(vec3(xpos, -3.0f+size, -3.5f));
		switch(type) {
		case 0: enemy=new Torus(vec4(0.0f,0.2f,0.0f,1.0f),0.1f, size, 8, 16);
			v=0.3f;
			enemy->fixedTransformation=rotate(mat4(1.0f), 90.0f, vec3(1.0f, 0.0f, 0.0f));
			break;
		case 1: enemy=new glutCube(vec4(0.5f, 0.0f, 0.0f, 1.0f), size);
			v=0.5f;
			break;
		case 2: enemy=new glutCone(vec4(0.0f, 0.2f, 0.2f, 1.0f), size, size, 16, 32);
			v=0.9f;
			enemy->fixedTransformation=rotate(mat4(1.0f), 90.0f, vec3(1.0f, 0.0f, 0.0f));
			break;
		default:
			enemy=new Atom(size);
			v=1.5f;
		}
		enemy->setShader(glutShaderProgram);
		enemy->initialize();
		enemy->addController(new WaypointController(vec3(xpos,-3.0f+size, 16.0f), dest, v));
		enemy->update(0);
		addChild(enemy);
		enemies.push_back(pair<GlutObject*, bool>(enemy,false));
	}

	void checkHitsAndBreaches() {
		for(unsigned int i = 0; i < projectiles.size(); i++) {
			if(projectiles.at(i)->getWorldPosition().y < floor->getWorldPosition().y-1.0f) {
				projectiles.at(i)->detachFromParent();
				projectiles.erase(projectiles.begin() + i);
				break;
			}
			for(unsigned int j = 0; j < enemies.size(); j++) {
				if(glm::distance(enemies.at(j).first->getWorldPosition(), projectiles.at(i)->getWorldPosition()) <= enemies.at(j).first->getZone() + projectiles.at(i)->getZone()) {
					enemies.at(j).first->detachFromParent();
					enemies.erase(enemies.begin() + j);
					projectiles.at(i)->detachFromParent();
					projectiles.erase(projectiles.begin() + i);
					hits++;
					break;
				}
			}
		}
		for(unsigned int i = 0; i < enemies.size(); i++) {
			if(enemies.at(i).first->getWorldPosition().z >= 10.0) {
				enemies.at(i).first->detachFromParent();
				enemies.erase(enemies.begin() + i);
				break;
			}
			else if(enemies.at(i).first->getWorldPosition().z >= 3.5 && !enemies.at(i).second) {
				breaches++;
				enemies.at(i).second=true;
				break;
			}
		}
	}

	// Update scene objects inbetween frames
	virtual void update( float elapsedTimeSec )
	{ 
		static float counterStart = 7;
		counterStart = 7-t/((float)30.0);
		t+=elapsedTimeSec;
		lastShot+=elapsedTimeSec;
		setViewPoint( );
		VisualObject::update(elapsedTimeSec);
		checkHitsAndBreaches();
		if(enemies.size() == 0){
			countdown = counterStart;
			spawnEnemy();
		}
		countdown -= elapsedTimeSec;
		if(countdown < 0) {
			spawnEnemy();
			countdown = counterStart;
		}
		if(breaches>9)
			gameOver=true;
	} // end update

	friend void SpecialKeyboardCB(int Key, int x, int y);

	void Project1continnd::setUpMenus()
	{
		// Create main menu
		topMenu = glutCreateMenu(mainMenu);
		glutAddMenuEntry("Quit", 1); // Specify identifier for "Quit"
		glutAttachMenu(GLUT_RIGHT_BUTTON); // Attach menu to right mouse button
		GLuint menu1id = createPolygonMenu();
		GLuint menu2id = createPointSizeMenu();
		GLuint menu3id = createAntiAliasingMenu();
		GLuint menu6id = createFrontFacingMenu();
		GLuint menu7id = createLineWidthMenu();
		// Create main menu
		topMenu = glutCreateMenu(mainMenu);
		glutAddSubMenu("Polygon Mode", menu1id); // Attach polygon Menu
		glutAddSubMenu("Point Size", menu2id); // Attach polygon 
		glutAddSubMenu("Anti-Aliasing", menu3id); // Attach polygon Menu
		glutAddSubMenu("Front Facing", menu6id);
		glutAddSubMenu("Line Width", menu7id);
		glutAddMenuEntry("Quit", 1); // Specify identifier for "Quit"
		glutAttachMenu(GLUT_RIGHT_BUTTON); // Attach menu to right mouse button
	} //end setUpMenus


protected:
	Floor* floor;
	Turret* turret;
	vector<glutSphere*> projectiles;
	vector<pair<GlutObject*, bool>> enemies;
}; // end Project1continnd

Project1continnd* classPointer;

void SpecialKeyboardCB(int Key, int x, int y){
	switch (Key) {
	case GLUT_KEY_RIGHT:
		if(*turrX <= 3.5)
			*turrX+=0.1f;
		break;
	case GLUT_KEY_LEFT:
		if(*turrX >= -3.5)
			*turrX-=0.1f;
		break;
	case GLUT_KEY_UP:
		if(*gAngle <= 90)
			*gAngle+=5.0f;
		break;
	case GLUT_KEY_DOWN:
		if(*gAngle >= -45)
			*gAngle-=5.0f;
		break;
	}
}

void viewMenu(int value){
	cout << "View point " << value << endl;
}

int main(int argc, char** argv)
{
	GLUTBaseInit(argc, argv);
	GLUTBaseCreateWindow( "CSE 386 Project 1" );
	Project1continnd pApp;
	classPointer = &pApp;
	GLUTBaseRunApplication(&pApp);
} // end main