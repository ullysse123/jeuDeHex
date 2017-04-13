#ifndef __PLATEAU__H__
#define __PLATEAU__H__

#include <stdio.h>
#include <stdlib.h>

struct Case;

typedef struct Plateau {
    int taille;
    struct Case *nord;
    struct Case *sud;
    struct Case *est;
    struct Case *ouest;
} Plateau;

Plateau *creer_plateau(int taille);
void affichage_plateau(Plateau *plateau);


// Couleur estFini(Plateau *plateau);
// int taillePlateau(Plateau *plateau);
// int plusGrandGroupe(Plateau *plateau);
// void afficherPlateau(Plateau *plateau);
// int nombreCaseCouleur(Plateau *plateau);
// void supprimerPlateau(Plateau *plateau);

#endif