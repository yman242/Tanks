/*************************************************
 * Game
 *
 * This implements the things used in game.
 *
 * Dylan Wilson
 * Dec 11 2009
 **************************************************/
#include "Game.h"



Game::Game()
{ //Sets the starting values

	Move = false;
	Shoot = false;
	TurnLeft = false;
	TurnRight = false;
	MoveTurretLeft = false;
	MoveTurretRight = false;
	MoveGunUp = false;
	MoveGunDown = false;
	ShootAgain = true;

	tank.Base.Distance[0]=50;
	tank.Base.Distance[2]=50;


	Dudes.clear();
	for(int i = 0; i<10; i++)
	{
		Dude* Bother = new Dude();

		Bother->x += (float)(rand()%220);
		Bother->z += (float)(rand()%120 + 100);

		Bother->Movement.angle =(float)(rand()%360); //sets the locations

		Bother->model->setAnimation("run");
		Dudes.push_back(Bother);
	}

	

	Score = (int)Dudes.size();

	TextScore = "People to shoot: ";

	itoa(Score,Dummy,10); //turn the score into text

	TextScore2 = Dummy;

	CurrentState = 1;
}

void Game::Reset() //This is used to reset the game
{
	Move = false;
	Shoot = false;
	TurnLeft = false;
	TurnRight = false;
	MoveTurretLeft = false;
	MoveTurretRight = false;
	MoveGunUp = false;
	MoveGunDown = false;
	ShootAgain = true;

	tank.Base.Distance[0]=50;
	tank.Base.Distance[2]=50;

	for(int i = (int)Dudes.size()-1;i>=0;i--) //This is to prevent memory loss
	{
		delete Dudes[i]->model;
	}

	Shots.clear();
	Dudes.clear();
	for(int i = 0; i<10; i++)
	{
		Dude* Bother = new Dude();

		Bother->x += (float)(rand()%220);
		Bother->z += (float)(rand()%120 + 100);

		Bother->Movement.angle =(float)(rand()%360); //sets the locations

		Bother->model->setAnimation("run");
		Dudes.push_back(Bother);
	}

	

	Score = (int)Dudes.size();

	itoa(Score,Dummy,10); //turn the score into text

	TextScore2 = Dummy;

	CurrentState = 1;
}


void Game::Run(int argc, char** argv)
{
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	
	//Create the window
	glutCreateWindow("Tanks");
	initRendering();
	t3dInit();
	TextScale = computeScale(TextScore);

	if(FSOUND_Init(44000,64,0) == FALSE)
	{
		std::cerr << "[ERROR] Could not initialise fmod\n";
	}
	 
	 FSOUND_SetSFXMasterVolume(150);
	 Die = FSOUND_Sample_Load(FSOUND_FREE,"Ding.wav",FSOUND_2D,0,0); //Sets the sound for death of monsters

	 // attempt to open the mp3 file as a stream
	g_mp3_stream = FSOUND_Stream_Open( "I Wanted to Tell You.mp3" , FSOUND_2D , 0 , 0 );

	// make sure mp3 opened OK
	if(!g_mp3_stream) {
		std::cerr << "[ERROR] could not open file\n"; //Sets the MP3
	}

	FSOUND_Stream_Play(0,g_mp3_stream);
}

void Game::handleKeypress(unsigned char key, int x, int y)
{
		switch (key) 
		{
			case 27: //Escape key
			{
				// Stop and close the mp3 file
				FSOUND_Stream_Stop( g_mp3_stream );
				FSOUND_Stream_Close( g_mp3_stream );

				// kill off fmod
				FSOUND_Close();
				t3dCleanup();
				cleanup();
				exit(0);
			}
		}

	if(key =='d'||key=='D') //D
	{
		TurnRight = true;

	}
	if(key == 'a'||key=='A') //A
	{
		TurnLeft = true;
	}
	
	if(key=='c'||key=='C')
	{
		MoveTurretRight = true;
	}
	if(key=='z'||key=='Z')
	{	
		MoveTurretLeft = true;
	}

	if(key=='w'||key=='W')
	{
		MoveGunUp = true;
		
	}
	if(key=='s'||key=='S')
	{
		MoveGunDown =true;
	}

	if(key==' ') //Spacebar
	{
		Move = true;
	}

	if(key=='q'||key=='Q'|| key == 13)
	{
		Shoot = true;
	}
}

void Game::handleUpKeypress(unsigned char key, int x, int y) //This sets values to false if the button is released
{
	if(key =='d'||key=='D') //D
	{
		TurnRight = false;

	}
	if(key == 'a'||key=='A') //A
	{
		TurnLeft = false;
	}
	
	if(key=='c'||key=='C')
	{
		MoveTurretRight = false;
	}
	if(key=='z'||key=='Z')
	{	
		MoveTurretLeft = false;
	}

	if(key=='w'||key=='W')
	{
		MoveGunUp = false;
		
	}
	if(key=='s'||key=='S')
	{
		MoveGunDown =false;
	}

	if(key==' ') //Spacebar
	{
		Move = false;
	}

	if(key=='q'||key=='Q'|| key == 13)
	{
		Shoot = false;
		ShootAgain = true;
	}

}

