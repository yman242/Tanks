/*************************************************
 *Bullet
 *
 * This class is for a basic bullet
 *
 * Dylan Wilson
 * Dec 11 2009
 **************************************************/
#ifndef BULLET_H
#define BULLET_H

#include <iostream>
#include <stdlib.h>
#include <vector>
#include "Block.h"
#include "Triangles.h"
#include <math.h>

#include <GL/glut.h>

class Bullet
{
	public:
		Block Base;
		float LifeTime;

		Bullet();
		void DrawBullet();
		float GetYMove();
};

#endif