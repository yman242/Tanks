/*************************************************
 *Tank
 *
 * This class uses basic and block to build a tank.
 *
 * Dylan Wilson
 * Dec 11 2009
 **************************************************/
#ifndef TANK_H
#define TANK_H

#include <iostream>
#include <stdlib.h>
#include <vector>
#include "Block.h"
#include "Triangles.h"

#include <GL/glut.h>

using namespace std;

class Tank
{
	public:
		Block Base;
		Block Turret;
		Block Gun;

		Triangles Wheels[4];

		Tank();
		void DrawTank();

};
#endif