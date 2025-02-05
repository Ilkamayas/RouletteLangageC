#include "sdl_utils.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>

bool initSDL(SDL_Window** window, SDL_Renderer** renderer){
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){ // Initialise SDL avec support vidéo et audio
        printf("Erreur SDL_Init : %s\n", SDL_GetError());
        return false;
    }
    int imgFlags = IMG_INIT_PNG;  // Indique que nous souhaitons utiliser le support PNG
    if(!(IMG_Init(imgFlags) & imgFlags)){
        printf("Erreur SDL_image\n");
        SDL_Quit();
        return false;
    }
    if(TTF_Init() == -1){
        printf("Erreur TTF_Init\n");
        SDL_Quit();
        return false;
    }

    // Création de la fenêtre centrée avec les dimensions définies
    *window = SDL_CreateWindow("Roulette",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, SDL_WINDOW_SHOWN);
    if(!*window){
        SDL_Quit();
        return false;
    }
    // Création du renderer avec accélération matérielle
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if(!*renderer){
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return false;
    }
    return true;
}

SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer){
    SDL_Texture* tex = IMG_LoadTexture(renderer, path); // Charge l'image et la convertit en texture
    if(!tex){
        printf("Erreur loadTexture '%s': %s\n", path, IMG_GetError());
    }
    return tex;
}

void renderText(SDL_Renderer* renderer, const char* text, int x, int y,
                TTF_Font* font, SDL_Color color){
    SDL_Surface* surf = TTF_RenderText_Solid(font, text, color); // Crée une surface contenant le texte
    if(!surf){
        printf("Erreur TTF_RenderText\n");
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf); // surface -> texture
    SDL_Rect rect = { x, y, surf->w, surf->h }; // zone de destination
    SDL_RenderCopy(renderer, texture, NULL, &rect); // copie la texture
    SDL_FreeSurface(surf);        // libère temporairement la surface
    SDL_DestroyTexture(texture);  // détruit la texture temporaire
}
