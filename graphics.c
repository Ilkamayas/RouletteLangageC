#include "graphics.h"   // inclut le header graphique
#include "sdl_utils.h"  // pour les fonctions SDL utilitaires
#include "game_logic.h" // pour la logique du jeu
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

// fonction qui dessine la frame du jeu
void renderFrame(bool displayRoulette, SDL_Renderer* renderer,
                 SDL_Texture* menuTexture, SDL_Texture* plateauTexture, SDL_Texture* wheelTexture,
                 SDL_Texture* retourTexture,
                 SDL_Texture* jeton5, SDL_Texture* jeton10, SDL_Texture* jeton20,
                 SDL_Texture* jeton50, SDL_Texture* jeton100,
                 TTF_Font* font, int solde, int timer, bool bettingPhase, int selectedMise,
                 float rouletteAngle, SDL_Rect rouletteRect, SDL_Point rouletteCenter,
                 SDL_Rect retourRect, SDL_Rect jetonsRect[5])
{
    SDL_RenderClear(renderer);  // efface l'ecran avant de redessiner

    // si on est pas sur l'ecran de la roulette, on affiche le menu
    if(!displayRoulette){
        SDL_RenderCopy(renderer, menuTexture, NULL, NULL); // affiche le menu
    } else {
        SDL_RenderCopy(renderer, plateauTexture, NULL, NULL); // affiche le tapis de jeu
        SDL_RenderCopyEx(renderer, wheelTexture, NULL, &rouletteRect, rouletteAngle, &rouletteCenter, SDL_FLIP_NONE); // affiche la roue avec rotation

        SDL_Color white = {255,255,255,255}; // couleur blanche pour le texte

        // affiche le solde du joueur
        char soldeBuf[30];
        sprintf(soldeBuf, "SOLDE: %d", solde);
        renderText(renderer, soldeBuf, 10, 10, font, white);

        char phaseBuf[64]; // texte pour le timer de la phase de jeu
        if(bettingPhase){ 
            sprintf(phaseBuf, "FAITES VOS JEUX : %d SEC", timer);
        } else {
            sprintf(phaseBuf, "RIEN NE VA PLUS : %d SEC", timer);
        }
        renderText(renderer, phaseBuf, WINDOW_WIDTH/2 - 100, 10, font, white);
        
        SDL_RenderCopy(renderer, retourTexture, NULL, &retourRect); // affiche le bouton retour

        // affiche la mise selectionnée
        if(selectedMise > 0){ 
            char miseText[20];
            sprintf(miseText, "%d$", selectedMise);
            SDL_Color yellow = {255,255,0,255};
            renderText(renderer, miseText, 740, 550, font, yellow);
        }

        // affiche les mises posees sur le plateau
        for(int i = 0; i < MAXMISES; i++){ 
            if(!misesPosees[i].actif) continue; // si mise inactive, on passe

            int ci = misesPosees[i].caseIndex; 
            // on centre le jeton sur la case
            int xMid = (plateau[ci].x1 + plateau[ci].x2) / 2 - 15;
            int yMid = (plateau[ci].y1 + plateau[ci].y2) / 2 - 15;

            SDL_Texture* chipTex = NULL;
            // selectionne la texture du jeton en fonction du montant
            switch(misesPosees[i].montant){
                case 5:   chipTex = jeton5;   break;
                case 10:  chipTex = jeton10;  break;
                case 20:  chipTex = jeton20;  break;
                case 50:  chipTex = jeton50;  break;
                case 100: chipTex = jeton100; break;
            }
            SDL_Rect dstRect = { xMid, yMid, 30, 30 }; // position et taille du jeton
            if(chipTex)
                SDL_RenderCopy(renderer, chipTex, NULL, &dstRect); // affiche le jeton
        }

        afficherHistorique(renderer, font); // affiche les num gagnants precedents

        // debug: affiche les zones des jetons (desactive par defaut)
        bool debugZonesJetons = false;
        if(debugZonesJetons) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // met en rouge
            for (int i = 0; i < 5; i++) {
                SDL_RenderDrawRect(renderer, &jetonsRect[i]); // dessine les bordures
            }
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // remet en noir
        }
    }

    SDL_RenderPresent(renderer);  // affiche l'image finale a l'ecran
}
