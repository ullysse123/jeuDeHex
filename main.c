#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "jouer.h"
#include "affichage.h"

int menu_lancement(){
    //Menu apparaissant au lancement du jeux
    int choix = 0;
    int confirmer = 0;

    while(confirmer != 1) {

        if (confirmer != 1)
            affichage_menu_principal();

        if (choix == 0)
            while(choix<1 || choix>3) {
                printf("  Que voulez vous faire ? (1/2/3)  ");
                scanf("%d",&choix);
                printf("\n");
            }
        printf("  Confirmer (1) ? :");
        scanf("%d", &confirmer);

        if (confirmer != 1) {
            choix = 0;
            res_affichage_menu();
        } else {
            res_affichage();
        }
    }
    printf("\n");
    return choix;
}

char* afficher_partie_sauvegarde(){
  DIR * rep = NULL;
  struct dirent* nomFichier = NULL;
  rep = opendir("save/");
  if (rep == NULL) {
    return NULL;
    printf("  Erreur d'ouverture du repertoir \"save/\"\n");
  }
  int i = 0;
  while ((nomFichier=readdir(rep)) != NULL) {
    if (strcmp(nomFichier->d_name, ".") != 0 && strcmp(nomFichier->d_name, "..") != 0) {
      i++;
      printf("%3d) - %s\n", i, nomFichier->d_name);
    }
  }
  int idF = 0;
  do {
    printf("  Saisir l'indice correspondant : ");
    scanf("%d", &idF);
  } while (idF > i || idF < 1);
  i = 0;
  rep = opendir("save/");
  while (i!=idF) {
    nomFichier=readdir(rep);
    if (strcmp(nomFichier->d_name, ".") != 0 && strcmp(nomFichier->d_name, "..") != 0) {
      i++;
    }
  }
  printf("%3d)%d -%s\n", i, idF, nomFichier->d_name);
  closedir(rep);
  return nomFichier->d_name;
}

int menu_jeu(){
    //Menu apparaissant durant une partie a chaque tours
    int choix;
    int confirmer;
    printf("\n");
    printf("  Coup joue,\n  Que souhaitez vous faire ?\n");
    printf("    PASSER AU TOUR SUIVANT        (1)\n");
    printf("    ANULER LE DERNIER COUP JOUE   (2)\n");
    printf("    ABANDONNER LA PARTIE          (3)\n");
    do{
        do{
            printf("  Selectionner votre choix :\n");
            scanf("%d",&choix);
            printf("\n");
        }while(choix<1 || choix>3);
        printf("  Confirmez vous votre choix ? Si oui tapez 1 sinon le chiffre de votre choix\n");
        scanf("%d",&confirmer);
        printf("\n");
    }while(confirmer != 1);
    printf("\n");
    return choix;
}

int menu_fin(){
    //Menu apparaissant à la fin d'une partie
    int choix;
    int confirmer;
    printf("\n");
    printf("  Que souhaitez vous faire maintenant ?\n");
    printf("   (1) LANCER UNE NOUVELLE PARTIE    (1)\n");
    printf("   (2) CHARGER UNE PARTIE EXISTANTE  (2)\n");
    printf("   (3) QUITTER LE JEU             (3)\n");
    do{
        do{
            printf("Selectionnez votre choix :\n");
            scanf("%d",&choix);
            printf("\n");
        }while(choix<1 || choix>3);
        printf("  Confirmez vous votre choix ? Si oui tapez 1 sinon le chiffre de votre choix\n");
        scanf("%d",&confirmer);
        printf("\n");
    }while(confirmer != 1);
    printf("\n");
    return choix;
}

int demande_save(){
    int choix;
    printf("\n");
    printf("  Souhaitez vous effectuer une sauvegarde de votre partie ?\n  Si oui tapez 1 sinon le chiffre de votre choix\n");
    scanf("%d",&choix);
    if( choix != 1) choix=0;
    return choix;
}

int valider(Case c) {
  int valid;
  do {
    printf("  Souhaitez vous valider le coup ?\n	1-oui\n	2-non\n");
    scanf("%d\n", &valid);
  } while (valid != 0 && valid != 1);
  if (valid == 1) {
    sauvegarde_coup_tmp(c);
  } else {
    annuler(c);
  }
  return valid;
}
  
void recuperation_nom_sauvegarde (char *nomComplet) {
  // récupération nom + chemain de sauvegarde
    char nom[26] = "";
    strcat(nom,  afficher_partie_sauvegarde());
    strcat(nomComplet, "save/");
    strcat(nomComplet, nom);
}

int main(){

    clrscr();

    int i;
    affichage_entete_menu();
    
    // récupération nom sauvegarde
//     char nom[31] = "";
//     strcat(nom,  afficher_partie_sauvegarde());
//     printf("[main] %s\n",nom);
//     char nomComplet[36] = "";
//     strcat(nomComplet, "save/");
//     strcat(nomComplet, nom);
    
    
//     char nom[36] = "";
//     recuperation_nom_sauvegarde(nom);
//     printf("[main] %s\n",nom);
  
    
    
    Plateau nouveau_plateau;
    int idjoueur;

    do { // boucle de fin de programme
      i = menu_lancement();
      if (i == 1) { // nouvelle partie
	  nouveau_plateau = nouvellePartie();    
	  idjoueur = quiCommence();
      } else if (i == 2) { // chargement d'une partie existente
	  char nom[36] = "";
	  recuperation_nom_sauvegarde(nom);
	  printf("[main] %s\n",nom);
	  nouveau_plateau = charger(nom, &idjoueur);
	  idjoueur = (idjoueur % 2) + 1;
      } else if (i == 3) {
	  exit(0);
      }
      
      if ( i!= 3) {
	Case c;
	int choix;
	int fin = 0;
	while (fin == 0) {
	  affichage_plateau(nouveau_plateau);
	  c = jouer(nouveau_plateau, idjoueur);
	  choix = menu_jeu();
	  if (choix == 1) {
	    sauvegarde_coup_tmp(c);
	    idjoueur = (idjoueur % 2) + 1;
	    fin = estFini(nouveau_plateau);
	  } else if (choix == 2) {
	    annuler(c);
	  } else {
	    int save, confirmer;

        res_affichage();
	    do {
	      do {
        
		printf("  Voulez vous sauvegarder la partie en cours ? (toute partie non sauvegardee sera perdu dans les abimes)\n	1 - oui\n	2 - non\n");
		scanf("%d", &save);
	      } while(save != 1 && save != 2);
	      printf("  Confirmez vous votre choix ? Si oui tapez 1 sinon le chiffre de votre choix\n");
	      scanf("%d",&confirmer);
	      printf("\n");
	    } while(confirmer != 1);

        if( confirmer == 1)
            res_affichage_menu();

	    if (save == 1) {
	      sauvegarde_coup_tmp(c);
	      sauvegarde(nouveau_plateau);
	    } else {
	      suppr_Tmp();
	    }

	    fin = 3;

	    supprimerPlateau(nouveau_plateau);
	    suppr_Tmp();
	  }

	}

        res_affichage_menu();
            printf(" \xE2\x95\x91                                                  \xE2\x95\x91\n");
            printf(" \xE2\x95\x91  ");
            couleur("31");
            printf("          Le Joueur %d a gagner !", fin);
            couleur("0");
            printf("                \xE2\x95\x91\n");
            printf(" \xE2\x95\x91                                                  \xE2\x95\x91\n");
      }
    
    
    } while ( i != 3);

    return 0;
}
