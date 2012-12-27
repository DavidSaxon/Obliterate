#include "Engine.hpp"

//CONSTRUCTOR
Engine::Engine() {}

//DESTRUCTOR
Engine::~Engine() {}

//FUNCTIONS
/*Initialise the program*/
bool Engine::init() {
    
	//set the variables
	running = true;
    mode = STD;
    mouseX = 0;
    mouseY = 0;
    mouseClickX = 0;
    mouseClickY = 0;
    leftDown = false;
    restart = false;
    title = true;
    titleAlpha = -0.7f;
    fadeIn = 1.0f;

	//initialise sdl
    if (!initSDL()) return false;

    frameLength = 17;
    startFrame = SDL_GetTicks();
    accumTime = 0;

    //open the window
    const SDL_VideoInfo *videoInfo = SDL_GetVideoInfo(); //get the video info
    int flags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE | SDL_FULLSCREEN; //sets the window flags
    if(videoInfo->hw_available) flags |= SDL_HWSURFACE; //check to see if hardware surfaces are enabled
    else flags |= SDL_SWSURFACE;
    if(videoInfo->blit_hw) flags |= SDL_HWACCEL; //check to see if hardware supports blitting
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    if ((display = SDL_SetVideoMode(NATURAL_RESO_X, NATURAL_RESO_Y, 32, flags)) == NULL) return false; //sets up the video mode

    //get the width and height
    width = display->w;
    height = display->h;

    //initialise opengl
    initGL();

    //Load the textures
    loadTextures();

    //create the logo
    logo = new Logo(logoTex, logoWidth, logoHeight);

    //create the buttons
    buttons.push_back(new Button(refreshTex, 25, 680, REFRESH));
    buttons.push_back(new Button(stdTex, 250, 680, STD));
    buttons.push_back(new Button(blackTex, 475, 680, BLACKHOLE));
    buttons.push_back(new Button(swishTex, 700, 680, SWISH));
    buttons.push_back(new Button(butterTex, 925, 680, BUTTERFLY));
    buttons.push_back(new Button(reformTex, 1150, 680, REFORM));

	return true;
}

/*Initialises SDL*/
bool Engine::initSDL() {
	if (SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_AUDIO) < 0) return false;

	return true;
}

