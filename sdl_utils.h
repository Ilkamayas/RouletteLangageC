#ifndef SDL_UTILS_H  // evite d'inclure plusieurs fois le meme fichier
#define SDL_UTILS_H

// inclut les biblio SDL necessaires
#include <SDL2/SDL.h>      // lib principale SDL
#include <SDL2/SDL_ttf.h>  // pour gerer le texte
#include <stdbool.h>       // pour utiliser le type bool

// fonction qui initialise sdl, la fenetre et le renderer
bool initSDL(SDL_Window** window, SDL_Renderer** renderer);

// charge une image et la converti en texture
SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer);

// affiche du texte a une position precise
void renderText(SDL_Renderer* renderer, const char* text, int x, int y, 
                TTF_Font* font, SDL_Color color);

#endif // fin du header guard
