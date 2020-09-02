#ifndef __IA_H
#define __IA_H

// algorithme de recherche minimax
int minimax(grille oth, int joueur, int profondeur, int profondeurMax, int *l, char *c);

// alpha beta avec poids statiques
int alphabeta(grille oth, int joueur, int profondeur, int profondeurMax, int *l, char *c, int alpha, int beta);

// alpha beta avec fonctions heuristiques à composantes
int alphabeta2(grille oth, int joueur, int profondeur, int profondeurMax, int *l, char *c, int alpha, int beta);

#endif
