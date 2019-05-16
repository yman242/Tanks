#include "Game.h"
#include <time.h>

void handleKeypress(unsigned char key, int x, int y);
void handleUpKeypress(unsigned char key, int x, int y);
void handleResize(int w, int h);
void drawScene();
void update(int value);


Game *myGame;

int main(int argc, char** argv)
{
	srand((unsigned)time(NULL));
	
	myGame = new Game();


	// set game object into motion
	myGame->Run(argc, argv);

	myGame->terrain = myGame->loadTerrain("heightmap.bmp", 20);

	//Set handler functions
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutKeyboardUpFunc(handleUpKeypress);
	glutTimerFunc(25,update, 0); //Add a timer

	glutMainLoop();
	return 0;
}

void handleKeypress(unsigned char key, int x, int y)
{
	myGame->handleKeypress(key, x, y);
}
void handleUpKeypress(unsigned char key, int x, int y)
{
	myGame->handleUpKeypress(key, x, y);
}
void handleResize(int w, int h)
{
	myGame->handleResize(w, h);
}
void drawScene()
{
	myGame->drawScene();
}

void update(int value)
{
	myGame->update(value);
	glutTimerFunc(25, update, 0);
}