/*Initialises openGL*/
bool Engine::initGL() {
    glEnable (GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    glOrtho(0, NATURAL_RESO_X, NATURAL_RESO_Y, 0, 0, 1);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glEnable(GL_TEXTURE_2D);

	return true;
}

/*Run the main loop*/
bool Engine::execute() {
	SDL_Event event; //creates a new event

	while (running) {
		//poll events
		while (SDL_PollEvent(&event)) onEvent(&event);

        //clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        long currentTime = SDL_GetTicks()-startFrame+accumTime;
        if (currentTime >= frameLength) {

            if (title) { //display the title

                //increase the alpha
                titleAlpha += 0.01;

                if (titleAlpha >= 1.0) title = false; //exit the title
            }
            else { //display the obliterator
                if (leftDown) { //check for button presses
                    vector<Button*>::iterator r;
                    for (r = buttons.begin(); r != buttons.end(); ++r) {
                        int next = (*r)->mouseOn(mouseX, mouseY); //get the mode from the button
                        if (next == REFRESH) {
                            restartSim();
                            leftDown = false;
                        }
                        else if (next != -1) {
                            mode = next;
                            leftDown = false;
                        }

                    }
                }


                if (logo != NULL) { //if the logo exists
                    if (leftDown) obliterate(); //if the mouse is clicked obliterate
                }

                //debris
                vector<Debris*>::iterator q;
                for (q = debris.begin(); q != debris.end(); ++q) {
                    (*q)->update();
                }

                if (fadeIn > 0) { //fade in
                    fadeIn -= 0.01;
                }

            }

            leftDown = false; //reset the mouse

            accumTime = currentTime-frameLength; //find the accumulated time
            startFrame = SDL_GetTicks(); //set the start time of the new frame

        }


        if (title) { //display the title
            glBindTexture(GL_TEXTURE_2D, titleTex);
            glBegin(GL_QUADS);
            glTexCoord2f(0.0, 1.0); glVertex2f(350, 250);
            glTexCoord2f(1.0, 1.0); glVertex2f(1050, 250);
            glTexCoord2f(1.0, 0.0); glVertex2f(1050, 450);
            glTexCoord2f(0.0, 0.0); glVertex2f(350, 450);
            glEnd();

            glBindTexture(GL_TEXTURE_2D, 0);
            glColor4f(1.0f, 1.0f, 1.0f, titleAlpha);
            glBegin(GL_QUADS);
            glVertex2f(350, 250);
            glVertex2f(1050, 250);
            glVertex2f(1050, 450);
            glVertex2f(350, 450);
            glEnd();
        }
        else { //display the obliterator

            if (logo != NULL) { //if the logo exists
                logo->draw(width/2, height/2); //draw the logo
            }

            //debris
            vector<Debris*>::iterator q;
            for (q = debris.begin(); q != debris.end(); ++q) {
                (*q)->draw();
            }

            //buttons
            vector<Button*>::iterator p;
            for (p = buttons.begin(); p != buttons.end(); ++p) {
                (*p)->draw();
            }

            if (fadeIn > 0) { //fade in
                glBindTexture(GL_TEXTURE_2D, 0);
                glColor4f(1.0f, 1.0f, 1.0f, fadeIn);
                glBegin(GL_QUADS);
                glVertex2f(0, 0);
                glVertex2f(NATURAL_RESO_X, 0);
                glVertex2f(NATURAL_RESO_X, NATURAL_RESO_Y);
                glVertex2f(0, NATURAL_RESO_Y);
                glEnd();
            }

        }

        //Swap the buffers
        SDL_GL_SwapBuffers();
	}

	return true;
}

/*Takes a logo and turns it into many smaller parts.*/
void Engine::obliterate() {
    //find the number of debris on the width and the height
    float widthCount = logoWidth/DEBRIS_WIDTH;
    float heightCount = logoHeight/DEBRIS_WIDTH;

    //loop through the logo and split create pieces from it
    float j = 0.0f;
    for (int x = (NATURAL_RESO_X/2)-(logoWidth/2); x < (NATURAL_RESO_X/2)+(logoWidth/2); x += DEBRIS_WIDTH) {
        float i = 0.0f;
        for (int y = (NATURAL_RESO_Y/2)-(logoHeight/2); y < (NATURAL_RESO_Y/2)+(logoHeight/2); y += DEBRIS_WIDTH) {

            // //Read the pixels at that point in the point where the debris will be created
            // //If it is mostly white then don't create debris for it
            // GLubyte *data = new GLubyte[4*DEBRIS_WIDTH*DEBRIS_WIDTH];
            // glReadPixels(x+DEBRIS_WIDTH/4, y+DEBRIS_WIDTH/2, DEBRIS_WIDTH, DEBRIS_WIDTH, GL_RGBA, GL_UNSIGNED_BYTE, data);

            // //create an average of the colours
            // float colAvg = 0.0f; //the average of the colours between 0 and 255
            // for (int k = 0; k < DEBRIS_WIDTH; ++k) {
            //     for (int l = 0; l < DEBRIS_WIDTH; ++l) {
            //         float rgbAvg = (float) (data[k+l+0]) + (float) (data[k+l+1]) + (float) (data[k+l+2]); //the average of the colors in this pixel
            //         rgbAvg = rgbAvg/3.0f;
            //         colAvg += rgbAvg;
            //     }
            // }

            // //find the average
            // colAvg = colAvg/(DEBRIS_WIDTH*DEBRIS_WIDTH);

            //if (colAvg < 255.0f) //don't draw if it is too white
            debris.push_back(new Debris(logoTex, x, y, widthCount, heightCount, j, i, mouseClickX, mouseClickY, mode));
            
            ++i;
        }
        ++j;
    }

    //delete the logo
    logo = NULL;
}

/*Restart the simulation*/
void Engine::restartSim() {
    logo = new Logo(logoTex, logoWidth, logoHeight);
    debris.clear(); //delete all the debris
    restart = false;
}

/*Cleanup the program*/
bool Engine::cleanup() {

	return true;
}