#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "utilitaire.h"
#include "gameplay.h"
#include "ia.h"
#include "evaluation.h"
#include "interface.h"


void init_grille(grille oth) {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            oth[i][j] = ' ';
        }
    }

    oth[N/2][N/2] = 'O';
    oth[N/2-1][N/2-1] = 'O';
    oth[N/2][N/2-1] = 'X';
    oth[N/2-1][N/2] = 'X';
}


void afficher_grille(grille oth) {
    int i, j;
    char a = 'A';

    printf("\n");
    for (i = 0; i < N; i++) {
        printf("  %c ", a);
        a++;
    }

    printf("\n+");
    for (i = 0; i < N; i++)
        printf("---+");
    printf("\n");
    for (i = 0; i < N; i++) {
        printf("|");
        for (j = 0; j < N; j++)
            printf(" %c |", oth[i][j]);
        printf(" %d\n+", i + 1);
        for (j = 0; j < N; j++)
            printf("---+");
        printf("\n");
    }
}


int detjoueur() {
    char couleur;
    printf("Choisissez une couleur. (X/O): ");
    scanf("\n%c", &couleur);
    if (couleur == 'X') {
        return 1;
    } else {
        return 2;
    }
}


int changerJoueur(int joueur) {
    return joueur%2+1;
}


void aide(grille oth, int joueur) {
  char k;
  int i,j;
    for (k = 'A'; k <= 'H'; k++) {
        for (j = 1; j <= 8; j++) {
            for (i = 1; i <= 8; i++) {
                if (oth[j-1][colonneCharToInt(k)-1] == ' ' && coupJouable(oth, joueur, k, j, i)) {
                    oth[j-1][colonneCharToInt(k)-1] = '*';
                }
            }
        }
    }
}


void cleanAide(grille oth) {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (oth[i][j] == '*')
                oth[i][j] = ' ';
        }
    }
}


int partieTerminee(grille oth) {
    if (plein(oth)) return 1;
    else if (nbCoupsPossibles(oth, 1) == 0 && nbCoupsPossibles(oth, 2) == 0) return 1;
    else return 0;
}


void vainqueur(grille oth) {
    int i, j, compteX = 0, compteO = 0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (oth[i][j] == 'X') compteX++;
            else if (oth[i][j] == 'O') compteO++;
        }
    }
    if (compteX > compteO) printf("Le joueur 1 a gagné.");
    else if (compteX == compteO) printf("Il y a égalité.");
    else printf("Le joueur 2 a gagné.");
}



void rejouer(grille oth, char *continuer, int *difficulte, int choix, int *numerochoisi) {
    char cont;
    if (partieTerminee(oth)) {
        afficher_grille(oth);
        printf("Noir %d - Blanc %d\n", nbPions(oth, 'X'), nbPions(oth, 'O'));
        printf("\nFin de la partie.\n");
        vainqueur(oth);
        printf("\nVoulez-vous rejouer ? (o/n): ");
        scanf("\n%c", &cont);
        *continuer = cont;
        if (*continuer == 'o'){
            init_grille(oth);
            if (choix == 1) {
                choixCouleur();
            } else if (choix == 2) {
                choixDifficulte(difficulte);
                *numerochoisi = detjoueur();
            } else {
                choixDifficulte(difficulte);
            }
        }
    }
}
