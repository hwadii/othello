#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "utilitaire.h"
#include "ia.h"
#include "gameplay.h"
#include "evaluation.h"
#include "interface.h"


void placer_coup(grille oth, int joueur, char c, int l) {
    char pion;
    int col;

    if (joueur == 1) pion = 'X';
    else pion = 'O';

    col = colonneCharToInt(c);
    if (coupJouableTtDir(oth, joueur, c, l) && oth[l-1][col-1] == '*') oth[l-1][col-1] = pion;
    update(oth, joueur, c, l);
}


int coupJouable(grille oth, int joueur, char c, int l, int dir) {
    int i = 0;
    char pionAdv;
    if (joueur == 1) pionAdv = 'O';
    else pionAdv = 'X';

    if (dir == 1) {
        do {
            l--;
            i++;
        } while (oth[l-1][colonneCharToInt(c)-1] == pionAdv);
        if (l < 1 || l > 8) return 0;
        if (colonneCharToInt(c) < 1 || colonneCharToInt(c) > 8) return 0;
        if (i == 1 && oth[l-1][colonneCharToInt(c)-1] != pionAdv) return 0;
        if (oth[l-1][colonneCharToInt(c)-1] != ' ' && oth[l-1][colonneCharToInt(c)-1] != '*') return 1;

    } else if (dir == 2) {
        do {
            l++;
            i++;
        } while (oth[l-1][colonneCharToInt(c)-1] == pionAdv);
        if (l < 1 || l > 8) return 0;
        if (colonneCharToInt(c) < 1 || colonneCharToInt(c) > 8) return 0;
        if (i == 1 && oth[l-1][colonneCharToInt(c)-1] != pionAdv) return 0;
        if (oth[l-1][colonneCharToInt(c)-1] != ' ' && oth[l-1][colonneCharToInt(c)-1] != '*') return 1;

    } else if (dir == 3) {
        do {
            c++;
            i++;
        } while (oth[l-1][colonneCharToInt(c)-1] == pionAdv);
        if (l < 1 || l > 8) return 0;
        if (colonneCharToInt(c) < 1 || colonneCharToInt(c) > 8) return 0;
        if (i == 1 && oth[l-1][colonneCharToInt(c)-1] != pionAdv) return 0;
        if (oth[l-1][colonneCharToInt(c)-1] != ' ' && oth[l-1][colonneCharToInt(c)-1] != '*') return 1;

    } else if (dir == 4) {
        do {
            c--;
            i++;
        } while (oth[l-1][colonneCharToInt(c)-1] == pionAdv);
        if (l < 1 || l > 8) return 0;
        if (colonneCharToInt(c) < 1 || colonneCharToInt(c) > 8) return 0;
        if (i == 1 && oth[l-1][colonneCharToInt(c)-1] != pionAdv) return 0;
        if (oth[l-1][colonneCharToInt(c)-1] != ' ' && oth[l-1][colonneCharToInt(c)-1] != '*') return 1;

    } else if (dir == 5) {
        do {
            l--;
            c--;
            i++;
        } while (oth[l-1][colonneCharToInt(c)-1] == pionAdv);
        if (l < 1 || l > 8) return 0;
        if (colonneCharToInt(c) < 1 || colonneCharToInt(c) > 8) return 0;
        if (i == 1 && oth[l-1][colonneCharToInt(c)-1] != pionAdv) return 0;
        if (oth[l-1][colonneCharToInt(c)-1] != ' ' && oth[l-1][colonneCharToInt(c)-1] != '*') return 1;

    } else if (dir == 6) {
        do {
            l--;
            c++;
            i++;
        } while (oth[l-1][colonneCharToInt(c)-1] == pionAdv);
        if (l < 1 || l > 8) return 0;
        if (colonneCharToInt(c) < 1 || colonneCharToInt(c) > 8) return 0;
        if (i == 1 && oth[l-1][colonneCharToInt(c)-1] != pionAdv) return 0;
        if (oth[l-1][colonneCharToInt(c)-1] != ' ' && oth[l-1][colonneCharToInt(c)-1] != '*') return 1;

    } else if (dir == 7) {
        do {
            l++;
            c--;
            i++;
        } while (oth[l-1][colonneCharToInt(c)-1] == pionAdv);
        if (l < 1 || l > 8) return 0;
        if (colonneCharToInt(c) < 1 || colonneCharToInt(c) > 8) return 0;
        if (i == 1 && oth[l-1][colonneCharToInt(c)-1] != pionAdv) return 0;
        if (oth[l-1][colonneCharToInt(c)-1] != ' ' && oth[l-1][colonneCharToInt(c)-1] != '*') return 1;

    } else if (dir == 8) {
        do {
            l++;
            c++;
            i++;
        } while (oth[l-1][colonneCharToInt(c)-1] == pionAdv);
        if (l < 1 || l > 8) return 0;
        if (colonneCharToInt(c) < 1 || colonneCharToInt(c) > 8) return 0;
        if (i == 1 && oth[l-1][colonneCharToInt(c)-1] != pionAdv) return 0;
        if (oth[l-1][colonneCharToInt(c)-1] != ' ' && oth[l-1][colonneCharToInt(c)-1] != '*') return 1;
    }

    return 0;
}


