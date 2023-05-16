#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Game.h"

Game* game = nullptr;

int main(int argc, char *argv[]) {

	//Setting FPS
	const int FPS = 60;
	const int ticksPerFrame = 1000 / FPS;
	Uint32 startTime;
	int currentTime;

	//Game Loop
	game = new Game();
	game->init("Custom Game Engine", 960, 540);
	while (game->runCheck()) 
	{
		startTime = SDL_GetTicks();
		
		game->handleEvents();
		game->update();
		game->render();
		

		currentTime = SDL_GetTicks() - startTime;
		if (ticksPerFrame > currentTime)
		{
			SDL_Delay(ticksPerFrame - currentTime);
		}
		
	}

	return 0;
}