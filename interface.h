#ifndef __INTERFACE_H
#define __INTERFACE_H


// initialisation de la grille
void init_grille(grille oth);


// affichage de la grille à l'écran
void afficher_grille(grille oth);


// affiche les hints sur la grille
void aide(grille oth, int joueur);


// vérifie si la partie est terminée
int partieTerminee(grille oth);


// efface les hints
void cleanAide(grille oth);

// détermine le vainqueur de la partie s'il y en a un
void vainqueur(grille oth);

// demande à l'utilisateur s'il veut rejouer
void rejouer(grille oth, char *continuer, int *difficulte, int choix, int *numerochoisi);

// renvoie le numéro de joueur en fonction du pion choisi
int detjoueur();


// renvoie le joueur suivant
int changerJoueur(int joueur);

#endif
