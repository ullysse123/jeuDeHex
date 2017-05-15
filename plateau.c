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
                x->lien[5]->lien[2]=x;
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
  // on regarde la valeur de la case
  switch ((int)c->valeur) {
    case 1 :
      // case blanche
      return 'o';
      break;
    case 2:
      // case noir
      return '*';
      break;
    default:
      // case vide
      return '.';
  }
}

void affichage_plateau(Plateau plateau) {
  // 
  Case case_courrante_colonne = plateau->nord;
  Case case_courrante_ligne = plateau->nord;
  int nombre_espace = 1;
  // parcour du plateau de jeu
  while (case_courrante_ligne != NULL) {
      
    while (case_courrante_colonne != NULL) {
      //affichage de la couleur de la case
      printf("[%c] ", couleurToChar(case_courrante_colonne));
      case_courrante_colonne = case_courrante_colonne->lien[2];
    }
    // fin de ligne
    printf("\n");
    // mise en forme du plateau (pour avoir le décalage
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
  // variable de comptage des case déjà occupés
  int sum = 0;
  // parcour du plateau
  while (case_courrante_ligne != NULL) {
        
        while (case_courrante_colonne != NULL) {
	  // si la case n'est pas vide on ajoute 1 à la somme
            if ((int)case_courrante_colonne->valeur != 0){
	      sum ++;
	    }
            case_courrante_colonne = case_courrante_colonne->lien[2];
        }        
        case_courrante_ligne = case_courrante_ligne->lien[3];
        case_courrante_colonne = case_courrante_ligne;
    }
    // en retourne le résultat
    return sum;
}


Couleur estFini(Plateau plateau){
    
    //La couleur noir pour gagner doit relier le coté gauche au coté doit ( colonne 0 a colonne taille-1 )
    //La couleur rouge pour gagner doit relier le coté haut au coté bas ( ligne 0 a ligne taille-1 )
    
    //On initialise nos variables
    int i,j,k;
    Case case_courrante;
    printf("\n");
    //On parcours toutes les lignes de colonne 0 a colonne taille-1 
    //Parcour de gauche a droite
    for( i = 0; i < (plateau->taille); i++ ){ //Colonne fixé
        for (j = 0; j < (plateau->taille); j++){ //Ligne fixé
            case_courrante = obtenir_case(plateau,i,j);
            
            if((case_courrante->pos.colonne == 0) && (case_courrante->valeur == NOIR) && (case_courrante->murDeb == false)){
                case_courrante->murDeb = true;
                
            }else{
                if ( case_courrante->valeur == NOIR){
                    if(case_courrante->pos.ligne == 0){
                        //Cas ou on a que les lien 5 et 4 a traiter
                        for( k = 4; k< 6; k++ ){
                            if((case_courrante->lien[k]->valeur == NOIR) && (case_courrante->lien[k]->murDeb == true)){
                        
                                    case_courrante->murDeb = true;
                        
                                }
                        }
                    }else{
                        if(case_courrante->pos.ligne == plateau->taille-1){
                            //Cas ou on a que les lien 5 et 0 a traiter
                            for( k = 5; k < 1; k = (k+1)%6){
                                if((case_courrante->lien[k]->valeur == NOIR) && (case_courrante->lien[k]->murDeb == true)){
                        
                                    case_courrante->murDeb = true;
                        
                                }
                            }
                        }else{
                            //Parcours les liens allant vers la gauche ( 4->5->0 ) si on est pas sur un bord
                            for( k = 4; k < 1; k = (k+1)%6){
                                if((case_courrante->lien[k]->valeur == NOIR) && (case_courrante->lien[k]->murDeb == true)){
                                    
                                    case_courrante->murDeb = true;
                        
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    //On parcours toutes les lignes de colonne taille-1 a colonne 0
    //Parcour de droite a gauche
    for( i = (plateau->taille-1); i >= 0; i-- ){//Colonne fixé
        for( j = 0; j < (plateau->taille); j++){//Ligne fixé
            
            case_courrante = obtenir_case(plateau,i,j);
            
            if((case_courrante->pos.colonne == (plateau->taille-1)) && (case_courrante->valeur == NOIR) && (case_courrante->murFin == false)){
                
                case_courrante->murFin = true;
                
            }else{
                if ( case_courrante->valeur == NOIR ){
                    if( case_courrante->pos.ligne == 0 ){
                        //Cas ligne du haut
                        for( k = 2; k < 4; k++ ){
                            if((case_courrante->lien[k]->valeur == NOIR) && (case_courrante->lien[k]->murFin == true)){
                        
                                    case_courrante->murFin = true;
                        
                            }
                        }
                    }else{
                        if( case_courrante->pos.ligne == plateau->taille-1){
                            //Cas ligne du bas
                            for( k = 1; k < 3; k++){
                                if((case_courrante->lien[k]->valeur == NOIR) && (case_courrante->lien[k]->murFin == true)){
                            
                                    case_courrante->murFin = true;
                            
                                }
                            }
                        }else{
                            //Parcours les liens allant vers la droite (1->2->3)
                            for( k = 1; k < 4; k++ ){
                                if((case_courrante->lien[k]->valeur == NOIR) && (case_courrante->lien[k]->murFin == true)){
                                    
                                    case_courrante->murFin = true;
                            
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    //On parcours toutes les colonnes de ligne 0 a ligne taille-1
    //parcours de haut en bas
    for( j = 0; j < (plateau->taille); j++){ //Ligne fixé
        for( i = 0; i < (plateau->taille); i++){//colonne fixé
            
            case_courrante = obtenir_case(plateau,i,j);
            
            if((case_courrante->pos.ligne == 0) && (case_courrante->valeur == ROUGE) && (case_courrante->murDeb == false)){
                
                case_courrante->murDeb = true;
                
            }else{
                if ( case_courrante->valeur == ROUGE ){
                    if(case_courrante->pos.colonne == (plateau->taille-1)){
                        //Cas colonne de droite
                        
                        if((case_courrante->lien[0]->valeur == ROUGE) && (case_courrante->lien[0]->murDeb == true)){
                            
                            case_courrante->murDeb = true;
                        
                        }
                    }else{
                        for ( k = 0; k < 2; k++ ){
                            if ((case_courrante->lien[k]->valeur == ROUGE) && (case_courrante->lien[k]->murDeb == true)){
                                
                                case_courrante->murDeb = true;
                            
                            }
                        }
                    }
                }
            }
        }
    }
    
    //On parcours toutes les colonnes de ligne taille-1 a taille 0
    //parcour de bas en haut
    for ( j = (plateau->taille-1); j >= 0; j--){ //Ligne fixé
        for ( i = 0; i < (plateau->taille); i++){ //Colonne fixé
            
            case_courrante = obtenir_case(plateau,i,j);
            
            if((case_courrante->pos.ligne == (plateau->taille-1)) && (case_courrante->valeur == ROUGE) && (case_courrante->murFin == true)){
                
                case_courrante->murFin = true;
                
            }else{
                if ( case_courrante->valeur == ROUGE ){
                    if(case_courrante->pos.colonne == 0){
                        //Cas colonne de gauche
                        
                        if((case_courrante->lien[3]->valeur == ROUGE) && (case_courrante->lien[3]->murFin == true)){
                            
                            case_courrante->murFin = true;
                            
                        }
                    }else{
                        for ( k = 3; k < 5; k++){
                            if((case_courrante->lien[k]->valeur == ROUGE) && (case_courrante->lien[k]->murFin == true)){
                                
                                case_courrante->murFin = true;
                            
                            }
                        }
                    }
                }
            }
        }
    }
    
    //On fini en verifiant si on a un gagnant et on renvoi la couleur du gagnant ou VIDE si il n'y en a pas
    //On parcour dans un premier temps la colonne 0
    for ( i = 0; i < (plateau->taille); i++ ){
        
        case_courrante = obtenir_case(plateau,i,0);
        
        if((case_courrante->valeur == NOIR ) && (case_courrante->murDeb == true) && (case_courrante->murFin == true)) return NOIR;
        
    }
    
    //Puis la ligne 0
    for ( j = 0; j < (plateau->taille); j++){
        
        case_courrante = obtenir_case(plateau,0,j);
        
        if((case_courrante->valeur == ROUGE) && (case_courrante->murDeb == true) && (case_courrante->murFin == true)) return ROUGE;
        
    }
    
    //Cas ou la partie n'est pas fini on retourn VIDE
    return VIDE;
    
}
// int plusGrandGroupe(Plateau plateau);

void supprimerPlateau(Plateau plateau){
    
    Case case_courrante = plateau->nord;
    Case case_suivante = case_courrante->lien[2];
    int taille = plateau->taille;
    
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
            supprimerCase(case_courrante);
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
            supprimerCase(case_courrante);
            case_courrante = case_suivante;
            case_suivante = case_courrante->lien[2];
        }
    }
    //On supprime la derniere case restante
    supprimerCase(case_courrante);
    //On supprime le plateau
    free(plateau);
}
