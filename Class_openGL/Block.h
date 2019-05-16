/*************************************************
 *Block
 *
 * This class is a basic block
 *
 * Dylan Wilson
 * Dec 11 2009
 **************************************************/
#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <stdlib.h>
#include <vector>

#include <GL/glut.h>

#include "Basic.h"


class Block: public Basic
{
	public:
		
		float Points[6][4][3]; //First number is for the quad, second for the point of the quad, the last is the XYZ value


		Block();

		virtual void Draw();

		virtual void ChangeSize(float);

		virtual void Move(float,float,float);
};
#endif