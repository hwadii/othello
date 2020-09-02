#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "utilitaire.h"
#include "gameplay.h"
#include "ia.h"
#include "evaluation.h"
#include "interface.h"

int main(void)
{
    grille oth;
    int joueur = 1, ligne, profondeur = 0, ligneIA, choix, difficulte, difficulte2, numerochoisi;
    char colonne, continuer, colonneIA, piece;

    printf("\n==== Bienvenue sur le jeu Othello ====\n");
    printf("Choisissez un mode de jeu\n1. 1c1\n2. 1cIA\n3. IAcIA\n");
    scanf("%d", &choix);
    switch(choix) {
        case 1:
            init_grille(oth);
            choixCouleur();
            while (!partieTerminee(oth)) {
                printf("C'est au joueur %d de jouer.\n", joueur);
                aide(oth, joueur);
                afficher_grille(oth);
                printf("Noir %d - Blanc %d\n", nbPions(oth, 'X'), nbPions(oth, 'O'));
                if (nbCoupsPossibles(oth, joueur) != 0) {
                    demanderCoups(oth, joueur, &colonne, &ligne);
                    placer_coup(oth, joueur, colonne, ligne);
                } else {
                    printf("Le joueur %d ne peut pas jouer. Il passe son tour...\n", joueur);
                }
                
                joueur = changerJoueur(joueur);
                cleanAide(oth);

                rejouer(oth, &continuer, &difficulte, choix, NULL);
            }
            return 0;
        
        case 2:
            init_grille(oth);
            numerochoisi = detjoueur();
            printf("Vous êtes le joueur %d.\nL'ordinateur est le joueur %d.\n" , numerochoisi, 3-numerochoisi);
            choixDifficulte(&difficulte);
            while (!partieTerminee(oth)) {
                printf("C'est au joueur %d de jouer.\n", joueur);
                aide(oth, joueur);
                afficher_grille(oth);
                printf("Noir %d - Blanc %d\n", nbPions(oth, 'X'), nbPions(oth, 'O'));
                if ((joueur == numerochoisi+1) || (joueur == numerochoisi-1)) {
                    if (nbCoupsPossibles(oth, joueur) != 0) {
                        alphabeta(oth, joueur, profondeur, difficulte, &ligneIA, &colonneIA, -INF, INF);
                        placer_coup(oth, joueur, colonneIA, ligneIA);
                        printf("Le joueur %d a joué en %c%d.\n", joueur, colonneIA, ligneIA);
                    } else {
                        printf("Le joueur %d ne peut pas jouer. Il passe son tour...\n", joueur);
                    }
                } else if (joueur == numerochoisi) {
                    if (nbCoupsPossibles(oth, joueur) != 0) {
                        demanderCoups(oth, joueur, &colonne, &ligne);
                        placer_coup(oth, joueur, colonne, ligne);
                    } else {
                        printf("Le joueur %d ne peut pas jouer. Il passe son tour...\n", joueur);
                    }
                }
                joueur = changerJoueur(joueur);
                cleanAide(oth);

                rejouer(oth, &continuer, &difficulte, choix, &numerochoisi);
            }
            return 0;
        
        case 3:
            init_grille(oth);
            choixDifficulte(&difficulte);
            printf("Le niveau de l'IA est %d\n", difficulte);
            while (!partieTerminee(oth)) {
                printf("C'est au joueur %d de jouer.\n", joueur);
                aide(oth, joueur);
                afficher_grille(oth);
                printf("Noir %d - Blanc %d\n", nbPions(oth, 'X'), nbPions(oth, 'O'));
                if (joueur == 1) {
                    if (nbCoupsPossibles(oth, 1) != 0) {
                        alphabeta(oth, joueur, profondeur, difficulte, &ligneIA, &colonneIA, -INF, INF);
                        placer_coup(oth, joueur, colonneIA, ligneIA);
                        printf("Le joueur %d a joué en %c%d.\n", joueur, colonneIA, ligneIA);
                    } else {
                        printf("Le joueur %d ne peut pas jouer. Il passe son tour...\n", joueur);
                    }
                } else if (joueur == 2) {
                    if (nbCoupsPossibles(oth, 2) != 0) {
                        alphabeta2(oth, joueur, profondeur, difficulte, &ligneIA, &colonneIA, -INF, INF);
                        placer_coup(oth, joueur, colonneIA, ligneIA);
                        printf("Le joueur %d a joué en %c%d.\n", joueur, colonneIA, ligneIA);
                    } else {
                        printf("Le joueur %d ne peut pas jouer. Il passe son tour...\n", joueur);
                    }
                }
                joueur = changerJoueur(joueur);
                cleanAide(oth);

                rejouer(oth, &continuer, &difficulte, choix, NULL);
            }
            return 0;
    }

}