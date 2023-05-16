#pragma once
#include "SDL.h"

//The Game Class 
class Game {

public:
	Game();
	~Game();
	void init(const char* title, int width, int height);
	void handleEvents();
	void update();
	void render();
	bool runCheck();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool isRunning;
};
