#include <SDL2/SDL.h>           
#include <SDL2/SDL_image.h>     // Image
#include <SDL2/SDL_ttf.h>       // Ecriture
#include <SDL2/SDL_mixer.h>     // Son
#include <stdio.h>              
#include <stdlib.h>             
#include <stdbool.h>            
#include <string.h>             
#include <time.h>               

#include "sdl_utils.h"
#include "audio.h"
#include "game_logic.h"
#include "graphics.h"

#define WINDOW_WIDTH  800       
#define WINDOW_HEIGHT 600       

int main(int argc, char* argv[]){
    srand(time(NULL));             // pour le random
    SDL_Window* window = NULL;     // Pointeur vers la fenêtre SDL
    SDL_Renderer* renderer = NULL; // Pointeur vers le renderer SDL

    if(!initSDL(&window, &renderer)) {
        exit(EXIT_FAILURE);       // si pas de fenêtre ou renderer, on sort
    }

    if(TTF_Init() == -1){         // Initialisation de SDL_ttf pour la gestion de texte
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);       // si le ttf marche pas, on sort
    }

    TTF_Font* font = TTF_OpenFont("media/Casino3D.ttf", 24); // on ouvre un fichier de police en taille 24
    if(!font){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);       // si erreur avec la police, on sort
    }

    if(!initAudio()){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    Mix_Music* backgroundMusic = loadBackgroundMusic("media/casino.mp3"); // on charge la musique de fond
    Mix_Chunk* clickSound = loadClickSound("media/jeton.wav"); // on charge le son du clic
    Mix_Chunk* spinSound = loadSpinSound("media/spin.mp3"); // on charge le son de la roulette

    if(backgroundMusic){ // si musique de fond, on la joue en boucle
        Mix_PlayMusic(backgroundMusic, -1);
    }

    // On charge toutes les images (roulette, tapis, jetons, etc.)
    SDL_Texture* menuTexture    = loadTexture("media/menu.png", renderer);
    SDL_Texture* plateauTexture = loadTexture("media/tapis.png", renderer);
    SDL_Texture* wheelTexture   = loadTexture("media/roulette_eur1.png", renderer);
    SDL_Texture* retourTexture  = loadTexture("media/retour.png", renderer);

    SDL_Texture* jeton5   = loadTexture("media/jetons_vert.png", renderer);
    SDL_Texture* jeton10  = loadTexture("media/jetons_bleu.png", renderer);
    SDL_Texture* jeton20  = loadTexture("media/jetons_rouge.png", renderer);
    SDL_Texture* jeton50  = loadTexture("media/jetons_noir.png", renderer);
    SDL_Texture* jeton100 = loadTexture("media/jetons_violet.png", renderer);

    if(!menuTexture || !plateauTexture || !wheelTexture || !retourTexture ||
       !jeton5 || !jeton10 || !jeton20 || !jeton50 || !jeton100) {
        printf("Erreur chargement des textures.\n"); // on ne sort pas, on affiche juste un message
    }

    int solde = 1000;              // Mise de départ
    int selectedMise = 0;          // Jeton sélectionné (afficher en jaune)
    bool running = true;           // boucle qui fait tourner le jeu
    bool displayRoulette = false;  // Indique si l'écran de roulette est affiché (sinon, le menu) (permet de ne pas confondre les clics)
    SDL_Event event;               // variable event

    int timer = TIME_BETTING;      // temps pour miser
    bool bettingPhase = true;      // si phase de mise, on peut miser, sinon non
    Uint32 lastTime = SDL_GetTicks(); // Stocke le dernier tick pour gérer le timer

    float rouletteAngle = 0.0f;    // Angle actuel de la roue
    SDL_Rect rouletteRect    = { 50, 80, 440, 410 }; // coordonnées de la roue
    SDL_Point rouletteCenter = { 215, 205 }; // Centre de rotation de la roue

    SDL_Rect retourRect = { 10, WINDOW_HEIGHT - 100, 100, 100 }; // coordonnées du bouton retour

    SDL_Rect jetonsRect[5] = { // coordonnées des jetons
        {742,180,35,45},
        {742,229,35,45},
        {742,278,35,45},
        {742,327,35,45},
        {742,375,35,45}
    };

    int mises[5] = {5,10,20,50,100};  // Différentes mises

    SDL_RenderPresent(renderer);    // Affiche la première image dans la fenêtre (le menu)

    initialiserMises();             // Réinitialise le tableau des mises (aucune mise n'est active)
    initHistorique();               // Initialise l'historique des numéros gagnants

    while(running) { // le jeu commence
        while(SDL_PollEvent(&event)) { // gestion des events
            if(event.type == SDL_QUIT) { // Si on ferme la fenêtre, on sort du jeu
                running = false;        
            }
            else if(event.type == SDL_MOUSEBUTTONDOWN) { // Si un bouton de la souris est cliqué
                playClickSound(clickSound);
                int x = event.button.x; // on récupère les coordonnées
                int y = event.button.y;

                if(!displayRoulette){ // Pas la roulette, donc le menu
                    if(x > 120 && x < 351 && y > 400 && y < 500) { // bouton "Play"
                        displayRoulette = true;
                    }
                    else if(x > 451 && x < 700 && y > 400 && y < 500){ // bouton "Exit"
                        running = false;
                    }
                } else { // sur l'écran de la roulette
                    if(x > retourRect.x && x < (retourRect.x + retourRect.w) &&
                       y > retourRect.y && y < (retourRect.y + retourRect.h)) {
                        displayRoulette = false; // Bouton menu cliqué -> retour au menu
                    }
                    else if(bettingPhase) { // Si phase de mise
                        for(int i = 0; i < 5; i++) { // regarde si on a cliqué sur des jetons
                            if(x > jetonsRect[i].x && x < (jetonsRect[i].x + jetonsRect[i].w) &&
                               y > jetonsRect[i].y && y < (jetonsRect[i].y + jetonsRect[i].h)) {
                                selectedMise = mises[i]; // On prend la mise définie par le jeton
                                printf("Mise sélectionnée : %d\n", selectedMise);
                            }
                        }
                        // Si déjà sélectionné, remplace la mise
                        if(selectedMise > 0) {
                            const char* caseNom = detecterCaseCliquee(x, y, plateau, taillePlateau);
                            if(caseNom){
                                int iCase = -1;
                                for(int c = 0; c < taillePlateau; c++){
                                    if(strcmp(plateau[c].nom, caseNom) == 0){
                                        iCase = c;
                                        break;
                                    }
                                }
                                if(iCase >= 0 && solde >= selectedMise) {
                                    if(poserMise(iCase, selectedMise)) {
                                        solde -= selectedMise;
                                        printf("Mise sur %s, solde=%d\n", caseNom, solde);
                                    } else {
                                        printf("Nombre maximum de mises atteint, vous ne pouvez pas miser plus !\n");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        // Création d'un timer, pour le temps (eh oui)
        Uint32 currentTime = SDL_GetTicks(); // timer en tick
        if(currentTime > lastTime + 1000){ // si une seconde est passée
            timer--;             // on la décrémente
            lastTime = currentTime;
            if(timer <= 0){ // si le temps = 0
                bettingPhase = !bettingPhase; // "RIEN NE VA PLUS"

                if(!bettingPhase){
                    timer = TIME_STOP;           // On met le temps à 10
                    numeroTire = false;          // réinitialise le numéro tiré
                    debutRienNeVaPlus = SDL_GetTicks();  // Nouveau timer en tick

                    playSpinSound(spinSound);
                } else {
                    timer = TIME_BETTING;          // Une fois fini, on repart à la phase de mise
                    initialiserMises();            // On réinitialise les mises
                }
            }
        }

        // Petit temps entre la roue qui tourne et le tirage du numéro (8 secondes)
        if(!bettingPhase && !numeroTire) {
            if(SDL_GetTicks() > debutRienNeVaPlus + 8000) { // 8 secondes passées
                int numeroGagnant = rand() % 37;      // Tire un numéro aléatoire entre 0 et 36
                calculerGains(numeroGagnant, &solde);   // on calcule les gains
                ajouterNumeroHistorique(numeroGagnant); // on met le numéro dans l'historique
                printf("Numéro tiré : %d\n", numeroGagnant);
                numeroTire = true;                      // On l'affiche
            }
        }

        // La roue ralentit au fur et à mesure qu'elle tourne (logique)
        if(!bettingPhase && displayRoulette) {
            Uint32 spinElapsed = SDL_GetTicks() - debutRienNeVaPlus; // regarde le temps écoulé depuis le début
            float spinDuration = TIME_STOP * 1000.0f;                  // durée de la rotation (en millisecondes)
            float initialSpeed = 5.0f;                                 // Vitesse initiale de rotation (degrés par frame)
            float currentSpeed = initialSpeed * (1.0f - (float)spinElapsed / spinDuration); // Vitesse actuelle dégressive : vitesse = vitesse * (1 - temps écoulé / durée totale)
            if (currentSpeed < 0)
                currentSpeed = 0; // arrêt de la roue
            rouletteAngle += currentSpeed; // Mise à jour de l'angle de la roue
        }

        renderFrame(displayRoulette, renderer,
                    menuTexture, plateauTexture, wheelTexture,
                    retourTexture,
                    jeton5, jeton10, jeton20, jeton50, jeton100,
                    font, solde, timer, bettingPhase, selectedMise,
                    rouletteAngle, rouletteRect, rouletteCenter,
                    retourRect, jetonsRect);
    }

    // On libère toutes les ressources avant de quitter
    // Libération des textures
    SDL_DestroyTexture(menuTexture);
    SDL_DestroyTexture(plateauTexture);
    SDL_DestroyTexture(wheelTexture);
    SDL_DestroyTexture(retourTexture);
    SDL_DestroyTexture(jeton5);
    SDL_DestroyTexture(jeton10);
    SDL_DestroyTexture(jeton20);
    SDL_DestroyTexture(jeton50);
    SDL_DestroyTexture(jeton100);
    TTF_CloseFont(font);          // Fermeture de la police

    closeAudio(backgroundMusic, clickSound, spinSound);

    SDL_DestroyRenderer(renderer); // on détruit le renderer
    SDL_DestroyWindow(window);     // on détruit la fenêtre
    IMG_Quit();                    // arrêt du système d'image
    TTF_Quit();                    // arrêt du système de texte
    SDL_Quit();                    // on ferme

    exit(EXIT_SUCCESS);           // Fin du programme avec succès
}
