#include "game_logic.h"
#include "sdl_utils.h"  // Pour utiliser renderText dans afficherHistorique
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL_mixer.h>

// Définition des variables globales
CasePlateau plateau[] = { // chaque coordonné a été rentré et ajusté par mes soins :)
    { "nb0",          567,  42,  721,  80, 36 },     // nb definit un nombre
    { "nb1",          567,  80,  605, 110, 36 },
    { "h1_2",         605,  80,  630, 110, 18 },     // h definit un horse (a cheval) entre 2 nombres
    { "nb2",          630,  80,  658, 110, 36 },
    { "h2_3",         658,  80,  683, 110, 18 },
    { "nb3",          683,  80,  721, 110, 36 },
    { "h1_4",         567, 110,  605, 128, 18 },
    { "h2_5",         630, 110,  658, 128, 18 },
    { "h3_6",         683, 110,  721, 128, 18 },
    { "sq1_2_4_5",    605, 110,  630, 128,  8 },     // sq definit un square (carré) entre 4 nombres
    { "sq2_3_5_6",    658, 110,  683, 128,  8 },
    { "nb4",          567, 128,  605, 149, 36 },
    { "h4_5",         605, 128,  630, 149, 18 },
    { "nb5",          630, 128,  658, 149, 36 },
    { "h5_6",         658, 128,  683, 149, 18 },
    { "nb6",          683, 128,  721, 149, 36 },
    { "h4_7",         567, 149,  605, 167, 18 },
    { "h5_8",         630, 149,  658, 167, 18 },
    { "h6_9",         683, 149,  721, 167, 18 },
    { "sq4_5_7_8",    605, 149,  630, 167,  8 },
    { "sq5_6_8_9",    658, 149,  683, 167,  8 },
    { "nb7",          567, 167,  605, 187, 36 },
    { "h7_8",         605, 167,  630, 187, 18 },
    { "nb8",          630, 167,  658, 187, 36 },
    { "h8_9",         658, 167,  683, 187, 18 },
    { "nb9",          683, 167,  721, 187, 36 },
    { "h7_10",        567, 187,  605, 206, 18 },
    { "h8_11",        630, 187,  658, 206, 18 },
    { "h9_12",        683, 187,  721, 206, 18 },
    { "sq7_8_10_11",  605, 187,  630, 206,  8 },
    { "sq8_9_11_12",  658, 187,  683, 206,  8 },
    { "nb10",         567, 206,  605, 226, 36 },
    { "h10_11",       605, 206,  630, 226, 18 },
    { "nb11",         630, 206,  658, 226, 36 },
    { "h11_12",       658, 206,  683, 226, 18 },
    { "nb12",         683, 206,  721, 226, 36 },
    { "h10_13",       567, 226,  605, 244, 18 },
    { "h11_14",       630, 226,  658, 244, 18 },
    { "h12_15",       683, 226,  721, 244, 18 },
    { "sq10_11_13_14",605, 226,  630, 244,  8 },
    { "sq11_12_14_15",658, 226,  683, 244,  8 },
    { "nb13",         567, 244,  605, 265, 36 },
    { "h13_14",       605, 244,  630, 265, 18 },
    { "nb14",         630, 244,  658, 265, 36 },
    { "h14_15",       658, 244,  683, 265, 18 },
    { "nb15",         683, 244,  721, 265, 36 },
    { "h13_16",       567, 265,  605, 283, 18 },
    { "h14_17",       630, 265,  658, 283, 18 },
    { "h15_18",       683, 265,  721, 283, 18 },
    { "sq13_14_16_17",605, 265,  630, 283,  8 },
    { "sq14_15_17_18",658, 265,  683, 283,  8 },
    { "nb16",         567, 283,  605, 303, 36 },
    { "h16_17",       605, 283,  630, 303, 18 },
    { "nb17",         630, 283,  658, 303, 36 },
    { "h17_18",       658, 283,  683, 303, 18 },
    { "nb18",         683, 283,  721, 303, 36 },
    { "h16_19",       567, 303,  605, 321, 18 },
    { "h17_20",       630, 303,  658, 321, 18 },
    { "h18_21",       683, 303,  721, 321, 18 },
    { "sq16_17_19_20",605, 303,  630, 321,  8 },
    { "sq17_18_20_21",658, 303,  683, 321,  8 },
    { "nb19",         567, 321,  605, 342, 36 },
    { "h19_20",       605, 321,  630, 342, 18 },
    { "nb20",         630, 321,  658, 342, 36 },
    { "h20_21",       658, 321,  683, 342, 18 },
    { "nb21",         683, 321,  721, 342, 36 },
    { "h19_22",       567, 342,  605, 360, 18 },
    { "h20_23",       630, 342,  658, 360, 18 },
    { "h21_24",       683, 342,  721, 360, 18 },
    { "sq19_20_22_23",605, 342,  630, 360,  8 },
    { "sq20_21_23_24",658, 342,  683, 360,  8 },
    { "nb22",         567, 360,  605, 380, 36 },
    { "h22_23",       605, 360,  630, 380, 18 },
    { "nb23",         630, 360,  658, 380, 36 },
    { "h23_24",       658, 360,  683, 380, 18 },
    { "nb24",         683, 360,  721, 380, 36 },
    { "h22_25",       567, 380,  605, 398, 18 },
    { "h23_26",       630, 380,  658, 398, 18 },
    { "h24_27",       683, 380,  721, 398, 18 },
    { "sq22_23_25_26",605, 380,  630, 398,  8 },
    { "sq23_24_26_27",658, 380,  683, 398,  8 },
    { "nb25",         567, 398,  605, 419, 36 },
    { "h25_26",       605, 398,  630, 419, 18 },
    { "nb26",         630, 398,  658, 419, 36 },
    { "h26_27",       658, 398,  683, 419, 18 },
    { "nb27",         683, 398,  721, 419, 36 },
    { "h25_28",       567, 419,  605, 437, 18 },
    { "h26_29",       630, 419,  658, 437, 18 },
    { "h27_30",       683, 419,  721, 437, 18 },
    { "sq25_26_28_29",605, 419,  630, 437,  8 },
    { "sq26_27_29_30",658, 419,  683, 437,  8 },
    { "nb28",         567, 437,  605, 457, 36 },
    { "h28_29",       605, 437,  630, 457, 18 },
    { "nb29",         630, 437,  658, 457, 36 },
    { "h29_30",       658, 437,  683, 457, 18 },
    { "nb30",         683, 437,  721, 457, 36 },
    { "h28_31",       567, 457,  605, 475, 18 },
    { "h29_32",       630, 457,  658, 475, 18 },
    { "h30_33",       683, 457,  721, 475, 18 },
    { "sq28_29_31_32",605, 457,  630, 475,  8 },
    { "sq29_30_32_33",658, 457,  683, 475,  8 },
    { "nb31",         567, 475,  605, 496, 36 },
    { "h31_32",       605, 475,  630, 496, 18 },
    { "nb32",         630, 475,  658, 496, 36 },
    { "h32_33",       658, 475,  683, 496, 18 },
    { "nb33",         683, 475,  721, 496, 36 },
    { "h31_34",       567, 496,  605, 514, 18 },
    { "h32_35",       630, 496,  658, 514, 18 },
    { "h33_36",       683, 496,  721, 514, 18 },
    { "sq31_32_34_35",605, 496,  630, 514,  8 },
    { "sq32_33_35_36",658, 496,  683, 514,  8 },
    { "nb34",         567, 514,  605, 543, 36 },
    { "h34_35",       605, 514,  630, 543, 18 },
    { "nb35",         630, 514,  658, 543, 36 },
    { "h35_36",       658, 514,  683, 543, 18 },
    { "nb36",         683, 514,  721, 543, 36 },
    { "Manque", 518, 81, 542, 158, 2},             // Pari specifique a partir d'ici (tout ce qui n'est pas nombre)
    { "Impair", 518, 158, 542, 235, 2},
    { "Rouge", 518, 235, 542, 312, 2},
    { "Noir", 518, 312, 542, 389, 2},
    { "Pair", 518, 389, 542, 466, 2},
    { "Passe", 518, 466, 542, 543, 2},
    { "1ère Douzaine", 542, 81, 567, 235, 3},
    { "2ème Douzaine", 542, 235, 567, 389, 3},
    { "3ème Douzaine", 542, 389, 567, 543, 3},
    { "1ère Colonne", 567, 543, 618, 573, 3},
    { "2ème Colonne", 618, 543, 670, 573, 3},
    { "3ème Colonne", 670, 543, 721, 573, 3}
};
int taillePlateau = sizeof(plateau)/sizeof(CasePlateau); // nombre de case dans le plateau

