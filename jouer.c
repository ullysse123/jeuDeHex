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

int sauvegarde_coup_tmp(Case c) {
  FILE * id_save_coup = NULL;
  id_save_coup = fopen("save/saveCoupTmp.txt", "at");
  if (id_save_coup == NULL) return 1;
  fprintf(id_save_coup, "/play %c %d %d\n", couleurToChar(c), c->pos.ligne, c->pos.colonne);
  fclose(id_save_coup);
  return 0;
}

int sauvegarde_plateau_tmp(Plateau plateau) {
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

static void purger(void)

{

    int c;


    while ((c = getchar()) != '\n' && c != EOF)

    {}

}


static void clean (char *chaine)

{

    char *p = strchr(chaine, '\n');


    if (p)

    {

        *p = 0;

    }


    else

    {

        purger();

    }

}

int lire(char *chaine, int longueur)
{
    printf("[save]	Nom de la sauvegarde : \n");
    clean(chaine);
    fgets(chaine, longueur * sizeof(char), stdin);
    printf("[abandon|lire] fgets effectuer\n");
    clean(chaine);
    printf("%s\n", chaine);
    
//     if (fgets(chaine, longueur * sizeof(char), stdin) != NULL)  // Pas d'erreur de saisie ?
//     {
//       
//         printf("[abandon|lire] fgets effectuer\n");
//         positionEntree = strchr(chaine, '\n'); // On recherche l'"Entrée"
//         if (positionEntree != NULL) // Si on a trouvé le retour à la ligne
//         {
// 	    printf("[abandon|lire] retour à la ligne trouvé\n");
//             *positionEntree = '.'; // On remplace ce caractère par \0
//             strcat(chaine, "txt\0");
//         }
//         printf("[abandon|lire] retour 0\n");
//         return 0;
//     }
//     else
//     {
//         printf("[abandon|lire] retour 1\n");
//         return 1;
//     }
	return 0;
}

int sauvegarde(Plateau plateau) {
  // Ouverture des fichier temporaire
  if (sauvegarde_plateau_tmp(plateau) != 0) {
    return 2;
  }
  FILE *id_save_coup = NULL;
  FILE *id_save_plateau = NULL;
  id_save_coup = fopen("save/saveCoupTmp.txt", "rt");
  if (id_save_coup == NULL) {
    printf("[abandon] erreur fichier save coup\n");
    return 1;
  }
  printf("[abandon] fichier save coup fait\n");
  id_save_plateau = fopen("save/savePlateauTmp.txt", "rt");
  if (id_save_plateau == NULL) {
    printf("[abandon] erreur fichier save plateau\n");
    fclose(id_save_coup);
    return 1;
  }
  
  char nomSauvegarde[26];
  char save[35] = "save/";
  printf("[abandon] init\n"); 
  if (lire(nomSauvegarde, 26)) {
  printf("[abandon] erreur lire\n");
    return 1; // erreur lors de la saisie
  }
  strcat(save, nomSauvegarde);
  strcat(save, ".txt\0");
  printf("%s\n", save);
  
  
  // création du fichier de la sauvegarde
  FILE *id_save = NULL;
  id_save = fopen(save, "wt");
  if (id_save == NULL) {
    printf("[abandon] erreur fichier save\n");
    fclose(id_save_coup);
    fclose(id_save_plateau);
    return 1;
  }
  
  // copie de save plateau > save
  int size = plateau->taille;
  
  char line[size];
  while (fgets(line, size*2, id_save_plateau) != NULL) {
    fprintf( id_save, "%s", line);
  }
  
  while (fgets(line, size*2, id_save_coup) != NULL) {
    fprintf( id_save, "%s", line);
  }
  
  // TODO supprimer temps + fermeture fichier. !!!!!!!
  
  fclose(id_save_coup);
  
  int ret;
  ret = remove("save/saveCoupTmp.txt");
  if (ret == 0) {
    printf("[sauvegarde] (remove) fichier save/saveCoupTmp.txt supprimer\n");
  } else {
    printf("[sauvegarde] (remove) fichier save/saveCoupTmp.txt erreur de suppression\n");
  }
    
  
  return 0;
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
      erreur = sauvegarde(plateau);
      printf("[abandon] erreur = %d\n", erreur);
    }
//     supprimerPlateau(plateau);
  }
  return (save == 1);
}


int main(void) {
//     Plateau plateau = creer_plateau(4);
//     printf("<>	[-jeux-] plateau créé\n");
//     
// //     affichage_plateau(plateau);
// //     printf("\n");
//     modifierCase(plateau->nord, 1);
// //     printf("<>	[-jeux-] case nord modifié\n");
//     sauvegarde_coup_tmp(plateau->nord);
// //     printf("<>	[-jeux-] coup sauvegardé\n");
// //     affichage_plateau(plateau);
// //     printf("\n");
// //     printf("%d\n", nombreCaseCouleur(plateau));
//     abandonner(plateau);
// //     printf("<>	[-jeux-] partie abandonné\n");
//     
// //     nouvellePartie();
    return 0;
}