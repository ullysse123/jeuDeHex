#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "jouer.h"

int main(){
    Plateau plateau;
    Case caseJouer;
    Couleur gagner;
    plateau = creer_plateau(4);
    int joueurCourrant = 0;
    joueurCourrant = 1;
    do {
      affichage_plateau(plateau);
      caseJouer = jouer(plateau, joueurCourrant);
      printf("[tu_jouer] estFini >\n");
      gagner = estFini(plateau);
      affichage_plateau(plateau);
      sauvegarde_coup_tmp(caseJouer);
//       joueurCourrant = ((joueurCourrant)%2)+1;
      printf("[tu_jouer] couleur gagner = %d\n", gagner);
    } while (gagner == 0);
    printf("[tu_jouer] caseJouer : murDed = %d , murFin = %d\n", caseJouer->murDeb, caseJouer->murFin);
    suppr_Tmp();
    return 0;
}