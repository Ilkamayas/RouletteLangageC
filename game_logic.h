#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#define TIME_BETTING 30         // Faite vos jeux
#define TIME_STOP    10         // Rien ne vas plus
#define MAXMISES     100        
#define HISTORY_SIZE 10         

typedef struct { // structure avec le nom, les coordonnées (pour former un carré) et le multiplicateur de gain pour chaque zone de mise
    char nom[20];              
    int x1, y1;                
    int x2, y2;                
    int multiplicateur;        
} CasePlateau;

typedef struct { // structure pour stocker les informations de chaque mise placée (ou, combien et actif)
    int caseIndex;             // Index dans le tableau 'plateau' correspondant à la zone de mise
    int montant;               // Montant de la mise
    bool actif;                
} MisePosee;

// Déclarations des variables globales (déclarées extern)
extern CasePlateau plateau[];
extern int taillePlateau; // nombre de case dans le plateau

extern MisePosee misesPosees[MAXMISES];   // stocke les mises placées
extern int lastNumbers[HISTORY_SIZE];     // historiques des numéros gagnants
extern int lastIndex;                 // Index actuel (pour gestion circulaire)
extern bool numeroTire;           // Numero gagnant tiré ou pas
extern Uint32 debutRienNeVaPlus;      // Passage a la phase rien ne vas plus

// Déclarations des fonctions de game_logic
const char* detecterCaseCliquee(int x, int y, CasePlateau* plateau, int taillePlateau);  // regarde ou on a cliqué
void parseNumList(const char* nom, int* coverage, int* count); // stocke le numéro de la zone cliqué, pour stocker apres le numéro et le montant
void calculerGains(int numeroGagnant, int* solde);  // calcul de gains
bool estRouge(int numero);  // rouge (inverse sera noir et 0 sera vert)
void initHistorique();  // crée l'historique
void ajouterNumeroHistorique(int numero);  // ajoute le numéro gagant dans l'historique
void afficherHistorique(SDL_Renderer* renderer, TTF_Font* font); // les affiches
void initialiserMises();  // reset a chaque tirage (mise deviennent inactive)
bool poserMise(int caseIndex, int montant); // enregistre la mise index et montant

#endif // GAME_LOGIC_H
