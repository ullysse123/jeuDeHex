#include "plateau.h"
#include <time.h>
#include <string.h>
#include <stdio.h>

// int quiCommence();
void jouer();
// void sauvegarde(Plateau plateau); // formatage plateau fini
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
    idJoueur = (rand() % 2) + 1;
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
  int save, abandon, erreur;
  //erreur = 0;
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
      erreur = sauvegarde(*plateau);
    }
//     supprimerPlateau(plateau);
  }
  return (save == 1);
}

int sauvegarde_coup_tmp(Case c) {
  FILE * id_save_coup = NULL;
  id_save_coup = fopen("save/saveCoupTmp.txt", "at");
  if (id_save_coup == NULL) return 1;
  fprintf(id_save_coup, "/play %c %d %d\n", couleurToChar(c), c->pos.ligne, c->pos.colonne);
  fclose(id_save_coup);
  return 0;
}

int sauvegard_plateau_tmp(Plateau plateau) {
  FILE * id_save_plateau = NULL;
  id_save_plateau = fopen("save/savePlateauTmp.txt", "wt");
  if (id_save_plateau == NULL) return 1;
  Case case_courrante_colonne = plateau->nord;
  Case case_courrante_ligne = plateau->nord;
  fprintf(id_save_plateau, "/board\n");
  while (case_courrante_ligne != NULL) {
    
    while (case_courrante_colonne != NULL) {
      if ((int)case_courrante_colonne->valeur == 0) {
      
	fprintf(id_save_plateau, ". ");
      } else if ((int)case_courrante_colonne->valeur == 1) {
	
	fprintf(id_save_plateau, "o ");
      } else {
	fprintf(id_save_plateau, "* ");
      }
      case_courrante_colonne = case_courrante_colonne->lien[2];
    }
    fprintf(id_save_plateau, "\n");        
    case_courrante_ligne = case_courrante_ligne->lien[3];
    case_courrante_colonne = case_courrante_ligne;
    
  }
  fprintf(id_save_plateau, "/endboard\n");
  fclose(id_save_plateau);
  return 0;
}

int lire(char *chaine, int longueur)
{
    char *positionEntree = NULL;
 
    if (fgets(chaine, longueur, stdin) != NULL)  // Pas d'erreur de saisie ?
    {
        positionEntree = strchr(chaine, '\n'); // On recherche l'"Entrée"
        if (positionEntree != NULL) // Si on a trouvé le retour à la ligne
        {
            *positionEntree = '.'; // On remplace ce caractère par \0
            strcat(chaine, "txt\0");
        }
        return 0;
    }
    else
    {
        return 1;
    }
}

int sauvegarde(Plateau plateau) {
  // Ouverture des fichier temporaire
  FILE *id_save_coup = NULL;
  FILE *id_save_plateau = NULL;
  id_save_coup = fopen("save/saveCoupTmp.txt", "wt");
  if (id_save_coup == NULL) return 1;
  id_save_plateau = fopen("save/savePlateauTmp.txt", "wt");
  if (id_save_plateau == NULL) return 1;
  // création du fichier de la sauvegarde
  FILE *id_save = NULL;
  
  char *nomSauvegarde, *chemain;
  strcpy(chemain, "save/");
  if (lire(nomSauvegarde, 25)) {
    return 1; // erreur lors de la saisie
  }
  strcat(chemain, nomSauvegarde);
  
    
  return 0;
}

int main(void) {
  int erreur =0;
  Plateau plateau = creer_plateau(4);
    
    affichage_plateau(plateau);
    printf("\n");
    modifierCase(plateau->nord, 1);
    sauvegarde_coup_tmp(plateau->nord);
    affichage_plateau(plateau);
    printf("\n");
    printf("%d\n", nombreCaseCouleur(plateau));
    sauvegard_plateau_tmp(plateau);
    abandonner(plateau);
    
    nouvellePartie();
    return 0;
}