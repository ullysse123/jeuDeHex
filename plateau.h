#ifndef __PLATEAU__H__
#define __PLATEAU__H__

#include <stdio.h>
#include <stdlib.h>

#include "case.h"

typedef struct Plateau {
    int nb_niveau;
    struct Case *Nord;
    struct Case *Sud;
    struct Case *Est;
    struct Case *Ouest;
} Plateau;

Plateau *creerPlateau(int niveau);
Couleur estFini(Plateau *plateau);
int taillePlateau(Plateau *plateau);
int plusGrandGroupe(Plateau *plateau);
void afficherPlateau(Plateau *plateau);
int nombreCaseCouleur(Plateau *plateau);
void supprimerPlateau(Plateau *plateau);

#endif