#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "TextureManager.h"


SDL_Texture* playerTexture;


Game::Game() 
{
	
}

Game::~Game() 
{

}

void Game::init(const char* title, int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) 
	{
		std::cout << "SDL Initialized" << std::endl;
		isRunning = true;
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, 0);
	}
	else
	{
		std::cout << "SDL Initialization failed." << SDL_GetError() << std::endl;
		isRunning = false;
	}

	playerTexture = TextureManager::LoadTexture(renderer, "assets/player.png");
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) 
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
}

void Game::update()
{

}

void Game::render()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, playerTexture, NULL, NULL);
	SDL_RenderPresent(renderer);
}


bool Game::runCheck() { return isRunning; };