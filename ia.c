#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "utilitaire.h"
#include "gameplay.h"
#include "ia.h"
#include "evaluation.h"
#include "interface.h"


int minimax(grille oth, int joueur, int profondeur, int profondeurMax, int *l, char *c) {
    int meilleurL, score, meilleurScore;
    char meilleurC;
    int i;
    int coupsLignes[NBC];
    char coupsColonnes[NBC];
    int len; // taille du tableau
    // si on atteint une feuille
    if (profondeur == profondeurMax)
        return poidsStatique(oth, joueur);

    else {
        // genere une liste de coups valides
        genererCoups(oth, joueur, coupsColonnes, coupsLignes);
        len = taille(coupsLignes);

        // si la liste est vide
        if (len == 0) {
            return poidsStatique(oth, joueur);
        } else {
            meilleurScore = -INF;
            for (i = 0; i < len; i++) {
                // place un coup sur la grille copiée pour anticiper un scénario
                grille copie;
                copieGrille(oth, copie);
                aide(copie, joueur);
                placer_coup(copie, joueur, coupsColonnes[i], coupsLignes[i]);
                cleanAide(copie);
                // appel récursif
                score = -minimax(copie, changerJoueur(joueur), profondeur, profondeurMax-1, l, c);
                // si le score de la feuille est supérieur au score de la feuille précédente
                if (score > meilleurScore) {
                    meilleurScore = score;
                    meilleurL = coupsLignes[i];
                    meilleurC = coupsColonnes[i];
                }
            }
            // renvoie le meilleur coup
            *l = meilleurL;
            *c = meilleurC;
            return meilleurScore;
        }
    }
}


int alphabeta(grille oth, int joueur, int profondeur, int profondeurMax, int *l, char *c, int alpha, int beta) {
    int meilleurL, score, meilleurScore;
    char meilleurC;
    int i,j;
    int coupsLignes[NBC];
    char coupsColonnes[NBC];
    int len; // taille du tableau

    if (profondeur == profondeurMax)
        return poidsStatique(oth, joueur);

    genererCoups(oth, joueur, coupsColonnes, coupsLignes);
    len = taille(coupsLignes);
    if (len == 0) return poidsStatique(oth, joueur);
    for (i = 0; i < len; i++) {
        grille copie;
        copieGrille(oth, copie);
        aide(copie, joueur);
        placer_coup(copie, joueur, coupsColonnes[i], coupsLignes[i]);
        cleanAide(copie);
        score = -alphabeta(copie, changerJoueur(joueur), profondeur, profondeurMax-1, l, c, -beta, -alpha);
        if (score >= alpha) {
            alpha = score;
            meilleurL = coupsLignes[i];
            meilleurC = coupsColonnes[i];
            if (alpha >= beta) {
                break;
            }
        }
    }
    *l = meilleurL;
    *c = meilleurC;
    return alpha;
}


int alphabeta2(grille oth, int joueur, int profondeur, int profondeurMax, int *l, char *c, int alpha, int beta) {
    int meilleurL, score, meilleurScore;
    char meilleurC;
    int i,j;
    int coupsLignes[NBC];
    char coupsColonnes[NBC];
    int len; // taille du tableau

    if (profondeur == profondeurMax)
        return heuristiqueParametres(oth, joueur);

    genererCoups(oth, joueur, coupsColonnes, coupsLignes);
    len = taille(coupsLignes);
    if (len == 0) return heuristiqueParametres(oth, joueur);
    for (i = 0; i < len; i++) {
        grille copie;
        copieGrille(oth, copie);
        aide(copie, joueur);
        placer_coup(copie, joueur, coupsColonnes[i], coupsLignes[i]);
        cleanAide(copie);
        score = -alphabeta2(copie, changerJoueur(joueur), profondeur, profondeurMax-1, l, c, -beta, -alpha);
        if (score >= alpha) {
            alpha = score;
            meilleurL = coupsLignes[i];
            meilleurC = coupsColonnes[i];
            if (alpha >= beta) {
                break;
            }
        }
    }
    *l = meilleurL;
    *c = meilleurC;
    return alpha;
}
