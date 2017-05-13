#include "plateau.h"
#include <time.h>
#include <string.h>
#include <stdio.h>

int quiCommence();
void jouer();
void sauvegarde(Plateau plateau); // formatage plateau fini
Plateau charger (FILE *fichier);
Plateau annuler (Plateau plateau, FILE* fichier);
// bool abandonner (Plateau plateau); -> maj save ou s
// Plateau nouvellePartie (); -> test a finaliser

int quiCommence() {
  int idJoueur;
  srand(time(NULL));
  do {
    printf("Choix du joueur commençant la partie :\n	1-joueur 1\n	2-joueur 2\n	3-laisser le hasard choisir\n	");
    scanf("%d", &idJoueur);
  } while (idJoueur != 1 && idJoueur != 2 && idJoueur != 3);
  if (idJoueur == 3) {
    idJoueur = (rand() % 2) + 1} else {
    idJoueur;
  }
  return idJoueur;
}

// Fonction de verification du random.
// void testRand() {
//   int test;
//   srand(time(NULL));
//   for (int i = 0 ; i < 10000 ; i ++) {
//     printf("%d ", (rand()%2));
//   }
// }
  
int choix_couleur(int joueur) {
  int choix;
  do {
    printf("	Choix de la couleur :\n		joueur %d :\n		1-Pour blanc\n		2-Pour noir\n		", joueur);
    scanf("%d", &choix);
  } while (choix != 1 && choix != 2);
  return choix;
}

Plateau nouvellePartie () {
  
  int size, joueur;
  Plateau plateau = NULL;
  printf("Nouvelle partie :\nentrer la taille du plateau :\n");
  scanf("%d", &size);
  plateau = creer_plateau(size);
  choix_couleur(1);
  joueur = quiCommence();
  printf("[nouvelle partie] id joueur = %d\n", joueur);
  
  FILE *id_save;
  id_save = fopen("save/saveTmp.txt", "wt");
  if (id_save == NULL) perror("save/saveTmp.txt");
  fprintf(id_save, "/hex\n/dim %d\n", size);
  fclose(id_save);
  
  return plateau;
}

bool abandonner(Plateau plateau) {
  int save, abandon;
  do {
    printf("confirmer abandon (0 = non - 1 = oui) ? :");
      scanf("%d", &abandon);
  } while (abandon != 0 && abandon !=1);
  if (abandon == 1) {
    do {
      printf("sauvegarder plateau (0 = non - 1 = oui) ? :");
      scanf("%d", &save);
    } while (save != 0 && save != 1);
    if (save == 1) {
      sauvegarde(plateau);
    }
//     supprimerPlateau(plateau);
  }
  return (save == 1);
}

void sauvegarde(Plateau plateau) {
  FILE *id_save;
  id_save = fopen("saveTmp.txt", "
  Case case_courrante_colonne = plateau->nord;
  Case case_courrante_ligne = plateau->nord;
  printf("/board\n");
  while (case_courrante_ligne != NULL) {
    
    while (case_courrante_colonne != NULL) {
      if ((int)case_courrante_colonne->valeur == 0) {
      
	printf(". ");
      } else if ((int)case_courrante_colonne->valeur == 1) {
	
	printf("o ");
      } else {
	printf("* ");
      }
      case_courrante_colonne = case_courrante_colonne->lien[2];
    }
    printf("\n");        
    case_courrante_ligne = case_courrante_ligne->lien[3];
    case_courrante_colonne = case_courrante_ligne;
    
  }
  printf("/endboard\n");
}

int main(void) {
    Plateau plateau = creer_plateau(4);
    
    affichage_plateau(plateau);
    printf("\n");
    modifierCase(plateau->nord, 1);
    
    affichage_plateau(plateau);
    printf("\n");
    printf("%d\n", nombreCaseCouleur(plateau));
    sauvegarde(plateau);
    
    abandonner(plateau);
    
    nouvellePartie();
    return 0;
}