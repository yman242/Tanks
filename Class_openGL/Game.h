/*************************************************
 * Game
 *
 * This is the stuff needed for the main game
 *
 * Dylan Wilson
 * Dec 11 2009
 **************************************************/
#ifndef _GAME
#define _GAME

#include <iostream>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#include "imageloader.h"
#include "vec3f.h"
#include "Terrain.h"
#include "Guy.h"

#include "Tank.h"
#include "Bullet.h"
#include "Dude.h"
#include "text3d.h"

#include "inc\fmod.h"
#include "inc\fmod_errors.h"

#ifdef WIN32
	#include <windows.h>
	// automatically link to fmod library
	#pragma comment(lib,"lib/fmod.lib")
#else
	#include <wincompat.h>
#endif


#define PI 3.14159265

using namespace std;

class Game
{
private:



public:
	Game();
	void Run(int argc, char** argv);
	void handleKeypress(unsigned char key, int x, int y);
	void handleUpKeypress(unsigned char key, int x, int y);
	void initRendering();
	void handleResize(int w, int h);
	void drawScene();
	void update(int value);
	float _cameraAngle;
	float _angle;

	bool Move; //Movment bools
	bool Shoot;
	bool TurnLeft;
	bool TurnRight;
	bool MoveTurretLeft;
	bool MoveTurretRight;
	bool MoveGunUp;
	bool MoveGunDown;
	bool ShootAgain;

	int CurrentState; //Game state controls

	enum blah
	{
		InGame,
		StartScreen,
		EndScreen

	};


	char Dummy[10]; //Used for text
	int Score;
	const char* TextScore; //Text used for scoring
	const char* TextScore2; //Text used for intro and scoring
	float TextScale; //Used to scale the text

	
	Terrain* terrain; //This is the ground

	Tank tank; //This is the tank

	vector <Bullet*> Shots;
	vector <Dude*> Dudes;

	bool CollisionDudetoBull(Bullet*, Dude*); //For collisions

	Terrain* loadTerrain(const char* filename, float height);
	float heightAt(Terrain* terrain, float x, float z);
	float computeScale(const char* strs);
	void Reset();


	FSOUND_STREAM* g_mp3_stream; //For the sounds
	FSOUND_SAMPLE* Die;


	void cleanup() ;
};



#endif