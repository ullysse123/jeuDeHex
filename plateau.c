#include "plateau.h"
#include "case.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


Plateau creer_plateau(int taille) {
    printf("[creer_plateau] Creation du plateau.\n"); // Aide pour le dev
    Plateau plateau = malloc(sizeof(struct s_Plateau));
    if (taille<2) plateau->taille = 2;
    else plateau->taille = taille;

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

void construction_lien_case(Plateau plateau, Case x){
    
    int ligne = x->pos.ligne;
    int colonne = x->pos.colonne;
    int taille = plateau->taille-1;
    
    if(colonne == 0){
        if(ligne == 0){
            //Cas 1 : Angle en haut a gauche
            x->lien[0]=NULL;
            x->lien[1]=NULL;
            x->lien[4]=NULL;
            x->lien[5]=NULL;
        }else{
            if(ligne == taille){
                //Cas 2 : Angle en bas a gauche
                x->lien[0]=obtenir_case(plateau,ligne-1,colonne);
                x->lien[0]->lien[3]=x;
                x->lien[1]=obtenir_case(plateau,ligne-1,colonne+1);
                x->lien[1]->lien[4]=x;
                x->lien[3]=NULL;
                x->lien[4]=NULL;
                x->lien[5]=NULL;
            }else{
                //Cas 3 : Face gauche
                x->lien[0]=obtenir_case(plateau,ligne-1,colonne);
                x->lien[0]->lien[3]=x;
                x->lien[1]=obtenir_case(plateau,ligne-1,colonne+1);
                x->lien[1]->lien[4]=x;
                x->lien[4]=NULL;
                x->lien[5]=NULL;
            }
        }
    }else{
        if(colonne == taille){
            if(ligne == 0){
                //Cas 4 : Angle en haut a droite
                x->lien[0]=NULL;
                x->lien[1]=NULL;
                x->lien[2]=NULL;
                x->lien[5]=obtenir_case(plateau,ligne,colonne-1);
            }else{
                if(ligne == taille){
                    //Cas 5 : Angle en bas a droite
                    x->lien[0]=obtenir_case(plateau,ligne-1,colonne);
                    x->lien[0]->lien[3]=x;
                    x->lien[1]=NULL;
                    x->lien[2]=NULL;
                    x->lien[3]=NULL;
                    x->lien[4]=NULL;
                    x->lien[5]=obtenir_case(plateau,ligne,colonne-1);
                    x->lien[5]->lien[2]=x;
                }else{
                    //Cas 6 : Face Droite
                    x->lien[0]=obtenir_case(plateau,ligne-1,colonne);
                    x->lien[0]->lien[3]=x;
                    x->lien[1]=NULL;
                    x->lien[2]=NULL;
                    x->lien[5]=obtenir_case(plateau,ligne,colonne-1);
                    x->lien[5]->lien[2]=x;
                }
            }
        }else{
            if(ligne == 0){
                //Cas 7 : Face haute
                x->lien[0]=NULL;
                x->lien[1]=NULL;
                x->lien[5]=obtenir_case(plateau,ligne,colonne-1);
                x->lien[5]->lien[2]=x;
            }else{
                if(ligne == taille){
                    //Cas 8 : Face Basse
                    x->lien[0]=obtenir_case(plateau,ligne-1,colonne);
                    x->lien[0]->lien[3]=x;
                    x->lien[1]=obtenir_case(plateau,ligne-1,colonne-1);
                    x->lien[1]->lien[4]=x;
                    x->lien[3]=NULL;
                    x->lien[4]=NULL;
                    x->lien[5]=obtenir_case(plateau,ligne,colonne-1);
                    x->lien[5]->lien[2]=x;
                }else{
                    //Cas 9 : Centre
                    x->lien[0]=obtenir_case(plateau,ligne-1,colonne);
                    x->lien[0]->lien[3]=x;
                    x->lien[1]=obtenir_case(plateau,ligne-1,colonne+1);
                    x->lien[1]->lien[4]=x;
                    x->lien[5]=obtenir_case(plateau,ligne,colonne-1);
                    x->lien[5]->lien[2]=x;
                }
            }
        }
    }
    
}

// void construction_lien_case(Plateau plateau, Case x) {
//     
//     int ligne = x->pos.ligne;
//     int colonne = x->pos.colonne;
//     int taille = plateau->taille-1;
// 
//     printf("    [construction_lien_case] Creations des liens.\n"); // Aide pour le dev
//     
//     if (colonne == 0) {
//         x->lien[4] = NULL;
//         x->lien[5] = NULL;        
//     } else if (colonne == taille) {
//         x->lien[1] = NULL;
//         x->lien[2] = NULL;
//         x->lien[5] = obtenir_case(plateau, ligne, colonne-1);
//         x->lien[5]->lien[2] = x;
//     } else {
//         x->lien[5] = obtenir_case(plateau, ligne, colonne-1);
//         x->lien[5]->lien[2] = x;
//     }
//     
//     if (ligne == 0) {
//         x->lien[0] = NULL;
//         x->lien[1] = NULL;
//     } else if (ligne == taille) {
//         x->lien[3] = NULL;
//         x->lien[4] = NULL;
//         x->lien[0] = obtenir_case(plateau, ligne-1, colonne);
//         x->lien[0]->lien[3] = x;
//     } else {
//         x->lien[0] = obtenir_case(plateau, ligne-1, colonne);
//         x->lien[0]->lien[3] = x;
//     }
// }

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


// Couleur estFini(Plateau plateau);
// int plusGrandGroupe(Plateau plateau);

void supprimerPlateau(Plateau *plateau){
    
    Case case_courrante = (*plateau)->nord;
    Case case_suivante = case_courrante->lien[2];
    int taille = (*plateau)->taille;
    
    //Tant que case_suivante != NULL on continue
    while (case_suivante != NULL){
        //Si case->colonne == 0 alors
        //Parcours vers la droite tant qu case->colonne != taille-1
        if(case_courrante->pos.colonne == 0 && case_suivante != NULL){
            
            while (case_courrante->pos.colonne != taille-1) {
                supprimerCase(case_courrante);
                case_courrante = case_suivante;
                if(case_courrante->pos.colonne != taille-1){
                    case_suivante = case_courrante->lien[2];
                }else{
                    if(case_courrante->lien[3] != NULL){
                        case_suivante = case_courrante->lien[3];
                    }else{
                        case_suivante = NULL;
                    }
                }
            }
        }
        //Preparation au parcours vers la gauche
        if(case_suivante != NULL){
            case_courrante = case_suivante;
            case_suivante = case_courrante->lien[5];
        }
        //Si case->colonne == taille-1 alors
        //Parcours vers la gauche tant que case->colonne != 0
        if(case_courrante->pos.colonne == taille-1 && case_suivante != NULL){
            
            while (case_courrante->pos.colonne != 0){
                supprimerCase(case_courrante);
                case_courrante = case_suivante;
                if(case_courrante->pos.colonne != 0){
                    case_suivante = case_courrante->lien[5];
                }else{
                    if(case_courrante->lien[3] != NULL){
                        case_suivante = case_courrante->lien[3];
                    }else{
                        case_suivante = NULL;
                    }
                }
            }
        }
        //Preparation au parcours vers la droite
        if(case_suivante != NULL){
            case_courrante = case_suivante;
            case_suivante = case_courrante->lien[2];
        }
    }
    //On supprime la derniere case restante
    supprimerCase(case_courrante);
    //On supprime le plateau
    free(plateau);
}
