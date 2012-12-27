#include "Button.hpp"

//CONSTRUCTOR
/*Creates a new button takes a texture, position x and y, and a mode*/
Button::Button(GLuint t, int x, int y, int m) {
	tex = t;
	xPos = x;
	yPos = y;
	mode = m;
	width = 200;
	height = 65;
	alpha = 0.0f;
}

//DESTRUCTOR
Button::~Button() {}

//FUNCTIONS
/*returns a new mode if the mouse is on*/
int Button::mouseOn(int mx, int my) {
	if (mx > xPos && mx < xPos+width && my > yPos && my < yPos+height) {
		alpha = 1.0f;
		return mode;
	}
	return -1;
}

/*Draws the button*/
void Button::draw() {
    glPushMatrix();

    glTranslatef(xPos, yPos, 0);

    glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2f(0,     0);
    glTexCoord2f(1.0, 1.0); glVertex2f(width, 0);
    glTexCoord2f(1.0, 0.0); glVertex2f(width, height);
    glTexCoord2f(0.0, 0.0); glVertex2f(0,     height);
    glEnd();

    glPopMatrix();

    //draw press overlay
    glBindTexture(GL_TEXTURE_2D, 0);
    glColor4f(1.0f, 1.0f, 1.0f, alpha);
    glBegin(GL_QUADS);
    glVertex2f(xPos, yPos);
    glVertex2f(xPos+width, yPos);
    glVertex2f(xPos+width, yPos+height);
    glVertex2f(xPos, yPos+height);
    glEnd();

    if (alpha > 0) alpha -= 0.02f;
}