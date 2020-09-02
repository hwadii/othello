#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "utilitaire.h"
#include "gameplay.h"
#include "ia.h"
#include "evaluation.h"
#include "interface.h"


void choixCouleur() {
    char couleur;
    printf("Choisissez une couleur. (X/O): ");
    scanf("\n%c", &couleur);
    if (couleur == 'X') {
        printf("\nVous êtes le joueur 1.\n");
    } else {
        printf("\nVous êtes le joueur 2.\n");
    }
}

int colonneCharToInt(char c) {
    switch(c) {
        case 'A': return 1;
        case 'B': return 2;
        case 'C': return 3;
        case 'D': return 4;
        case 'E': return 5;
        case 'F': return 6;
        case 'G': return 7;
        case 'H': return 8;
    }
}


int plein(grille oth) {
    int casePleine = 1;
    int i, j;
    for (j = 1; j <= 8; j++) {
        for (i = 1; i <= 8; i++) {
            if (oth[i-1][j-1] == ' ') casePleine = 0;
        }
    }
    return casePleine;
}


void choixDifficulte(int *difficulte) {
    int diff;
    printf("Choisissez le niveau de l'IA. (1-5): ");
    scanf("\n%d", &diff);
    *difficulte = diff;
}

int nbPions(grille oth, char couleur) {
    int i, j;
    int nbPions = 0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (oth[i][j] == couleur) nbPions++;
        }
    }
    return nbPions;
}


void genererCoups(grille oth, int joueur, char colonne[], int ligne[]) {
    int i,k = 0;
    char j;

    clearTable(colonne, ligne);
    aide(oth, joueur);
    for (i = 1; i <= N; i++) {
        for (j = 'A'; j <= 'H'; j++) {
            if (oth[i-1][colonneCharToInt(j)-1] == '*') {
                colonne[k] = j;
                ligne[k] = i;
                k++;
            }
        }
    }
}


void clearTable(char colonne[], int ligne[]) {
    int k = 0;
    while (k < NBC) {
        colonne[k] = 0;
        ligne[k] = 0;
        k++;
    }
}


int taille(int t[]) {
    int i = 0;
    while (t[i] != 0 && i < NBC) {
        i++;
    }
    return i;
}


void copieGrille(grille src, grille dest) {
    memcpy(dest, src, 8 * 8 * sizeof(char));
}
