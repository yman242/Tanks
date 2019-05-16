/*************************************************
 *Dude
 *
 * This implements the stuff in Dude.h
 * Dylan Wilson
 * Dec 11 2009
 **************************************************/
#include "Dude.h"

Dude::Dude()
{
	model = MD2Model::load("blockybalboa.md2"); //This is the stuff needed for the model
	x = 0;
	z = 0;
	y = 0;
	CurrentTimeInAnimation = 0;
}