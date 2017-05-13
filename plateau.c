#include "plateau.h"
#include "case.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


Plateau creer_plateau(int taille) {
    printf("[creer_plateau] Creation du plateau.\n"); // Aide pour le dev
    Plateau plateau = malloc(sizeof(struct s_Plateau));
    plateau->taille = 4;

    /* construction du sommet nord */
    plateau->nord = creer_case(0,0);

    /* on relie les sommets entre eux pour simplifier la construction du plateau */
    construction_lien_case(plateau, plateau->nord);

    /* on construit les autres case du plateau en les ajoutants directement au plateau */
    Case nouvelle_case;

    int ligne, colonne;
    for(ligne = 0; ligne < taille; ligne++) {
        for(colonne = 0; colonne < taille; colonne++) {
            /* on saute le sommet nord, il est deja creer */
            if ((ligne == 0 && colonne == 0))
                continue;
                /* on creer la case et on edite les liens */
                nouvelle_case = creer_case(ligne, colonne);
                construction_lien_case(plateau, nouvelle_case);
        }
        printf("\n");
    }
    printf("\n");
    printf("\n");

    return plateau;
}

void construction_lien_case(Plateau plateau, Case x) {
    int ligne = x->pos.ligne;
    int colonne = x->pos.colonne;
    int taille = plateau->taille-1;

    printf("    [construction_lien_case] Creations des liens.\n"); // Aide pour le dev
    
    if (colonne == 0) {
        x->lien[4] = NULL;
        x->lien[5] = NULL;        
    } else if (colonne == taille) {
        x->lien[1] = NULL;
        x->lien[2] = NULL;
        x->lien[5] = obtenir_case(plateau, ligne, colonne-1);
        x->lien[5]->lien[2] = x;
    } else {
        x->lien[5] = obtenir_case(plateau, ligne, colonne-1);
        x->lien[5]->lien[2] = x;
    }
    
    if (ligne == 0) {
        x->lien[0] = NULL;
        x->lien[1] = NULL;
    } else if (ligne == taille) {
        x->lien[3] = NULL;
        x->lien[4] = NULL;
        x->lien[0] = obtenir_case(plateau, ligne-1, colonne);
        x->lien[0]->lien[3] = x;
    } else {
        x->lien[0] = obtenir_case(plateau, ligne-1, colonne);
        x->lien[0]->lien[3] = x;
    }
}

Case obtenir_case(Plateau plateau, int ligne, int colonne) {
    Case case_chercher = plateau->nord;

    /* on parcours le plateau jusqu'a etre a la bonne ligne */
    while((case_chercher->pos.ligne != ligne)) {
        case_chercher = case_chercher->lien[3];
    }
    /* on parcours le plateau jusqu'a etre a la bonne colonne */
    while((case_chercher->pos.colonne != colonne)) {
        case_chercher = case_chercher->lien[2];
    }

    return case_chercher;
}

char couleurToChar(Case c){
  switch ((int)c->valeur) {
    case 1 :
      return 'o';
      break;
    case 2:
      return '*';
      break;
    default:
      return '.';
  }
}

void affichage_plateau(Plateau plateau) {
    Case case_courrante_colonne = plateau->nord;
    Case case_courrante_ligne = plateau->nord;
    int nombre_espace = 1;
    while (case_courrante_ligne != NULL) {
        
        while (case_courrante_colonne != NULL) {
            //printf("[%d, %d]", case_courrante_colonne->pos.ligne, case_courrante_colonne->pos.colonne);
	    printf("[%c] ", couleurToChar(case_courrante_colonne));
            case_courrante_colonne = case_courrante_colonne->lien[2];
        }
        printf("\n");
        int i;
        for(i=0; i<(nombre_espace*2); i++)
            printf(" ");
        
        case_courrante_ligne = case_courrante_ligne->lien[3];
        case_courrante_colonne = case_courrante_ligne;
        
        nombre_espace++;
    }
}

int taillePlateau(Plateau plateau) {
  return (plateau->taille);
}


int nombreCaseCouleur(Plateau plateau){
  Case case_courrante_ligne = plateau->nord;
  Case case_courrante_colonne = plateau->nord;
  int sum = 0;
  while (case_courrante_ligne != NULL) {
        
        while (case_courrante_colonne != NULL) {
            if ((int)case_courrante_colonne->valeur != 0){
	      sum ++;
	    }
            case_courrante_colonne = case_courrante_colonne->lien[2];
        }        
        case_courrante_ligne = case_courrante_ligne->lien[3];
        case_courrante_colonne = case_courrante_ligne;
    }
    return sum;
}


// Couleur estFini(Plateau *plateau);
// int plusGrandGroupe(Plateau *plateau);

// void supprimerPlateau(Plateau *plateau);