MisePosee misesPosees[MAXMISES];   // stocke les mises placées
int lastNumbers[HISTORY_SIZE];     // historiques des numéros gagnants
int lastIndex = 0;                 // Index actuel (pour gestion circulaire)
bool numeroTire = false;           // Numero gagnant tiré ou pas
Uint32 debutRienNeVaPlus = 0;      // Passage a la phase rien ne vas plus

// --- Fonctions ---

const char* detecterCaseCliquee(int x, int y, CasePlateau* plateau, int taillePlateau){
    for(int i = 0; i < taillePlateau; i++){
        if(x >= plateau[i].x1 && x <= plateau[i].x2 &&
           y >= plateau[i].y1 && y <= plateau[i].y2){
            return plateau[i].nom;  // renvoie ce qui a été cliqué
        }
    }
    return NULL;
}

void parseNumList(const char* nom, int* coverage, int* count) {
    *count = 0;
    if (strncmp(nom, "nb", 2) == 0) {
        int n = atoi(nom + 2); // si nb au debut, on met nb + nombre
        coverage[(*count)++] = n;
        return;
    }
    if (nom[0] == 'h') {
        char buf[16];
        strcpy(buf, nom+1);  // si h, on cherche les nombre apres le _
        char* underscore = strchr(buf, '_'); 
        if(underscore) {
            *underscore = '\0';         // separe les nombres
            int n1 = atoi(buf);         // et conversion
            int n2 = atoi(underscore+1); 
            coverage[(*count)++] = n1;
            coverage[(*count)++] = n2;
        }
        return;
    }
    if (strncmp(nom, "sq", 2) == 0) {
        char buf[32];
        strcpy(buf, nom+2);    // Copie la chaîne après "sq"
        char* token = strtok(buf, "_"); // prend le premier nombre collé au sq
        while(token && *count < 6){
            coverage[(*count)++] = atoi(token); // prend les 3 suivant un par un
            token = strtok(NULL, "_");
        }
        return;
    }
}

