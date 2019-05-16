/*************************************************
 *Basic
 *
 * This class uses basic stuff needed for the hiarchy.
 * It's suppose to be inhareted.
 *
 * Dylan Wilson
 * Dec 11 2009
 **************************************************/
#ifndef BASIC_H
#define BASIC_H

#include <iostream>
#include <stdlib.h>
#include <vector>

#include <GL/glut.h>

#include "Vect.h"

using namespace std;

class Basic
{
	public:
		float angle[3]; //xyz rotations

		float Distance[3]; //XYZ location away from 0,0,0

		float Color[3]; //RGB value in that order

		Vect Movement;

		vector <Basic*> Child; //used to hold children

		float Radius;

		Basic();

		void Animate(); //Draws the object in the world

		virtual void ChangeSize(float); //Draws the object

		virtual void Move(float,float,float);
		
	protected:

		virtual void Draw(); //Draws the object
};

#endif