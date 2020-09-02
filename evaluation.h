#ifndef _EVALUATION_H
#define _EVALUATION_H

// table qui attribue une note de qualité à chaque case de l'othellier
int poidsStatique(grille oth, int joueur);

// eval qui prend en compte différents critères
int heuristiqueParametres(grille oth, int joueur);

// nb de coups possibles pour un joueur
int nbCoupsPossibles(grille oth, int joueur);


// nb de coins capturés
int coinsCaptures(grille oth, char couleur);

// table qui attribue une note de stabilité à chaque case de l'othellier
int stabilite(grille oth, char couleur);

#endif
