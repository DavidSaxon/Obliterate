/**************************************************************\
| A logo is an image that can be obliterated by clicking on it |
| 															   |
| Author: David Saxon										   |
\**************************************************************/
#ifndef _LOGO_H_
	#define _LOGO_H_

#include <iostream>
#include <SDL/SDL_opengl.h>

using namespace std;

class Logo {
private:

	//VARIABLES
	GLuint tex; //the texture of the logo
	int width; //the width of the logo
	int height; //the height of the logo

public:

	//CONSTRUCTOR
	/*Creates a new logo. Takes a texture, and the width and the height*/
	Logo(GLuint t, int w, int h);

	//DESTRUCTOR
	~Logo();

	//FUNCTIONS
	/*Draws the logo in the centre of the window*/
	void draw(int x, int y);

	/*Returns the width*/
	int getWidth();

	/*Returns the height*/
	int getHeight();
	
};
#endif
