#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(SDL_Renderer* renderer, const char* textureFile)
{
	SDL_Surface* surface = IMG_Load(textureFile);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}
