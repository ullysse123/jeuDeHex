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
  // initialisation de srand su le temps actuel pour générer des nombre aléatoire
  srand(time(NULL));
  // menu du choix de qui commence (protéger des saisie numéraire autre que celles attenduent
  do {
    printf("Choix du joueur commençant la partie :\n	1-joueur 1\n	2-joueur 2\n	3-laisser le hasard choisir\n	");
    scanf("%d", &idJoueur);
  } while (idJoueur != 1 && idJoueur != 2 && idJoueur != 3);
  // génération d'un nombre aléatoire étant soit 1 soit 2
  if (idJoueur == 3) {
    idJoueur = (rand() % 2) + 1;
  }
  // renvoi du numéro du joueur
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
  // boucle protéger pour choisir la couleur , soit blanc soit noir
  do {
    printf("	Choix de la couleur :\n		joueur %d :\n		1-Pour blanc\n		2-Pour noir\n		", joueur);
    scanf("%d", &choix);
  } while (choix != 1 && choix != 2);
  
  return choix;
}

Plateau nouvellePartie () {
  
  // variable utile pour une nouvelle partie
  int size, joueur;
  Plateau plateau = NULL;
  // choix de la taille du plateau
  printf("Nouvelle partie :\nentrer la taille du plateau :\n");
  scanf("%d", &size);
  // création du plateau
  plateau = creer_plateau(size);
  // le joueur choisi ça couleur
  choix_couleur(1);
  // le joueur choisi qui commence
  joueur = quiCommence();
  printf("[nouvelle partie] id joueur = %d\n", joueur);
  
//   // ancienne version maintenant c'est dans la fonction sauvegarde 
//   FILE *id_save;
//   id_save = fopen("save/saveTmp.txt", "wt");
//   if (id_save == NULL) perror("save/saveTmp.txt");
//   fprintf(id_save, "/hex\n/dim %d\n", size);
//   fclose(id_save);
//   
  return plateau;
}

int sauvegarde_coup_tmp(Case c) {
  // ouverrture du fichier temporaire de sauvegarde d'un coup jouer
  FILE * id_save_coup = NULL;
  id_save_coup = fopen("save/saveCoupTmp.txt", "at");
  // vérification de l'ouverture, si impossible renvoi 1
  if (id_save_coup == NULL) return 1;
  // on enregistre le nouveau coup jouer à la suite du fichier
  fprintf(id_save_coup, "/play %c %d %d\n", couleurToChar(c), c->pos.ligne, c->pos.colonne);
  // fermeture du fichier
  fclose(id_save_coup);
  return 0;
}

int sauvegarde_plateau_tmp(Plateau plateau) {
  // ouverture du fichier temporaire de sauvegarde du plateau
  FILE * id_save_plateau = NULL;
  id_save_plateau = fopen("save/savePlateauTmp.txt", "wt");
  // vérification de l'ouverture, si impossible renvoi 1  
  if (id_save_plateau == NULL) return 1;
  
  // parcour du plateau afin de sauvegarder chaque case
  Case case_courrante_colonne = plateau->nord;
  Case case_courrante_ligne = plateau->nord;
  fprintf(id_save_plateau, "/board\n");
  while (case_courrante_ligne != NULL) {
    
    while (case_courrante_colonne != NULL) {
      // on écris dans le fichier les valeurs avec leurs couleur
      if ((int)case_courrante_colonne->valeur == 0) {
	// case vide
	fprintf(id_save_plateau, ". ");
      } else if ((int)case_courrante_colonne->valeur == 1) {
	// case blanc
	fprintf(id_save_plateau, "o ");
      } else {
	// case noir
	fprintf(id_save_plateau, "* ");
      }
      case_courrante_colonne = case_courrante_colonne->lien[2];
    }
    // fin de ligne donc on revient à la ligne
    fprintf(id_save_plateau, "\n");        
    case_courrante_ligne = case_courrante_ligne->lien[3];
    case_courrante_colonne = case_courrante_ligne;
    
  }
  // fin de tableau on écris la balise de fin
  fprintf(id_save_plateau, "/endboard\n");
  // on ferme le fichier
  fclose(id_save_plateau);
  return 0;
}

/** Fonction de purge pour les saisie clavier **/
static void purger(void)

{
  int c;
  // on se place au caractere entrée ou à la fin du fichier
  while ((c = getchar()) != '\n' && c != EOF)
  {}
}

/** Fonction de netoyage de buffer pour la saisie clavier **/
static void clean (char *chaine)
{
  // on cherche le caractere entrée dans la chaine
  char *p = strchr(chaine, '\n');
  if (p)
  {
    // on le supprime de la chaine
    *p = 0;
  }
  else
  {
    // sinon on purge
    purger();
  }
}



int lire(char *chaine, int longueur) {
  printf("[save]	Nom de la sauvegarde : \n");
  // netoyage de la chaine (si il y à des reste d'une fonction précedante
  clean(chaine);
  // saisi de la nouvelle chaine de caractere
  fgets(chaine, longueur * sizeof(char), stdin);
  printf("[abandon|lire] fgets effectuer\n");
  // netoyage de la chaine
  clean(chaine);
  printf("[aandon|lire] chaine = %s\n", chaine);
  return 0;
}

