/*************************************************
 * Triangles
 *
 * This class uimplements the stuff in Triangles\
 *
 * Dylan Wilson
 * Dec 11 2009
 **************************************************/
#include "Triangles.h"

Triangles::Triangles()
{
	//Top Point
	Points[0][0] = 0.0f; //X
	Points[0][1] = 1.0f;//Y
	Points[0][2] = 0.0f;//Z

	//Bottom Right
	Points[1][0] = 1.0f; //X
	Points[1][1] = 0.0f;//Y
	Points[1][2] = 0.0f;//Z

	//Bottom Left
	Points[2][0] = -1.0f; //X
	Points[2][1] = 0.0f;//Y
	Points[2][2] = 0.0f;//Z

}

void Triangles::Draw()
{
	glBegin(GL_TRIANGLES);
	
	//Triangle
	glVertex3f(Points[0][0], Points[0][1], Points[0][2]);
	glVertex3f(Points[1][0], Points[1][1], Points[1][2]);
	glVertex3f(Points[2][0], Points[2][1], Points[2][2]);
	
	glEnd();
}

void Triangles::ChangeSize(float Scale)
{
	for(int i=0; i<3;i++)
	{
		for(int k =0; k<2;k++)
		{
			Points[i][k] *= Scale;
		}
	}
}

void Triangles::Move(float x, float y, float z) //Moves the triangle in space to change rotations and things
{
	for(int i=0; i<3;i++)
	{

		Points[i][0] += x;
		Points[i][1] += y;
		Points[i][2] += z;
	}
}