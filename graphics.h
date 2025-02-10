#ifndef GRAPHICS_H  // evite d'inclure plusieurs fois le fichier
#define GRAPHICS_H

// inclut les biblio SDL necessaires
#include <SDL2/SDL.h>      
#include <SDL2/SDL_ttf.h>  
#include <stdbool.h>       

// definit la taille de la fenetre
#define WINDOW_WIDTH  800       
#define WINDOW_HEIGHT 600       

// fonction qui gere l'affichage de la fenetre du jeu
void renderFrame(bool displayRoulette, SDL_Renderer* renderer,
                 SDL_Texture* menuTexture, SDL_Texture* plateauTexture, SDL_Texture* wheelTexture,
                 SDL_Texture* retourTexture,
                 SDL_Texture* jeton5, SDL_Texture* jeton10, SDL_Texture* jeton20,
                 SDL_Texture* jeton50, SDL_Texture* jeton100,
                 TTF_Font* font, int solde, int timer, bool bettingPhase, int selectedMise,
                 float rouletteAngle, SDL_Rect rouletteRect, SDL_Point rouletteCenter,
                 SDL_Rect retourRect, SDL_Rect jetonsRect[5]);

#endif // fin du header guard