int sauvegarde(Plateau plateau) {
  // Ouverture des fichier temporaire
  // si le plateau n'est pas créer on arrete la fonction
  if (sauvegarde_plateau_tmp(plateau) != 0) {
    return 2;
  }
  
  // ouverture des fichiers de sauvegarde temporaire
  FILE *id_save_coup = NULL;
  FILE *id_save_plateau = NULL;
  id_save_coup = fopen("save/saveCoupTmp.txt", "rt");
  if (id_save_coup == NULL) {
    // erreur lors de l'ouverture du fichier de sauvegarde d'un coup
    printf("[abandon] erreur fichier save coup\n");
    return 1;
  }
  printf("[abandon] fichier save coup fait\n");
  id_save_plateau = fopen("save/savePlateauTmp.txt", "rt");
  if (id_save_plateau == NULL) {
    printf("[abandon] erreur fichier save plateau\n");
    // erreur lors de l'ouverture du fichier de sauvegarde du plateau donc on fermes le fichier ouvert avant
    fclose(id_save_coup);
    return 1;
  }
  
  
  // choix du nom de la sauvegarde (26 caractere max)
  char nomSauvegarde[26];
  char save[36] = "save/";
  printf("[abandon] init\n");
  // on teste que la saisi s'effectue
  if (lire(nomSauvegarde, 26)) {
  printf("[abandon] erreur lire\n");
    return 1; // erreur lors de la saisie
  }
  // on formate le nom de la sauvegarde de la forme "save/nom_sauvergarde.txt\0"
  strcat(save, nomSauvegarde);
  strcat(save, ".txt\0");
  printf("%s\n", save);
  
  
  // création du fichier de la sauvegarde
  FILE *id_save = NULL;
  id_save = fopen(save, "wt");
  // test de la création du fichier de sauvegarde
  if (id_save == NULL) {
    printf("[abandon] erreur fichier save\n");
    // si il y a une erreur on ferme les fichiers ouvert avant de sortir
    fclose(id_save_coup);
    fclose(id_save_plateau);
    return 1;
  }
  
  // enregistrement  de l'entête du fichier
  fprintf(id_save, "/hex\n/dim %d\n", plateau->taille);
  
  // copie du contenu du fichier de la sauvegarde du plateau vers le fichier de sauvegarde final
  int size = plateau->taille;
  
  char line[size];
  // on lis chaque ligne du fichier source pour l'écrire dans le nouveau fichier
  // La taille de lecture est size * 2 car une ligne du plateau à un caractere et un espace
  while (fgets(line, size*2, id_save_plateau) != NULL) {
    fprintf( id_save, "%s", line);
  }
  // idem pour le fichier de sauvegarde de l'historique
  // taille est ici de 11 car le texte est formater de cette sorte : "/play . 0 0\0"
  while (fgets(line, 11, id_save_coup) != NULL) {
    fprintf( id_save, "%s", line);
  }
  
  // on va maintenant suprimer les fichiers temporaire
  
  // on ferme le fichier avant de le suprimer
  fclose(id_save_coup);
  int ret;
  // variable pour récuperer le code retour
  ret = remove("save/saveCoupTmp.txt");
  if (ret == 0) {
    // pas d'erreur
    printf("[sauvegarde] (remove) fichier save/saveCoupTmp.txt supprimer\n");
  } else {
    // erreur lors de la supression
    printf("[sauvegarde] (remove) fichier save/saveCoupTmp.txt erreur de suppression\n");
  }
  
  // idem
  fclose(id_save_plateau);
  
  ret = remove("save/savePlateauTmp.txt");
  if (ret == 0) {
    printf("[sauvegarde] (remove) fichier save/savePlateauTmp.txt supprimer\n");
  } else {
    printf("[sauvegarde] (remove) fichier save/savePlateauTmp.txt erreur de suppression\n");
  }
  
  // on ferme le fichier de sauvegarde final
  fclose(id_save);
  
  return 0;
}

bool abandonner(Plateau plateau) {
  int save, abandon, erreur;
  // boucle pour le menu de validation d'abandon
  do {
    printf("confirmer abandon (0 = non - 1 = oui) ? :");
      scanf("%d", &abandon);
  } while (abandon != 0 && abandon !=1);
  if (abandon == 1) {
    // si l'abandon est verfier on propose la sauvegarde
    do {
      printf("sauvegarder plateau (0 = non - 1 = oui) ? :");
      scanf("%d", &save);
    } while (save != 0 && save != 1);
    if (save == 1) {
      erreur = sauvegarde(plateau);
      if (erreur != 0) { 
	printf("[abandon] erreur = %d / erreur lors de la sauvegarde du jeu\n", erreur);
      }
    }
    // on supprime le plateau de jeu 
    supprimerPlateau(plateau);
  }
  // on retourne le booleen de l'abandon
  return (abandon == 1);
}


int main(void) {
    Plateau plateau = creer_plateau(4);
    printf("<>	[-jeux-] plateau créé\n");
    
//     affichage_plateau(plateau);
//     printf("\n");
    modifierCase(plateau->nord, 1);
//     printf("<>	[-jeux-] case nord modifié\n");
    sauvegarde_coup_tmp(plateau->nord);
//     printf("<>	[-jeux-] coup sauvegardé\n");
//     affichage_plateau(plateau);
//     printf("\n");
//     printf("%d\n", nombreCaseCouleur(plateau));
    abandonner(plateau);
//     printf("<>	[-jeux-] partie abandonné\n");
    
//     nouvellePartie();
    return 0;
}