#include "graphics.h"
#include "sdl_utils.h"
#include "game_logic.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

void renderFrame(bool displayRoulette, SDL_Renderer* renderer,
                 SDL_Texture* menuTexture, SDL_Texture* plateauTexture, SDL_Texture* wheelTexture,
                 SDL_Texture* retourTexture,
                 SDL_Texture* jeton5, SDL_Texture* jeton10, SDL_Texture* jeton20,
                 SDL_Texture* jeton50, SDL_Texture* jeton100,
                 TTF_Font* font, int solde, int timer, bool bettingPhase, int selectedMise,
                 float rouletteAngle, SDL_Rect rouletteRect, SDL_Point rouletteCenter,
                 SDL_Rect retourRect, SDL_Rect jetonsRect[5])
{
    SDL_RenderClear(renderer);  // Efface le renderer pour préparer le dessin du nouveau frame

    // affichage
    if(!displayRoulette){
        SDL_RenderCopy(renderer, menuTexture, NULL, NULL); // Affiche l'écran du menu
    } else {
        SDL_RenderCopy(renderer, plateauTexture, NULL, NULL); // Affiche le tapis/plateau de roulette
        SDL_RenderCopyEx(renderer, wheelTexture, NULL, &rouletteRect, rouletteAngle, &rouletteCenter, SDL_FLIP_NONE); // Affiche la roue de roulette en rotation

        SDL_Color white = {255,255,255,255}; // Affichage Argent du joueur
        char soldeBuf[30];
        sprintf(soldeBuf, "SOLDE: %d", solde);
        renderText(renderer, soldeBuf, 10, 10, font, white);

        char phaseBuf[64]; // Affichage du timer de la phase de jeu et du message qui va avec
        if(bettingPhase){ 
            sprintf(phaseBuf, "FAITES VOS JEUX : %d SEC", timer);
        } else {
            sprintf(phaseBuf, "RIEN NE VA PLUS : %d SEC", timer);
        }
        renderText(renderer, phaseBuf, WINDOW_WIDTH/2 - 100, 10, font, white);
        SDL_RenderCopy(renderer, retourTexture, NULL, &retourRect); // Affiche le bouton de retour

        if(selectedMise > 0){ // affiche la mise sélectionnée en jaune
            char miseText[20];
            sprintf(miseText, "%d$", selectedMise);
            SDL_Color yellow = {255,255,0,255};
            renderText(renderer, miseText, 740, 550, font, yellow);
        }

        for(int i = 0; i < MAXMISES; i++){ // Met un jeton sur le plateau à chaque mise
            if(!misesPosees[i].actif) continue; // si inactive, on passe

            int ci = misesPosees[i].caseIndex; 
            // On met le jeton au centre de la case (enfin on essaye)
            int xMid = (plateau[ci].x1 + plateau[ci].x2) / 2 - 15;
            int yMid = (plateau[ci].y1 + plateau[ci].y2) / 2 - 15;

            SDL_Texture* chipTex = NULL;
            // une couleur = une mise
            switch(misesPosees[i].montant){
                case 5:   chipTex = jeton5;   break;
                case 10:  chipTex = jeton10;  break;
                case 20:  chipTex = jeton20;  break;
                case 50:  chipTex = jeton50;  break;
                case 100: chipTex = jeton100; break;
            }
            SDL_Rect dstRect = { xMid, yMid, 30, 30 }; // On place le jeton et sa taille sur le plateau
            if(chipTex)
                SDL_RenderCopy(renderer, chipTex, NULL, &dstRect); // On l'affiche
        }

        afficherHistorique(renderer, font); // Affiche l'historique des numéros gagnants

        // Bloc de code de débuggage (je le met car ce type de debugage était pour la plupart des trucs, les cases, les jetons, la roulette, etc...)
        bool debugZonesJetons = false; // désactivé là
        if(debugZonesJetons) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Couleur rouge
            for (int i = 0; i < 5; i++) {
                SDL_RenderDrawRect(renderer, &jetonsRect[i]); // Dessine le contour de chaque zone des jetons
            }
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // remet par défaut
        }
    }

    SDL_RenderPresent(renderer);  // Présente le frame dessiné à l'écran
}
