#include "Engine.hpp"

/*Handles events*/
void Engine::onEvent(SDL_Event *event) {
    Event::onEvent(event); //gets and stores the current event
}

/*When the exit button is pressed*/
void Engine::onExit() {
    running = false; //exit the game
}

/*When a key is pressed down*/
void Engine::onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
	if (sym == SDLK_ESCAPE) running = false;
}

/*When the mouse is moved*/
void Engine::onMouseMove(int mX, int mY, int relX, int relY, bool left,bool right,bool middle) {
	mouseX = mX;
	mouseY = mY;
}

/*When the left mouse button is down*/
void Engine::onLButtonDown(int mX, int mY) {
	leftDown = true;
	mouseClickX = mX;
	mouseClickY = mY;
}