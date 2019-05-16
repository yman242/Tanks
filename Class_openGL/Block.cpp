/*************************************************
 * Block
 *
 * This class uses basic stuff needed for the hiarchy.
 * It's suppose to be inhareted.
 *
 * Dylan Wilson
 * Dec 11 2009
 **************************************************/
#include "Block.h"

Block::Block()
{

	//Front Quad----------------------------------------
	//Top Left
	Points[0][0][0] = -1.0;//X
	Points[0][0][1] = 1.0;//Y
	Points[0][0][2] = 0.5;//Z

	//Top Right
	Points[0][1][0] = 1.0;//X
	Points[0][1][1] = 1.0;//Y
	Points[0][1][2] = 0.5;//Z

	//Bottom Right
	Points[0][2][0] = 1.0;//X
	Points[0][2][1] = 0.0;//Y
	Points[0][2][2] = 0.5;//Z

	//Bottom Left
	Points[0][3][0] = -1.0;//X
	Points[0][3][1] = 0.0;//Y
	Points[0][3][2] = 0.5;//Z


	//Left Side Quad -------------------------------------
	//Top Left
	Points[1][0][0] = -1.0;//X
	Points[1][0][1] = 1.0;//Y
	Points[1][0][2] = -0.5;//Z

	//Top Right
	Points[1][1][0] = -1.0;//X
	Points[1][1][1] = 1.0;//Y
	Points[1][1][2] = 0.5;//Z

	//Bottom Right
	Points[1][2][0] = -1.0;//X
	Points[1][2][1] = 0.0;//Y
	Points[1][2][2] = 0.5;//Z

	//Bottom Left
	Points[1][3][0] = -1.0;//X
	Points[1][3][1] = 0.0;//Y
	Points[1][3][2] = -0.5;//Z


	//Back Quad -----------------------------------------
	//Top Left
	Points[2][0][0] = -1.0;//X
	Points[2][0][1] = 1.0;//Y
	Points[2][0][2] = -0.5;//Z

	//Top Right
	Points[2][1][0] = 1.0;//X
	Points[2][1][1] = 1.0;//Y
	Points[2][1][2] = -0.5;//Z

	//Bottom Right
	Points[2][2][0] = 1.0;//X
	Points[2][2][1] = 0.0;//Y
	Points[2][2][2] =- 0.5;//Z

	//Bottom Left
	Points[2][3][0] = -1.0;//X
	Points[2][3][1] = 0.0;//Y
	Points[2][3][2] = -0.5;//Z

	//Right Side Quad -------------------------------------
	//Top Left
	Points[3][0][0] = 1.0;//X
	Points[3][0][1] = 1.0;//Y
	Points[3][0][2] = 0.5;//Z

	//Top Right
	Points[3][1][0] = 1.0;//X
	Points[3][1][1] = 1.0;//Y
	Points[3][1][2] = -0.5;//Z

	//Bottom Right
	Points[3][2][0] = 1.0;//X
	Points[3][2][1] = 0.0;//Y
	Points[3][2][2] = -0.5;//Z

	//Bottom Left
	Points[3][3][0] = 1.0;//X
	Points[3][3][1] = 0.0;//Y
	Points[3][3][2] = 0.5;//Z

	//Top Quad -------------------------------------
	//Top Left
	Points[4][0][0] = -1.0;//X
	Points[4][0][1] = 1.0;//Y
	Points[4][0][2] = -0.5;//Z

	//Top Right
	Points[4][1][0] = 1.0;//X
	Points[4][1][1] = 1.0;//Y
	Points[4][1][2] = -0.5;//Z

	//Bottom Right
	Points[4][2][0] = 1.0;//X
	Points[4][2][1] = 1.0;//Y
	Points[4][2][2] = 0.5;//Z

	//Bottom Left
	Points[4][3][0] = -1.0;//X
	Points[4][3][1] = 1.0;//Y
	Points[4][3][2] = 0.5;//Z

	//Bottom Quad -------------------------------------
	//Top Left
	Points[5][0][0] = -1.0;//X
	Points[5][0][1] = 0.0;//Y
	Points[5][0][2] = -0.5;//Z

	//Top Right
	Points[5][1][0] = 1.0;//X
	Points[5][1][1] = 0.0;//Y
	Points[5][1][2] = -0.5;//Z

	//Bottom Right
	Points[5][2][0] = 1.0;//X
	Points[5][2][1] = 0.0;//Y
	Points[5][2][2] = 0.5;//Z

	//Bottom Left
	Points[5][3][0] = -1.0;//X
	Points[5][3][1] = 0.0;//Y
	Points[5][3][2] = 0.5;//Z

	Radius = 2.23606/2;
}

void Block::Draw()
{
	for(int i=0; i<6; i++)
	{
		glBegin(GL_QUADS); //Begin quadrilateral coordinates
			
			//Cube
			glVertex3f(Points[i][0][0], Points[i][0][1], Points[i][0][2]);
			glVertex3f(Points[i][1][0], Points[i][1][1], Points[i][1][2]);
			glVertex3f(Points[i][2][0], Points[i][2][1], Points[i][2][2]);
			glVertex3f(Points[i][3][0], Points[i][3][1], Points[i][3][2]);
			
		glEnd(); //End quadrilateral coordinates
	}
	
}

void Block::ChangeSize(float Scale) //Scales the blocks
{
	for(int i=0; i<6; i++)
	{
		for(int k=0;k<4;k++)
		{
			for(int j =0; j<3; j++)
			{
				Points[i][k][j] *= Scale;
			}
		}
		
	}

	Radius *= Scale;

}

void Block::Move(float x,float y,float z) //moves the blocks for rotation reasons
{

	for(int i=0; i<6; i++)
	{
		for(int k=0;k<4;k++)
		{
			Points[i][k][0] += x;//X
			Points[i][k][1] += y;//Y
			Points[i][k][2] += z;//Z
		}
		
	}

}