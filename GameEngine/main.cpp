#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Game.h"

Game* game = nullptr;

int main(int argc, char *argv[]) {

	game = new Game();
	game->init("Custom Game Engine", 960, 540);

	while (game->runCheck()) 
	{
		game->handleEvents();
	}

	return 0;
}