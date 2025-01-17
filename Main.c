#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define MAX_MISES 10 // Nombre maximum de mises par tour (j'ai pas trouver d'autre option que ca pour ne pas la reinitialiser a chaque tour sans changer que ici)

typedef struct { // definit le choix, le detail (deuxieme choix) et le montant de la mise
    int choix;
    int detail;
    int montant;
} Mise;

typedef struct { // definit son nom et son argent
    char nom[50];
    int solde;
} Joueur;

int tirageNombre() { // Aleatoire en 0 et 36
    return rand() % 37;
}

char* determinerCouleur(int numero) { // Tableau avec tout les numeros rouge, si le numero est dedans, il est rouge, sinon il est noir
    if (numero == 0) return "Vert";
    int rouges[] = {1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36};
    for (int i = 0; i < 18; i++) {
        if (numero == rouges[i]) return "Rouge";
    }
    return "Noir";
}

char* determinerParite(int numero) { // Si le numero est pair ou impair
    if (numero == 0) return "Aucun";
    return (numero % 2 == 0) ? "Pair" : "Impair";
}

int determinerColonne(int numero) { // Colonne
    if (numero == 0) return 0;
    return ((numero - 1) % 3) + 1; // Ex : 33 - 1 = 32 % 3 = 2 + 1 = 3, donc 3eme colonne
}

int determinerDouzaine(int numero) { // Douzaine
    if (numero == 0) return 0;
    return (numero - 1) / 12 + 1; // Ex : 33 - 1 = 32 / 12 = 2 + 1 = 3, donc 3eme douzaine
}

int calculerGains(int choix, int detail, int resultat, int mise) { // Calcul des gains
    switch (choix) {
        case 1: // numéro * 35
            return (resultat == detail) ? mise * 35 : 0;
        case 2: // couleur * 2
            return (detail == 1 && strcmp(determinerCouleur(resultat), "Rouge") == 0) ||
                   (detail == 2 && strcmp(determinerCouleur(resultat), "Noir") == 0) ? mise * 2 : 0;
        case 3: // parité * 2
            return (detail == 1 && strcmp(determinerParite(resultat), "Pair") == 0) ||
                   (detail == 2 && strcmp(determinerParite(resultat), "Impair") == 0) ? mise * 2 : 0;
        case 4: // manque/passe * 2
            return (detail == 1 && resultat >= 1 && resultat <= 18) ||
                   (detail == 2 && resultat >= 19 && resultat <= 36) ? mise * 2 : 0;
        case 5: // colonne * 3
            return (detail == determinerColonne(resultat)) ? mise * 3 : 0;
        case 6: // douzaine * 3
            return (detail == determinerDouzaine(resultat)) ? mise * 3 : 0;
        default:
            return 0; // Aucun gain
    }
}

