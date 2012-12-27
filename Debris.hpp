/***************************************************************************************\
| This is a piece of debris that is given an initial random force in a random direction |
| It falls with gravity and can collide with other debris passing on energy				|
|																						|
| Author: David Saxon																	|
\***************************************************************************************/
#ifndef _DEBRIS_H_
	#define _DEBRIS_H_

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL_opengl.h>

#include "Define.hpp"
using namespace std;

class Debris {
private:

	//VARIABLES
	int mode;
	GLuint tex; //the texture of the debris
	//The x and y positions
	int xPos;
	int yPos;
	//the orignal x and y positions
	int orgX;
	int orgY;
	//the point of force x and y
	int fX;
	int fY;
	//the texture coordinates
	float tX1;
	float tX2;
	float tY1;
	float tY2;
	//movement variables
	float speed; //the current speed the debris is traveling at
	float orgSpeed; //the orignal speed
	float direction; //the direction the debris is traveling in (in degrees)
	float rotation; //the current rotation of the debris
	float rotationSpeed; //the speed the debris is rotating at
	//mode
	bool pullIn; //is true when to still pull to centre in blackhole mode
	bool takeOff; ///is true when the butterfly has taken off
	int flap; //the flap rotation in butterfly mode
	bool reform; //is true when to reform in reform mode
	bool fall; //is true when to fall back

public:

	//CONSTUCTOR
	/*Creates a new piece of debris, takes a texture, the x and y positions,
	the number of debris the logo is wide and high, the index of this debris in relation
	to the logo height and width, the point of force x and y, and the mode*/
	Debris(GLuint t, float x, float y, float wc, float hc, float i, float j, float fx, float fy, int m);

	//DESTRUCTOR
	~Debris();

	//FUNCTIONS
	/*Update the debris*/
	void update();

	/*Draw the debris*/
	void draw();
};

#endif