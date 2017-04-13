#ifndef __CASE__H__
#define __CASE__H__

#include <stdio.h>
#include <stdlib.h>

typedef struct Position {
    int x;
    int y;
} Position;

typedef enum Couleur {
    ROUGE = 1, 
    NOIR  = 2, 
    VIDE  = 0
} Couleur;

typedef struct Case {
    Position pos;
    Couleur valeur;
} Case;

Case creerCase();
Case modifierCase(Case *caseModifier, Couleur valeur);
Couleur couleurCase(Case *x);
Position obtenirCoordonnee(Case *x);
void supprimerCase(Case *x);

#endif