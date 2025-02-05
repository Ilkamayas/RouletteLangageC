#ifndef ROULETTE_H
#define ROULETTE_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Définitions de constantes
#define TIME_BETTING 30         // "Faites vos jeux"
#define TIME_STOP    10         // "Rien ne va plus"
#define MAXMISES     100
#define HISTORY_SIZE 10

// Structure d'une case du plateau
typedef struct {
    char nom[20];
    int x1, y1;
    int x2, y2;
    int multiplicateur;
} CasePlateau;

// Structure d'une mise placée
typedef struct {
    int caseIndex;
    int montant;
    bool actif;
} MisePosee;

// Variables globales utilisées dans le module roulette
extern CasePlateau plateau[];
extern int taillePlateau;

extern MisePosee misesPosees[MAXMISES];
extern int lastNumbers[HISTORY_SIZE];
extern int lastIndex;
extern bool numeroTire;
extern Uint32 debutRienNeVaPlus;

// Déclarations des fonctions de gestion du jeu
const char* detecterCaseCliquee(int x, int y, CasePlateau* plateau, int taillePlateau);
void parseNumList(const char* nom, int* coverage, int* count);
void calculerGains(int numeroGagnant, int* solde);
bool estRouge(int numero);
void initHistorique();
void ajouterNumeroHistorique(int numero);
void afficherHistorique(SDL_Renderer* renderer, TTF_Font* font);
void initialiserMises();
bool poserMise(int caseIndex, int montant);

#endif // ROULETTE_H