void calculerGains(int numeroGagnant, int* solde) {
    for(int i = 0; i < MAXMISES; i++){
        if(!misesPosees[i].actif) continue;  // si pas active, on passe

        int ci   = misesPosees[i].caseIndex; // recupere ce qu'il a misé et combien il a misé
        int mise = misesPosees[i].montant;     
        bool gagne = false;                    // est ce gagnant ou pas

        int coverage[6];
        int count = 0;
        parseNumList(plateau[ci].nom, coverage, &count);  // regarde ce qui est couvert par la mise

        // si couvert, on met la gagne
        for(int c = 0; c < count; c++) {
            if(coverage[c] == numeroGagnant) {
                gagne = true;
                break;
            }
        }

        // on regarde pour les paris hors numéros
        if(!gagne){
            if(strcmp(plateau[ci].nom, "Rouge") == 0){
                if(numeroGagnant != 0 && estRouge(numeroGagnant)) gagne = true;
            }
            else if(strcmp(plateau[ci].nom, "Noir") == 0){
                if(numeroGagnant != 0 && !estRouge(numeroGagnant)) gagne = true;
            }
            else if(strcmp(plateau[ci].nom, "Pair") == 0){
                if(numeroGagnant != 0 && (numeroGagnant % 2 == 0)) gagne = true;
            }
            else if(strcmp(plateau[ci].nom, "Impair") == 0){
                if(numeroGagnant % 2 == 1) gagne = true;
            }
            else if(strcmp(plateau[ci].nom, "Manque") == 0){
                if(numeroGagnant >= 1 && numeroGagnant <= 18) gagne = true;
            }
            else if(strcmp(plateau[ci].nom, "Passe") == 0){
                if(numeroGagnant >= 19 && numeroGagnant <= 36) gagne = true;
            }
            else if(strcmp(plateau[ci].nom, "1ère Douzaine") == 0){
                if(numeroGagnant >= 1 && numeroGagnant <= 12) gagne = true;
            }
            else if(strcmp(plateau[ci].nom, "2ème Douzaine") == 0){
                if(numeroGagnant >= 13 && numeroGagnant <= 24) gagne = true;
            }
            else if(strcmp(plateau[ci].nom, "3ème Douzaine") == 0){
                if(numeroGagnant >= 25 && numeroGagnant <= 36) gagne = true;
            }
            else if(strcmp(plateau[ci].nom, "1ère Colonne") == 0){
                for(int col = 1; col <= 34; col += 3){
                    if(numeroGagnant == col) { gagne = true; break; }
                }
            }
            else if(strcmp(plateau[ci].nom, "2ème Colonne") == 0){
                for(int col = 2; col <= 35; col += 3){
                    if(numeroGagnant == col) { gagne = true; break; }
                }
            }
            else if(strcmp(plateau[ci].nom, "3ème Colonne") == 0){
                for(int col = 3; col <= 36; col += 3){
                    if(numeroGagnant == col) { gagne = true; break; }
                }
            }
        }

        // et on regarde pour les numéros gagnants en mettant a jour la solde
        if(gagne){
            int gain = mise * plateau[ci].multiplicateur;
            *solde += gain;
            printf("Case %s => Gagne +%d\n", plateau[ci].nom, gain);
        }
        misesPosees[i].actif = false;  // desactive la mise une fois la solde a jour
    }
}

