/*************************************************
 * Tank
 *
 * This implements the stuff in tank.
 *
 * Dylan Wilson
 * Dec 11 2009
 **************************************************/
#include "Tank.h"

Tank::Tank()
{
	Base.ChangeSize(10);
	for(int i = 0; i<4;i++) //sets the wheels
	{
		Wheels[i].Move(0,-0.5,0);
		Wheels[i].Color[1] = 1;
		Wheels[i].Color[2] = 1;
		Base.Child.push_back(&Wheels[i]);
	}
	Base.Child.push_back(&Turret);
	Turret.Child.push_back(&Gun);

	Gun.Move(1,0,0); //moves the gun so it rotates right

	

	Turret.ChangeSize(0.75*10); //This all sets and positions the peices of the tank
	Turret.Distance[1] +=1*10;

	Gun.ChangeSize(0.5*10);
	Gun.Distance[0] += .65*10;
	Gun.Distance[1] += .15*10;

	Base.Color[0] = 1.0;
	Turret.Color[1] = 1.0;
	Gun.Color[2] = 1.0;

	Wheels[0].ChangeSize(.5*10);
	Wheels[0].Distance[0] = 1.0*10;
	Wheels[0].Distance[1] = 0.20*10;
	Wheels[0].Distance[2] = 0.51*10;
	
	Wheels[1].ChangeSize(.5*10);
	Wheels[1].Distance[0] = -1.0*10;
	Wheels[1].Distance[1] = 0.20*10;
	Wheels[1].Distance[2] = 0.51*10;

	Wheels[2].ChangeSize(.5*10);
	Wheels[2].Distance[0] = 1.0*10;
	Wheels[2].Distance[1] = 0.20*10;
	Wheels[2].Distance[2] = -0.51*10;
	

	Wheels[3].ChangeSize(.5*10);
	Wheels[3].Distance[0] = -1.0*10;
	Wheels[3].Distance[1] = 0.20*10;
	Wheels[3].Distance[2] = -0.51*10;

}

void Tank::DrawTank()
{
	Base.Animate();
}