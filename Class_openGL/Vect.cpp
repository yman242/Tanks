/*************************************************
 * Vect
 *
 * This implements the stuff in Vect
 *
 * Dylan Wilson
 * Dec 11 2009
 **************************************************/
#include "Vect.h"

#define PI 3.14159265

Vect::Vect()
{
	angle = 90;
	Lenth = .1;
}

float Vect::GetX()
{
	return sin(angle*PI/180)*Lenth; //used to get a X value
}

float Vect::GetZ()
{
	return cos(angle*PI/180)*Lenth; //Used to get a Z value;
}