bool estRouge(int numero){
    if(numero == 0) return false;
    int rougeNums[] = {1,3,5,7,9,12,14,16,18,20,22,24,26,28,30,32,34,36}; 
    for(size_t i = 0; i < sizeof(rougeNums) / sizeof(rougeNums[0]); i++){
        if(rougeNums[i] == numero) return true;
    }
    return false;
}

void initHistorique(){
    for(int i = 0; i < HISTORY_SIZE; i++){
        lastNumbers[i] = -1;  // Initialise chaque élément à -1 pour indiquer qu'il est vide
    }
}

void ajouterNumeroHistorique(int numero){
    lastNumbers[lastIndex] = numero;
    lastIndex = (lastIndex + 1) % HISTORY_SIZE;  // Avance l'index pour que ca soit circulaire
}

void afficherHistorique(SDL_Renderer* renderer, TTF_Font* font){
    int startY = 200;  // On affiche en vertical a cote de la roue
    for(int i = 0; i < HISTORY_SIZE; i++){
        int idx = (lastIndex - 1 - i + HISTORY_SIZE) % HISTORY_SIZE;  // On affiche d'abord le plus recent, donc le dernier
        int numero = lastNumbers[idx];
        if(numero < 0) break;  // si pas de numeros, on sort
        SDL_Color color = {0, 0, 0, 255};  // Couleur par défaut : noir
        if(numero == 0){
            color.r = 0;   color.g = 255; color.b = 0;  // Le 0 s'affiche en vert
        } else if(estRouge(numero)){
            color.r = 255; color.g = 0;   color.b = 0;  // si dans le tableau rouge, en rouge
        }
        char buf[10];
        sprintf(buf, "%d", numero);  // Conversion du numéro en chaîne de caractères et l'affiche
        renderText(renderer, buf, 30, startY + i * 30, font, color);
    }
}

void initialiserMises(){
    for(int i = 0; i < MAXMISES; i++){
        misesPosees[i].actif = false;  // Marque chaque mise comme inactive
    }
}

bool poserMise(int caseIndex, int montant) {
    for (int i = 0; i < MAXMISES; i++) {
        if (!misesPosees[i].actif) {
            misesPosees[i].caseIndex = caseIndex;
            misesPosees[i].montant = montant;
            misesPosees[i].actif = true;
            return true;  // Mise enregistrée avec succès
        }
    }
    return false;  // Si plus de place, la mise ne s'enregistre pas
}
