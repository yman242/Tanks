/*************************************************
 *Basic
 *
 * This class implements the stuff in basic.
 *
 * Dylan Wilson
 * Dec 11 2009
 **************************************************/
#include "Basic.h"

Basic::Basic()
{
	angle[0] = 0.0f;
	angle[1] = 0.0f;
	angle[2] = 0.0f;

	Distance[0] = 0.0f;
	Distance[1] = 0.0f;
	Distance[2] = 0.0f;

	Color[0] = 0.0f;
	Color[1] = 0.0f;
	Color[2] = 0.0f;

	Radius = 0;
}

void Basic::ChangeSize(float) //the groth of the x, the y and the z of all points
{

}
void Basic::Draw()
{

}

void Basic::Animate() //This is a way to draw everything with one function and a draw for each object
{
	glPushMatrix(); //Save the transformations performed thus far
	
	glTranslatef(Distance[0], Distance[1], Distance[2]); //Move the the location

	glRotatef(angle[0], 1.0f, 0.0f, 0.0f); //Rotate about the x-axis
	glRotatef(angle[1], 0.0f, 1.0f, 0.0f); //Rotate about the y-axis
	glRotatef(angle[2], 0.0f, 0.0f, 1.0f); //Rotate about the z-axis
	


	glColor3f(Color[0], Color[1], Color[2]); //set the color
	Draw();
	
	if(Child.size() != 0) //if there are children
	{
		for(int i=0;i<(int)Child.size();i++) //for every child that there is
		{
			(*Child[i]).Animate();
		}
	}
	glPopMatrix();  //Removes the matric we no longer need and restores a previous one.
}

void Basic::Move(float x,float y,float z)
{

}
