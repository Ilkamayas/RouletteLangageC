#include "sdl_utils.h"    // inclut le header
#include <SDL2/SDL_image.h> // pour gerer les images
#include <stdio.h>        // pour afficher les erreurs

// fonction qui initialise sdl et les differents modules
bool initSDL(SDL_Window** window, SDL_Renderer** renderer) {
    // lance sdl avec video et audio
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) { 
        printf("erreur SDL_Init : %s\n", SDL_GetError());  // affiche l'erreur
        return false;  // retourne false si ca foire
    }

    // active le support des images png
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) { 
        printf("erreur SDL_image\n");  // affiche l'erreur
        SDL_Quit();  // ferme sdl
        return false;  // echoue si l'init foire
    }

    // active le support du texte
    if (TTF_Init() == -1) {
        printf("erreur TTF_Init\n");  // affiche l'erreur
        SDL_Quit();  // ferme tout
        return false;  
    }

    // cree une fenetre au centre de l'ecran, taille 800x600
    *window = SDL_CreateWindow("Roulette", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                               800, 600, SDL_WINDOW_SHOWN);
    if (!*window) {  // verif si la fenetre a ete creer
        printf("erreur SDL_CreateWindow : %s\n", SDL_GetError());
        SDL_Quit();  
        return false;  
    }

    // cree le renderer avec accel materiel (plus rapide)
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!*renderer) {  // si le renderer a pas marcher
        printf("erreur SDL_CreateRenderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);  // detruit la fenetre avant de quitter
        SDL_Quit();  
        return false;  
    }

    return true;  // tout s'est bien passer
}

// fonction qui charge une image et la transforme en texture pour l'affichage
SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer) {
    // charge l'image
    SDL_Texture* tex = IMG_LoadTexture(renderer, path);
    
    // verifie si ca a marcher
    if (!tex) {
        printf("erreur loadTexture '%s': %s\n", path, IMG_GetError());  // affiche l'erreur
    }

    return tex;  // renvoi la texture (ou NULL si ca foire)
}

// fonction qui affiche du texte a l'ecran
void renderText(SDL_Renderer* renderer, const char* text, int x, int y, 
                TTF_Font* font, SDL_Color color) {
    // cree une surface contenant le texte avec la couleur demandee
    SDL_Surface* surf = TTF_RenderText_Solid(font, text, color);
    if (!surf) {  // si la surface a pas pu etre creer
        printf("erreur TTF_RenderText\n");  // affiche l'erreur
        return;
    }

    // transforme la surface en texture pour affichage
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);
    
    // definit la zone ou afficher le texte
    SDL_Rect rect = { x, y, surf->w, surf->h };

    // affiche le texte a l'ecran
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    // libere la memoire
    SDL_FreeSurface(surf);  // supprime la surface
    SDL_DestroyTexture(texture);  // detruit la texture
}
