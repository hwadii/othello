#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "utilitaire.h"
#include "gameplay.h"
#include "ia.h"
#include "evaluation.h"
#include "interface.h"


int heuristiqueParametres(grille oth, int joueur) {
    int parite, coins, stab, nbc;
    char ordinateur, adv;
    if (joueur == 1) {
        ordinateur = 'X';
        adv = 'O';
    } else {
        ordinateur = 'O';
        adv = 'X';
    }

    parite =  100 * (nbPions(oth, ordinateur) - nbPions(oth, adv)) / (nbPions(oth, ordinateur) + nbPions(oth, adv));

    // if (coinsCaptures(oth, ordinateur) + coinsCaptures(oth, adv) != 0)  {
    //     coins = 100 * (coinsCaptures(oth, ordinateur) - coinsCaptures(oth, adv)) / (coinsCaptures(oth, ordinateur) + coinsCaptures(oth, adv));
    // } else coins = 0;

    // if (stabilite(oth, ordinateur) + stabilite(oth, adv) != 0)
    //     stab = 100 * (stabilite(oth, ordinateur) - stabilite(oth, adv)) / (stabilite(oth, ordinateur) + stabilite(oth, adv));
    // else stab = 0;

    // if (nbCoupsPossibles(oth, ordinateur) + nbCoupsPossibles(oth, adv) != 0)
    //     nbc = 100 * (nbCoupsPossibles(oth, ordinateur) - nbCoupsPossibles(oth, adv)) / (nbCoupsPossibles(oth, ordinateur) + nbCoupsPossibles(oth, adv));
    // else nbc = 0;

    return parite;
}


int nbCoupsPossibles(grille oth, int joueur) {
    int res = 0;
    int j;
    char i;
    for (i = 'A'; i <= 'H'; i++) {
        for (j = 1; j <= N; j++) {
            if (coupJouableTtDir(oth, joueur, i, j) && ((oth[j-1][colonneCharToInt(i)-1] == ' ' || oth[j-1][colonneCharToInt(i)-1] == '*'))) {
                res++;
            }
        }
    }
    return res;
}


int coinsCaptures(grille oth, char couleur) {
    int i, j;
    int lignes[2] = {0, 7};
    int colonnes[2] = {0, 7};
    int res = 0;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            if (oth[lignes[i]][colonnes[j]] == couleur) res = res + 10;
        }
    }
    return res;
}


int stabilite(grille oth, char couleur) {
    int res = 0, i, j;
    grille stab = {
        {1, -1, 0, 0, 0, 0, -1, 1},
        {-1, -1, -1, -1,-1, -1,-1, -1},
        {0, -1, -1, -1,-1, -1,-1, 0},
        {0, -1, -1, -1,-1, -1,-1, 0},
        {0, -1, -1, -1,-1, -1,-1, 0},
        {0, -1, -1, -1,-1, -1,-1, 0},
        {-1, -1, -1, -1,-1, -1,-1, -1},
        {1, -1, 0, 0, 0, 0, -1, 1},
    };

    for (i = 0; i < N ; i++) {
        for (j = 0; j < N; j++){
            if (oth[i][j] == couleur) res += stab[i][j];
        }
    }
    return res;
}


int poidsStatique(grille oth, int joueur) {
    int i, j;
    char ordinateur, adv;
    int parite, score = 0, mobilite;

    grille points = {
        {4, -3, 2, 2, 2, 2, -3, 4},
        {-3, -4,-1, -1, -1, -1,-4, -3},
        {2 , -1,  1, 0, 0, 1,  -1,  2},
        {2 , -1,  0, 1, 1, 0,  -1,  2},
        {2 , -1,  0, 1, 1, 0,  -1,  2},
        {2 , -1,  1, 0, 0, 1,  -1,  2},
        {-3, -4,-1, -1, -1, -1,-4, -3},
        {4, -3, 2, 2, 2, 2, -3, 4},
    };

    if (joueur == 1) {
        ordinateur = 'X';
        adv = 'O';
    } else {
        ordinateur = 'O';
        adv = 'X';
    }

    for (i = 0; i < N ; i++) {
        for (j = 0; j < N; j++){
            if (oth[i][j] == ordinateur) score += points[i][j];
            else if (oth[i][j] == adv) score -= points[i][j];
        }
    }
    return score;
}