void Game::initRendering()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
}

void Game::handleResize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

void Game::drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLfloat ambientColor3[] = {1.0f, 1.0f, 1.0f, .5f};
	GLfloat lightColor0[] = {0.6f, 0.6f, 0.6f, 1.0f};
	GLfloat lightPos0[] = {-0.5f, 0.8f, 0.1f, 0.0f};
	GLfloat ambientColor2[] = {.4f, .4f, .4f, .5f};
	GLfloat ambientColor[] = {1.0f, 1.0f, 1.0f, .5f};
	float scale = 20.0f / max(terrain->width() - 1, terrain->length() - 1); //That 20 use to be a 5
	switch(CurrentState)  //Used to flip between the game states
		{
			case InGame:
				glPushMatrix();
				
				glScalef(scale, scale, scale); 

				
				gluLookAt(tank.Base.Distance[0]-(sin((tank.Base.Movement.angle+tank.Turret.Movement.angle-90)*PI/180)*100),30,tank.Base.Distance[2]-(cos((tank.Base.Movement.angle+tank.Turret.Movement.angle-90)*PI/180)*100),tank.Base.Distance[0],tank.Base.Distance[1],tank.Base.Distance[2],0,1,0);
				
				
				glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

				tank.DrawTank();
				
				for each (Bullet* b in Shots)
				{
					b->DrawBullet();
				}
				
				
				glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor2);

				//enable texture
				
				glEnable(GL_TEXTURE_2D);
					
				for each (Dude* d in Dudes)
				{
					glPushMatrix();
					glColor3f(0.5f, 0.5f, 0.5f);
					glTranslatef(d->x, d->y, d->z);
					glRotatef(d->Movement.angle, 0.0f, 1.0f, 0.0f);
					glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
					glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);


					d->model->draw(d->CurrentTimeInAnimation);
					glPopMatrix();
				}

				glDisable(GL_TEXTURE_2D);

				
				glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
				glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

				
				
				glColor3f(0.3f, 0.9f, 0.0f);
				for(int z = 0; z < terrain->length() - 1; z++) {
					//Makes OpenGL draw a triangle at every three consecutive vertices
					glBegin(GL_TRIANGLE_STRIP);
					for(int x = 0; x < terrain->width(); x++) {
						Vec3f normal = terrain->getNormal(x, z);
						glNormal3f(normal[0], normal[1], normal[2]);
						glVertex3f(x, terrain->getHeight(x, z), z);
						normal = terrain->getNormal(x, z + 1);
						glNormal3f(normal[0], normal[1], normal[2]);
						glVertex3f(x, terrain->getHeight(x, z + 1), z + 1);
					}
					glEnd();
				}
				glPopMatrix();
				glPushMatrix();

				
				
				glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor3);


				glColor3f(1.0f, 1.0f, 1.0f);
				glTranslatef(1.25,1.75,-5);
				glScalef(.1, .1, .1);
				
				t3dDraw3D(TextScore,0, 0, 0);

				glTranslatef(7.5,1.75,-5);
				t3dDraw3D(TextScore2,0, 0, 0);
				glPopMatrix();
			break;

			case StartScreen:
				
				glColor3f(1.0f, 1.0f, 1.0f);
				glTranslatef(0,0,-5);
				glScalef(.1, .1, .1);
				
				t3dDraw3D("Welcome to my game!\nUse A & D to rotate the body of the tank.\n\Use Z & C to rotate the turret.\nUse W & S to move the gun up and down.\nUse Q or Enter to shoot.\nUse the space bar to move fowards\n\nThe point of the game is to kill all the people walking around.\n\nThe tank can not climb the hill that the people are on.\n\nThe background music is copyright Matthew Sweet\n\nPress space to start!",0, 0, 0);
				glPopMatrix();
			break;
			case EndScreen:
				glColor3f(1.0f, 1.0f, 1.0f);
				glTranslatef(0,0,-5);
				glScalef(.1, .1, .1);
				
				t3dDraw3D("You win!\n\nUse Esc to end and Space to play again!",0, 0, 0);
				glPopMatrix();
			break;
			
		}

	

	glutSwapBuffers();
}

