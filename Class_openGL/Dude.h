/*************************************************
 *Dude
 *
 * This is used to hold basic data on the dudes.
 *
 * Dylan Wilson
 * Dec 11 2009
 **************************************************/
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <math.h>
#include <set>
#include <sstream>
#include <stdlib.h>
#include <vector>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "imageloader.h"
#include "md2model.h"
#include "Vect.h"

using namespace std;

class Dude
{
	public:
			MD2Model* model;
			float x;
			float z;
			float y;
			float radius;
			float speed;


			Vect Movement;

			float CurrentTimeInAnimation;



	Dude();

};