int coupJouableTtDir(grille oth, int joueur, char c, int l) {
    int ok = 0, dir = 1, vrai;
    while (ok == 0 && dir <= 8) {
        vrai = coupJouable(oth, joueur, c, l, dir);
        dir++;
        if (vrai) ok = 1;
    }
    return ok;
}


void demanderCoups(grille oth, int joueur, char *colonne, int *ligne) {
    char col;
    int lig;
    do {
        printf("Quelle colonne? ");
        scanf("\n%c", &col);
        printf("Quelle ligne? ");
        scanf("\n%d", &lig);
    } while (!coupJouableTtDir(oth, joueur, col, lig) || oth[lig-1][colonneCharToInt(col)-1] != '*');
    *colonne = col;
    *ligne = lig;
}


void update(grille oth, int joueur, char c, int l) {
    int i, j;
    char pionJ, pionAdv;
    if (joueur == 1) {
        pionJ = 'X';
        pionAdv = 'O';
    } else {
        pionJ = 'O';
        pionAdv = 'X';
    }

    if (coupJouable(oth, joueur, c, l, 1) && oth[l-1][colonneCharToInt(c)-1] == pionJ) {
        i = l-1;
        while (oth[i-1][colonneCharToInt(c)-1] == pionAdv) {
            oth[i-1][colonneCharToInt(c)-1] = pionJ;
            i--;
        }
    }

    if (coupJouable(oth, joueur, c, l, 2) && oth[l-1][colonneCharToInt(c)-1] == pionJ) {
        i = l+1;
        while (oth[i-1][colonneCharToInt(c)-1] == pionAdv) {
            oth[i-1][colonneCharToInt(c)-1] = pionJ;
            i++;
        }
    }

    if (coupJouable(oth, joueur, c, l, 3) && oth[l-1][colonneCharToInt(c)-1] == pionJ) {
        j = colonneCharToInt(c)+1;
        while (oth[l-1][j-1] == pionAdv) {
            oth[l-1][j-1] = pionJ;
            j++;
        }
    }

    if (coupJouable(oth, joueur, c, l, 4) && oth[l-1][colonneCharToInt(c)-1] == pionJ) {
        j = colonneCharToInt(c)-1;
        while (oth[l-1][j-1] == pionAdv) {
            oth[l-1][j-1] = pionJ;
            j--;
        }
    }

    if (coupJouable(oth, joueur, c, l, 5) && oth[l-1][colonneCharToInt(c)-1] == pionJ) {
        j = colonneCharToInt(c)-1;
        i = l-1;
        while (oth[i-1][j-1] == pionAdv) {
            oth[i-1][j-1] = pionJ;
            i--;
            j--;
        }
    }

    if (coupJouable(oth, joueur, c, l, 6) && oth[l-1][colonneCharToInt(c)-1] == pionJ) {
        j = colonneCharToInt(c)+1;
        i = l-1;
        while (oth[i-1][j-1] == pionAdv) {
            oth[i-1][j-1] = pionJ;
            i--;
            j++;
        }
    }

    if (coupJouable(oth, joueur, c, l, 7) && oth[l-1][colonneCharToInt(c)-1] == pionJ) {
        j = colonneCharToInt(c)-1;
        i = l+1;
        while (oth[i-1][j-1] == pionAdv) {
            oth[i-1][j-1] = pionJ;
            i++;
            j--;
        }
    }

    if (coupJouable(oth, joueur, c, l, 8) && oth[l-1][colonneCharToInt(c)-1] == pionJ) {
        j = colonneCharToInt(c)+1;
        i = l+1;
        while (oth[i-1][j-1] == pionAdv) {
            oth[i-1][j-1] = pionJ;
            i++;
            j++;
        }
    }
}
