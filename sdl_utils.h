#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

bool initSDL(SDL_Window** window, SDL_Renderer** renderer);
SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer);
void renderText(SDL_Renderer* renderer, const char* text, int x, int y, TTF_Font* font, SDL_Color color);

#endif // SDL_UTILS_H
