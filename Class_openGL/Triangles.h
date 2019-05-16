/*************************************************
 * triangles
 *
 * This class builds basic triangles using basic
 *
 * Dylan Wilson
 * Dec 11 2009
 **************************************************/
#ifndef TRIANGLES_H
#define TRIANGLES_H

#include <iostream>
#include <stdlib.h>
#include <vector>

#include <GL/glut.h>

#include "Basic.h"


class Triangles: public Basic
{
	public:
		float Points[3][3];

		Triangles();

		virtual void Draw();

		virtual void ChangeSize(float);

		virtual void Move(float,float,float);
};
#endif