void Game::update(int value)
{
	glutPostRedisplay(); //Tell GLUT that the display has changed


	if(CurrentState == 0) //if game is playing
	{
		for(int i = (int)Dudes.size()-1;i>=0;i--)
		{
			Dudes[i]->CurrentTimeInAnimation +=.05;

			Dudes[i]->y -= 5;

			if(Dudes[i]->y<heightAt(terrain,Dudes[i]->x,Dudes[i]->z)+10) //basiclly very basic gravity and ground collision
			{
				Dudes[i]->y = heightAt(terrain,Dudes[i]->x,Dudes[i]->z)+10;
			}

			Dudes[i]->x += Dudes[i]->Movement.GetX()*5; //Moves the dudes
			Dudes[i]->z += Dudes[i]->Movement.GetZ()*5;

			if(Dudes[i]->x<0 || Dudes[i]->z<100 ||Dudes[i]->x>terrain->length() ||Dudes[i]->z>terrain->width())
			{
				Dudes[i]->Movement.angle +=90; //If they hit a wall they walk a diffrent way
			}

			for(int k = (int)Shots.size()-1;k>=0;k--)
			{
				if(CollisionDudetoBull(Shots[k],Dudes[i]))
				{
					delete Dudes[i]->model; //Prevents memory leaks
					Shots.erase(Shots.begin()+k);
					Dudes.erase(Dudes.begin()+i);
					if(!Die) 
					{
						std::cerr << "[ERROR] could not open file\n";
					}

					FSOUND_PlaySound(FSOUND_FREE,Die);

					break;
				}
			}

		}

		tank.Base.Distance[1] -=5;

		//if(tank.Base.Distance[1]<heightAt(terrain,tank.Base.Distance[0],tank.Base.Distance[2]))
		if(tank.Base.Distance[1]<heightAt(terrain,tank.Base.Distance[0]+(tank.Base.Movement.GetX()*100),tank.Base.Distance[2]+(tank.Base.Movement.GetZ()*100)))
		{
			tank.Base.Distance[1] = heightAt(terrain,tank.Base.Distance[0]+(tank.Base.Movement.GetX()*100),tank.Base.Distance[2]+(tank.Base.Movement.GetZ()*100));
		}


		//Deals with the key presses
		if(TurnRight) //D
		{
			if(!(tank.Base.Distance[1]<heightAt(terrain,tank.Base.Distance[0]+(tank.Base.Movement.GetX()*100),tank.Base.Distance[2]+(tank.Base.Movement.GetZ()*100))))
			{
				tank.Base.angle[1]-=2;
				tank.Base.Movement.angle -=2;
			}
			

			//TurnRight = false;
		}
		if(TurnLeft) //A
		{

			if(!(tank.Base.Distance[1]<heightAt(terrain,tank.Base.Distance[0]+(tank.Base.Movement.GetX()*100),tank.Base.Distance[2]+(tank.Base.Movement.GetZ()*100))))
			{
				tank.Base.angle[1]+=2;
				tank.Base.Movement.angle +=2;
			}
			

			//TurnLeft = false;
		}
		
		if(MoveTurretRight) //C
		{
			tank.Turret.angle[1] -= 2;
			tank.Turret.Movement.angle -=2;	

			//MoveTurretRight = false;
		}
		if(MoveTurretLeft) //Z
		{
			
			tank.Turret.angle[1] += 2;
			tank.Turret.Movement.angle +=2;

			//MoveTurretLeft = false;
			
		}

		if(MoveGunUp)
		{
			if(tank.Gun.angle[2]< 20)
			{
				tank.Gun.angle[2] += 2;
			}
			//MoveGunUp = false;
		}
		if(MoveGunDown)
		{
			if(tank.Gun.angle[2]> -12)
			{
				tank.Gun.angle[2] -= 2;
			}	
			//MoveGunDown = false;
		}
		if(Move) //Spacebar
		{
			tank.Wheels[0].angle[2] -=10;
			tank.Wheels[1].angle[2] -=10;
			tank.Wheels[2].angle[2] -=10;
			tank.Wheels[3].angle[2] -=10;
				
			

			if(!(tank.Base.Distance[1]<heightAt(terrain,tank.Base.Distance[0]+(tank.Base.Movement.GetX()*105),tank.Base.Distance[2]+(tank.Base.Movement.GetZ()*105))))
			{
				tank.Base.Distance[0] += tank.Base.Movement.GetX()*5;
				tank.Base.Distance[2] += tank.Base.Movement.GetZ()*5;
			}


			 //Move = false;

		}

		
		if(Shoot&& ShootAgain)
		{
			Bullet* Shoot = new Bullet();

			Shoot->Base.ChangeSize(.43*10);
			Shoot->Base.Movement.angle = tank.Base.Movement.angle+tank.Turret.angle[1];
			Shoot->Base.angle[0] = tank.Base.angle[0];
			Shoot->Base.angle[1] = tank.Base.angle[1]+tank.Turret.angle[1];
			Shoot->Base.angle[2] = tank.Base.angle[2]+tank.Gun.angle[2];

			Shoot->Base.Distance[0] = (tank.Base.Distance[0]) +(tank.Turret.Movement.GetX()*.01*10); //Using the tank distance to get the position, turret movement to get what direction it's facing and .01 centers the bullet to the cannon.
			Shoot->Base.Distance[1] = (tank.Gun.Distance[1]+tank.Turret.Distance[1]+tank.Base.Distance[1])-(sin(tank.Gun.angle[2]*PI/180)*.635)*10;
			Shoot->Base.Distance[2] = (tank.Base.Distance[2]) +(tank.Turret.Movement.GetZ()*.01*10);

			Shots.push_back(Shoot);	

			ShootAgain = false;
		}

		for(int i = (int)Shots.size()-1;i>=0;i--)
		{
			bool dead = false; //The bullet's life
			Shots[i]->Base.Distance[0] += Shots[i]->Base.Movement.GetX()*50;
			Shots[i]->Base.Distance[1] += Shots[i]->GetYMove()*10;
			Shots[i]->Base.Distance[2] += Shots[i]->Base.Movement.GetZ()*50;
			


			Shots[i]->LifeTime -=1;

			if(Shots[i]->LifeTime <=0)
			{
				dead = true;
			}
			if(Shots[i]->Base.Distance[1]<heightAt(terrain,Shots[i]->Base.Distance[0],Shots[i]->Base.Distance[2])) //If the bullet hit's the ground
			{
				dead = true;
			}
			if(dead)
			{
				Shots.erase(Shots.begin()+i);
			}
		}
		Score = (int)Dudes.size(); //sets the score

		itoa(Score,Dummy,10); //turn the score into text

		TextScore2 = Dummy;

		if(Score<=0)
		{
			CurrentState=2; //all the people are dead, game over
		}
	}
	else
	{
		if(Move && CurrentState!=0) //used to start and reset the game.
		{
			Reset();
			CurrentState = 0;
		}
	}
}

