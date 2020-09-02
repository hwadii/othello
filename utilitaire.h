#ifndef __UTILITAIRE_H
#define __UTILITAIRE_H

// fonction qui copie une grille
void copieGrille(grille src, grille dest);

// génère une liste de coups valides
void genererCoups(grille oth, int joueur, char colonne[], int ligne[]);

// fonction utilitaire qui néttoie la table
void clearTable(char colonne[], int ligne[]);

// fonction qui calcule la longueur d'une table
int taille(int t[]);

// vérifie si l'othellier est plein
int plein(grille oth);

// compte le nombre de pions sur l'othellier pour une couleur donnée
int nbPions(grille oth, char joueur);

// choix de la difficulté
void choixDifficulte(int *difficulte);

// demande à l'utilisateur la couleur de pion voulue
void choixCouleur();


int colonneCharToInt(char c);

#endif
