#ifndef __CASE__H__
#define __CASE__H__

#include <stdio.h>
#include <stdlib.h>

#include "plateau.h"

typedef struct Position {
    int ligne;
    int colonne;
} Position;

typedef enum Couleur {
    ROUGE = 1, 
    NOIR  = 2, 
    VIDE  = 0
} Couleur;

typedef struct Case {
    Position pos;
    Couleur valeur;
    struct Case *lien[6];
} Case;

Case *creer_case(int ligne, int colonne);
void construction_lien_case(Plateau *plateau, Case *x);


// Case modifierCase(Case *caseModifier, Couleur valeur);
// Couleur couleurCase(Case *x);
// Position obtenirCoordonnee(Case *x);
// void supprimerCase(Case *x);

#endif