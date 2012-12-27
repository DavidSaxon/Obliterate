#include "Logo.hpp"

//CONSTRUCTOR
/*Creates a new logo. Takes a texture, and the width and the height*/
Logo::Logo(GLuint t, int w, int h) {
	tex = t;
	width = w;
	height = h;
}

//DESTRUCTOR
Logo::~Logo() {}

//FUNCTIONS
/*Draws the logo in the centre of the window*/
void Logo::draw(int x, int y) {
    glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2f(x-(width/2.0), y-(height/2.0));
    glTexCoord2f(1.0, 1.0); glVertex2f(x+(width/2.0), y-(height/2.0));
    glTexCoord2f(1.0, 0.0); glVertex2f(x+(width/2.0), y+(height/2.0));
    glTexCoord2f(0.0, 0.0); glVertex2f(x-(width/2.0), y+(height/2.0));
    glEnd();
}

/*Returns the width*/
int Logo::getWidth() {
	return width;
}

/*Returns the height*/
int Logo::getHeight() {
	return height;
}