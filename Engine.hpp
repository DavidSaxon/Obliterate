/**************************************************************\
| The engine of obliterate. Has overall control of the program |
|															   |
| Author: David Saxon										   |
\**************************************************************/
#ifndef _ENGINE_H_
    #define _ENGINE_H_

#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_opengl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <png.h>
#include <vector>

#include "Define.hpp"
#include "Event.hpp"
#include "Logo.hpp"
#include "Debris.hpp"
#include "Button.hpp"
using namespace std;

class Engine : public Event {
//MAIN
private:

	//VARIABLES
	bool running; //is true while the engine is running
    int mode; //the obliterate mode
	SDL_Surface *display; //the window
    int width; //the width of the window
    int height; //the height of the window
    int mouseX; //the mouseX position
    int mouseY; //the mouseY position
    float mouseClickX; //the x position where the mouse was pressed
    float mouseClickY; //the y position where the mouse was pressed
    bool leftDown; //is true when the left mouse button is down
    bool restart; //is true when to restart the simulation

    bool title; //is true while at title screen
    float titleAlpha; //the alpha level of the title
    float fadeIn;

    //Objects
    Logo *logo; //the logo
    vector<Debris*> debris; //a vector that contains all the debris
    vector<Button*> buttons; //a vector containing all the buttons

    //fps management
    int frameLength; //the length of a frame
    long startFrame; //the time the frame started
    long accumTime; //the time accumulated from the last frame

public:

    //CONSTRUCTOR
    Engine();

    //DESTRUCTOR
    ~Engine();

    //FUNCTIONS
    /*Initialises the the program*/
    bool init();

    /*Initialises SDL*/
    bool initSDL();

    /*Initialises openGL*/
    bool initGL();

    /*Run the main loop*/
    bool execute();

    /*Cleanup the program*/
    bool cleanup();

    /*Takes a logo and turns it into many smaller parts.*/
    void obliterate();

    /*Restart the simulation*/
    void restartSim();

//EVENT
public:

    //FUNCTIONS
    /*Handles events*/
    void onEvent(SDL_Event *event);

    /*When the exit button is pressed*/
    void onExit();

    /*When a key is pressed down*/
    void onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);

    /*When the mouse is moved*/
    void onMouseMove(int mX, int mY, int relX, int relY, bool left,bool right,bool middle);

    /*When the left mouse button is down*/
    void onLButtonDown(int mX, int mY);

//RESOURCES
private:

    //VARIABLES
    //images
    GLubyte *titleImg;
    GLubyte *logoImg;
    GLubyte *refreshImg;
    GLubyte *stdImg;
    GLubyte *blackImg;
    GLubyte *swishImg;
    GLubyte *butterImg;
    GLubyte *reformImg;
    //textures
    GLuint titleTex;
    GLuint logoTex;
    GLuint refreshTex;
    GLuint stdTex;
    GLuint blackTex;
    GLuint swishTex;
    GLuint butterTex;
    GLuint reformTex;

    int logoWidth; //the width of the logo
    int logoHeight; //the hight of the logo

    //FUNCTIONS
    /*Loads the textures into memory*/
    void loadTextures();

    /*Loads a png image*/
    bool loadImage(char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData);
};

#endif