void jouerManche(Joueur* joueur) { // Deroulement de la partie
    Mise mises[MAX_MISES];
    int nombreMises = 0;
    int continuer = 1;

    while (continuer == 1 && nombreMises < MAX_MISES) {
        printf("Vous avez %d$. Faites vos jeux !\n", joueur->solde); // on recupere le solde du joueur a l'adresse de soldes
        printf("1. Un numero\n2. Rouge/Noir\n3. Pair/Impair\n4. Manque/Passe\n5. Colonne\n6. Douzaine\n");
        printf("Entrez votre choix : ");
        scanf("%d", &mises[nombreMises].choix); // on stocke le choix de la mise dans le tableau de mise

        switch (mises[nombreMises].choix) { // on regarde le choix de la mise par rapport au tableau, et on redemande un choix
            case 1: // numero
                printf("Entrez le numero sur lequel vous voulez miser (0-36) : ");
                scanf("%d", &mises[nombreMises].detail);
                if (mises[nombreMises].detail < 0 || mises[nombreMises].detail > 36) {  // si le numero est pas entre 0 et 36
                    printf("Numero invalide. Reessayez.\n");
                    continue;
                }
                break;
            case 2: // couleur
                printf("Rouge (1) ou Noir (2) ? ");
                scanf("%d", &mises[nombreMises].detail);
                if (mises[nombreMises].detail < 1 || mises[nombreMises].detail > 2) {
                    printf("Choix invalide. Reessayez.\n");
                    continue;
                }
                break;
            case 3: // pair ou impair
                printf("Pair (1) ou Impair (2) ? ");
                scanf("%d", &mises[nombreMises].detail);
                if (mises[nombreMises].detail < 1 || mises[nombreMises].detail > 2) {
                    printf("Choix invalide. Reessayez.\n");
                    continue;
                }
                break;
            case 4: // manque ou passe
                printf("Manque (1) (1-18) ou Passe (2) (19-36) ? ");
                scanf("%d", &mises[nombreMises].detail);
                if (mises[nombreMises].detail < 1 || mises[nombreMises].detail > 2) {
                    printf("Choix invalide. Reessayez.\n");
                    continue;
                }
                break;
            case 5: // colonne
                printf("Colonne 1 (1), 2 (2) ou 3 (3) ? ");
                scanf("%d", &mises[nombreMises].detail);
                if (mises[nombreMises].detail < 1 || mises[nombreMises].detail > 3) {
                    printf("Choix invalide. Reessayez.\n");
                    continue;
                }
                break;
            case 6: // douzaine
                printf("Douzaine 1 (1-12), 2 (13-24) ou 3 (25-36) ? ");
                scanf("%d", &mises[nombreMises].detail);
                if (mises[nombreMises].detail < 1 || mises[nombreMises].detail > 3) {
                    printf("Choix invalide. Reessayez.\n");
                    continue;
                }
                break;
            default:
                printf("Choix invalide. Reessayez.\n");
                continue;
        }

        printf("Combien voulez-vous miser ? ");
        scanf("%d", &mises[nombreMises].montant); // on stocke le montant de la mise dans le tableau de mise

        if (mises[nombreMises].montant > joueur->solde || mises[nombreMises].montant <= 0) { // si le montant est superieur au solde ou inferieur a 0
            printf("Mise invalide. Reessayez.\n");
            continue;
        }

        joueur->solde -= mises[nombreMises].montant; // on retire le montant de l'argent du joueur
        nombreMises++; // on ajoute une mise (pour pouvoir les afficher apres)

        if (nombreMises < MAX_MISES) {
            printf("Voulez-vous ajouter une autre mise ? (1: Oui, 2: Non) ");
            scanf("%d", &continuer);
        } else {
            printf("Vous avez atteint le nombre maximum de mises.\n");
            continuer = 0; // On arrete la boucle
        }
    }

    int resultat = tirageNombre(); // BLING BLING BLING, le numero est tiré
    printf("La roulette a donne : %d (%s) | Colonne : %d | Douzaine : %d\n", // affiche tout sauf pair et impair (j'ai hesité a l'afficher pour vous monsieur Trancho je sais que vous avez du mal avec les maths)
           resultat, determinerCouleur(resultat), determinerColonne(resultat), determinerDouzaine(resultat));

    for (int i = 0; i < nombreMises; i++) { // pour chaque mise, on regarde si le joueur a gagné ou perdu
        int gains = calculerGains(mises[i].choix, mises[i].detail, resultat, mises[i].montant);
        if (gains > 0) {
            printf("Mise %d : Vous avez gagne %d$ !\n", i + 1, gains); // si il a gagné, affiche le numero de la mise + les gains
            joueur->solde += gains;
        } else {
            printf("Mise %d : Vous avez perdu %d$.\n", i + 1, mises[i].montant); // si il a perdu, affiche le numero de la mise + le montant de la mise
        }
    }

    printf("Votre solde actuel : %d$\n", joueur->solde);
}

// Fonction principale
int main() {
    srand(time(NULL));

    Joueur joueur;
    printf("Bienvenue au casino ! Quel est votre nom ? \n");
    scanf("%s", joueur.nom);
    joueur.solde = 1000;

    printf("Bienvenue %s, vous avez %d$ pour commencer.\n", joueur.nom, joueur.solde);

    while (joueur.solde > 0) {
        jouerManche(&joueur);

        if (joueur.solde == 0) {
            printf("Vous n'avez plus d'argent ! Merci d'avoir joue.\n"); // si le joueur n'a plus d'argent, on le remercie (pour nous avoir donner son argent) et on arrete le jeu
            exit(EXIT_SUCCESS);
        }

        printf("Voulez-vous continuer ? (1: Oui, 2: Non) ");
        int continuer;
        scanf("%d", &continuer);
        if (continuer != 1) {
            printf("Merci d'avoir joue, %s ! A bientot.\n", joueur.nom); // si le joueur ne veut pas continuer, on le remercie et on arrete le jeu
            exit(EXIT_SUCCESS);
        }
    }

    return 0;
}
