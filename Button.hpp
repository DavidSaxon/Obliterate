/***************************************************\
| Is a button that returns a new state when pressed |
|													|
| Author: David Saxon								|
\***************************************************/
#ifndef _BUTTON_H_
	#define _BUTTON_H_

#include <iostream>
#include <SDL/SDL_opengl.h>

using namespace std;

class Button {
private:

	//VARIABLES
	GLuint tex;
	int xPos;
	int yPos;
	int width;
	int height;
	int mode; //the mode this button returns
	float alpha;

public:

	//CONSTRUCTOR
	/*Creates a new button takes a texture, position x and y, and a mode*/
	Button(GLuint t, int x, int y, int m);

	//DESTRUCTOR
	~Button();

	//FUNCTIONS
	/*returns a new mode if the mouse is on*/
	int mouseOn(int mx, int my);

	/*Draws the button*/
	void draw();

};

#endif