bool Game::CollisionDudetoBull(Bullet* Bull, Dude* Fellow) //used to check collision between dudes and bullets
{
	if(((Bull->Base.Distance[0] - Fellow->x)*(Bull->Base.Distance[0] - Fellow->x)) + ((Bull->Base.Distance[1] - Fellow->y+5)*(Bull->Base.Distance[1] - Fellow->y+5
		)) + ((Bull->Base.Distance[2] - Fellow->z)*(Bull->Base.Distance[2] - Fellow->z)) <= ((Bull->Base.Radius *2)*(Bull->Base.Radius *2)))
	{
		return true;
	}
	return false;
}


//_____________________________________________________________________________________
//Loads a terrain from a heightmap.  The heights of the terrain range from
//-height / 2 to height / 2.
Terrain* Game::loadTerrain(const char* filename, float height) 
{
	Image* image = loadBMP(filename);
	Terrain* t = new Terrain(image->width, image->height);
	for(int y = 0; y < image->height; y++) {
		for(int x = 0; x < image->width; x++) {
			unsigned char color =
				(unsigned char)image->pixels[3 * (y * image->width + x)];
			float h = height * ((color / 255.0f) - 0.5f);
			t->setHeight(x, y, h);
		}
	}
	
	delete image;
	t->computeNormals();
	return t;
}

float Game::heightAt(Terrain* terrain, float x, float z) 
{
	//Make (x, z) lie within the bounds of the terrain
	if (x < 0) {
		x = 0;
	}
	else if (x > terrain->width() - 1) {
		x = terrain->width() - 1;
	}
	if (z < 0) {
		z = 0;
	}
	else if (z > terrain->length() - 1) {
		z = terrain->length() - 1;
	}
	
	//Compute the grid cell in which (x, z) lies and how close we are to the
	//left and outward edges
	int leftX = (int)x;
	if (leftX == terrain->width() - 1) {
		leftX--;
	}
	float fracX = x - leftX;
	
	int outZ = (int)z;
	if (outZ == terrain->width() - 1) {
		outZ--;
	}
	float fracZ = z - outZ;
	
	//Compute the four heights for the grid cell
	float h11 = terrain->getHeight(leftX, outZ);
	float h12 = terrain->getHeight(leftX, outZ + 1);
	float h21 = terrain->getHeight(leftX + 1, outZ);
	float h22 = terrain->getHeight(leftX + 1, outZ + 1);
	
	//Take a weighted average of the four heights
	return (1 - fracX) * ((1 - fracZ) * h11 + fracZ * h12) +
		fracX * ((1 - fracZ) * h21 + fracZ * h22);
}

void Game::cleanup() 
{
	delete terrain;
}
//Computes a scaling value so that the strings
float Game::computeScale(const char* strs) {
	float maxWidth = 0;
	float width = t3dDrawWidth(strs);
	if (width > maxWidth)
	{
			maxWidth = width;
	}
	
	return 2.6f / maxWidth;
}