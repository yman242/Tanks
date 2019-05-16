/*************************************************
 * Vect
 *
 * This class build a basic vector
 *
 * Dylan Wilson
 * Dec 11 2009
 **************************************************/
#ifndef VECT_H
#define VECT_H

#include <iostream>
#include <math.h>

class Vect
{
	public:
		float angle;
		float Lenth;

		Vect();
		float GetX();
		float GetZ();

};
#endif;