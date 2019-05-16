/*************************************************
 *Basic
 *
 * This class implements the Bullet
 *
 * Dylan Wilson
 * Dec 11 2009
 **************************************************/
#include "Bullet.h"

#define PI 3.14159265

Bullet::Bullet()
{
	LifeTime = 250;

	Base.Color[0] = 1.0;

	Base.Color[2] = 1.0;

}
void Bullet::DrawBullet()
{
	glPushMatrix(); //Save the transformations performed thus far
	
	glTranslatef(Base.Distance[0], Base.Distance[1],Base. Distance[2]); //Move the the location

	glRotatef(Base.angle[0], 1.0f, 0.0f, 0.0f); //Rotate about the x-axis
	glRotatef(Base.angle[1], 0.0f, 1.0f, 0.0f); //Rotate about the y-axis
	glRotatef(Base.angle[2], 0.0f, 0.0f, 1.0f); //Rotate about the z-axis
	

	glTranslatef(1, 0, 0); //Move the the location so the bullets don't looke off


	glColor3f(Base.Color[0], Base.Color[1], Base.Color[2]); //set the color
	Base.Draw();
	glPopMatrix();  //Removes the matric we no longer need and restores a previous one.
}

float Bullet::GetYMove() //used to get the Y
{
	return sin(Base.angle[2]*PI/180)*.1;
}

