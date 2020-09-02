#ifndef __GAMEPLAY_H
#define __GAMEPLAY_H

// place un coup sur l'othellier s'il est valide
void placer_coup(grille oth, int joueur, char c, int l);

// vérifie si un coup est valide
int coupJouable(grille oth, int joueur, char c, int l, int dir);


// appelle la fonction coup jouable dans toutes les directions
int coupJouableTtDir(grille oth, int joueur, char c, int l);


// demande à l'utilisateur d'entrer la coordonnée de là où il veut placer son coup
void demanderCoups(grille oth, int joueur, char *colonne, int *ligne);


// met à jour l'othellier après qu'un utilisateur a placé un coup
void update(grille oth, int joueur, char c, int l);

#endif
