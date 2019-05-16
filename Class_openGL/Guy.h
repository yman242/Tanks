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

using namespace std;



//Represents a guy
class Guy {
	//private:
	//	MD2Model* model;
	//	Terrain* terrain;
	//	float terrainScale; //The scaling factor for the terrain
	//	float x0;
	//	float z0;
	//	float animTime; //The current position in the animation of the model
	//	float radius0; //The approximate radius of the guy
	//	float speed;
	//	//The angle at which the guy is currently walking, in radians.  An angle
	//	//of 0 indicates the positive x direction, while an angle of PI / 2
	//	//indicates the positive z direction.  The angle always lies between 0
	//	//and 2 * PI.
	//	float angle;
	//	//The amount of time until step() should next be called
	//	float timeUntilNextStep;
	//	bool isTurningLeft; //Whether the guy is currently turning left
	//	float timeUntilSwitchDir; //The amount of time until switching direction
	//	
	//	//Advances the state of the guy by GUY_STEP_TIME seconds (without
	//	//altering animTime)
	//	void step() {
	//		//Update the turning direction information
	//		timeUntilSwitchDir -= GUY_STEP_TIME;
	//		while (timeUntilSwitchDir <= 0) {
	//			timeUntilSwitchDir += 20 * randomFloat() + 15;
	//			isTurningLeft = !isTurningLeft;
	//		}
	//		
	//		//Update the position and angle
	//		float maxX = terrainScale * (terrain->width() - 1) - radius0;
	//		float maxZ = terrainScale * (terrain->length() - 1) - radius0;
	//		
	//		x0 += velocityX() * GUY_STEP_TIME;
	//		z0 += velocityZ() * GUY_STEP_TIME;
	//		bool hitEdge = false;
	//		if (x0 < radius0) {
	//			x0 = radius0;
	//			hitEdge = true;
	//		}
	//		else if (x0 > maxX) {
	//			x0 = maxX;
	//			hitEdge = true;
	//		}
	//		
	//		if (z0 < radius0) {
	//			z0 = radius0;
	//			hitEdge = true;
	//		}
	//		else if (z0 > maxZ) {
	//			z0 = maxZ;
	//			hitEdge = true;
	//		}
	//		
	//		if (hitEdge) {
	//			//Turn more quickly if we've hit the edge
	//			if (isTurningLeft) {
	//				angle -= 0.5f * speed * GUY_STEP_TIME;
	//			}
	//			else {
	//				angle += 0.5f * speed * GUY_STEP_TIME;
	//			}
	//		}
	//		else if (isTurningLeft) {
	//			angle -= 0.05f * speed * GUY_STEP_TIME;
	//		}
	//		else {
	//			angle += 0.05f * speed * GUY_STEP_TIME;
	//		}
	//		
	//		while (angle > 2 * PI) {
	//			angle -= 2 * PI;
	//		}
	//		while (angle < 0) {
	//			angle += 2 * PI;
	//		}
	//	}
	//public:
	//	Guy(MD2Model* model1,
	//		Terrain* terrain1,
	//		float terrainScale1) {
	//		model = model1;
	//		terrain = terrain1;
	//		terrainScale = terrainScale1;
	//		
	//		animTime = 0;
	//		timeUntilNextStep = 0;
	//		
	//		//Initialize certain fields to random values
	//		radius0 = 0.4f * randomFloat() + 0.25f;
	//		x0 = randomFloat() *
	//			(terrainScale * (terrain->width() - 1) - radius0) + radius0;
	//		z0 = randomFloat() *
	//			(terrainScale * (terrain->length() - 1) - radius0) + radius0;
	//		speed = 1.5f * randomFloat() + 2.0f;
	//		isTurningLeft = randomFloat() < 0.5f;
	//		angle = 2 * PI * randomFloat();
	//		timeUntilSwitchDir = randomFloat() * (20 * randomFloat() + 15);
	//	}
	//	
	//	//Advances the state of the guy by the specified amount of time, by
	//	//calling step() the appropriate number of times and adjusting animTime
	//	void advance(float dt) {
	//		//Adjust animTime
	//		animTime += 0.45f * dt * speed / radius0;
	//		if (animTime > -100000000 && animTime < 1000000000) {
	//			animTime -= (int)animTime;
	//			if (animTime < 0) {
	//				animTime += 1;
	//			}
	//		}
	//		else {
	//			animTime = 0;
	//		}
	//		
	//		//Call step() the appropriate number of times
	//		while (dt > 0) {
	//			if (timeUntilNextStep < dt) {
	//				dt -= timeUntilNextStep;
	//				step();
	//				timeUntilNextStep = GUY_STEP_TIME;
	//			}
	//			else {
	//				timeUntilNextStep -= dt;
	//				dt = 0;
	//			}
	//		}
	//	}
	//	
	//	void draw() {
	//		if (model == NULL) {
	//			return;
	//		}
	//		
	//		float scale = radius0 / 2.5f;
	//		
	//		glPushMatrix();
	//		glTranslatef(x0, scale * 10.0f + y(), z0);
	//		glRotatef(90 - angle * 180 / PI, 0, 1, 0);
	//		glColor3f(1, 1, 1);
	//		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	//		glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
	//		glScalef(scale, scale, scale);
	//		model->draw(animTime);
	//		glPopMatrix();
	//	}
	//	
	//	float x() {
	//		return x0;
	//	}
	//	
	//	float z() {
	//		return z0;
	//	}
	//	
	//	//Returns the current height of the guy on the terrain
	//	float y() {
	//		return terrainScale *
	//			heightAt(terrain, x0 / terrainScale, z0 / terrainScale);
	//	}
	//	
	//	float velocityX() {
	//		return speed * cos(angle);
	//	}
	//	
	//	float velocityZ() {
	//		return speed * sin(angle);
	//	}
	//	
	//	//Returns the approximate radius of the guy
	//	float radius() {
	//		return radius0;
	//	}
	//	
	//	//Returns the angle at which the guy is currently walking, in radians.
	//	//An angle of 0 indicates the positive x direction, while an angle of
	//	//PI / 2 indicates the positive z direction.
	//	float walkAngle() {
	//		return angle;
	//	}	
	//	
	//	//Adjusts the angle at which this guy is walking in response to a
	//	//collision with the specified guy
	//	void bounceOff(Guy* otherGuy) {
	//		float vx = velocityX();
	//		float vz = velocityZ();
	//		
	//		float dx = otherGuy->x0 - x0;
	//		float dz = otherGuy->z0 - z0;
	//		float m = sqrt(dx * dx + dz * dz);
	//		dx /= m;
	//		dz /= m;
	//		
	//		float dotProduct = vx * dx + vz * dz;
	//		vx -= 2 * dotProduct * dx;
	//		vz -= 2 * dotProduct * dz;
	//		
	//		if (vx != 0 || vz != 0) {
	//			angle = atan2(vz, vx);
	//		}
	//	}
};