#include "plateau.h"
#include <time.h>
#include <string.h>
#include <stdio.h>

void jouer();

//Plateau charger (FILE *fichier);

// Plateau annuler (Plateau plateau, FILE* fichier);




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



int charToInt(char c) {
  switch (c){
    case 'o' :
      // case blanche
      return 1;
      break;
    case '*':
      // case noire
      return 2;
      break;
    default:
      // case vide
      return 0;
  }
}
      

      
 /*     
Plateau annuler (Plateau plateau){
  FILE *id_save_annuler = NULL;*/
//   char info[6];
//   char couleur;
//   int line;
//   int col;
//   char * test;
//   id_save_annuler = fopen("save/saveCoupTmp.txt", "rt");
//   if (id_save_annuler == NULL) {
//     printf("[annuler] Erreur lors de l'ouverture du fichier \"save/saveCoupTmp.txt\", fichier innexistant ou protégé\nretour impossible\n");
//     perror("saveCoup");
//     return NULL;
//   } else {
//     printf("[annuler] fichier ouvert\n");
//   }
// //   fseek(id_save_annuler, -33, SEEK_END);
// //   printf("[annuler] positionnement du curseur\n");  
// //   fgets(info, 12*sizeof(char)+1, id_save_annuler);
// //   printf("[annuler] test info = %s\n", info);
// //   //fgetc(id_save_annuler);
//   
//   fseek(id_save_annuler, 0, SEEK_END);
//   printf("[annuler] position tête de lecture = %ld\n", ftell(id_save_annuler));
//   fseek(id_save_annuler, 1100, SEEK_CUR);
//   printf("[annuler] position tête de lecture = %ld\n", ftell(id_save_annuler));
//   rewind(id_save_annuler);
// //   test = fgets(info, 12*sizeof(char), id_save_annuler);
//   fscanf(id_save_annuler, "%s %c %d %d", info, &couleur, &line, &col);
//   printf("[annuler] test = %s\n", test);
//     printf("[annuler] test info = %s\n[annuler] test couleur = %c\n[annuler] test ligne = %d\n[annuler] test col = %d\n", info, couleur, line , col);
//   test = fgets(info, 30, id_save_annuler);
//   printf("[annuler] test = %s\n", test);
//   fseek(id_save_annuler, 0, SEEK_END);
//   printf("[annuler] position tête de lecture = %ld\n", ftell(id_save_annuler));
//   do {
//     printf("[annuler] test info = %s\n", info);
//   } while (fgets(info, 12, id_save_annuler) != NULL);
//   return NULL;
// }

//Plateau annuler (Plateau plateau) {
//   FILE * id_fichier;
//   char couleur;
//   int ligne, c;
//   id_fichier = fopen("save/saveCoupTmp.txt", "rt");
//   if (id_fichier == NULL) {
//     printf("Erreur Fichier innexistant ou protégé\n");
//     return plateau;
//   }
//   fseek(id_fichier, 0, SEEK_SET);
//   while ((c = fgetc(id_fichier)) != EOF) {
//     printf("%c\n", c);
//     if (c >= (int)'a' && c <= (int)'z') {
//       printf("[annuler] caracter alphabetique\n");
//     }
//     else if (c == (int)'.' || c == (int)'o' || c == (int)'*') {
//       couleur = (char)c;
//       printf("[annuler] couleur = %c\n", couleur);
//     } 
//   }
// //   fseek(id_fichier, 8, SEEK_SET);
// //   fscanf(id_fichier, "%d", &ligne);
// //   printf("[abandon] ligne = %d\n", ligne);
//   
// //   char mot[5];
// //   char couleur;
// //   char espace = '1';
// //   int ligne = 0;
// //   int colonne = 0;
//   
// //   fscanf(id_fichier, "%c%c%c%c%c%c%c%c%d%c%d%c", &mot[0],&mot[1],&mot[2],&mot[3],&mot[4],&espace, &couleur,&espace, &ligne,&espace, &colonne, &espace);
// //   printf("[annuler] test info = %s\n[annuler] test couleur = %c\n[annuler] test espace = %c\n[annuler] test ligne = %d\n[annuler] test col = %d\n", mot, couleur, espace, ligne , colonne);
//  return NULL;
//}

void annuler(Case c) {
  c = modifierCase(c, '.');
}

int annuler_dernier_coup(Plateau plateau) {
  FILE * id_save_coup = NULL;
  char trash[3]  = {};
  char color[0] = {};
  int l = 0;
  int c = 0;
  int l2 = 0;
  int c2 = 0;
  int ret = 0;
  id_save_coup = fopen("save/saveCoupTmp.txt", "rt");
  if (id_save_coup == NULL) {
    printf("[annuler_dernier_coup] erreur lors de l'ouverrture de \"save/saveCoupTmp.txt\"\n");
    return 1;
  } else {
    printf("[annuler_dernier_coup] ouverrture de \"save/saveCoupTmp.txt\"\n");
  }
  fseek(id_save_coup,0, SEEK_SET);
  ret = fscanf(id_save_coup, "%s %s %d %d", &trash[3], &color[0], &l, &c);
  while ((ret != EOF) && (ret != 0)) {
    printf("[annuler_dernier_coup] trash = %s\n", &trash[3]);
    printf("[annuler_dernier_coup] color = %s\n", &color[0]);
    printf("[annuler_dernier_coup] ligne = %d, colonne = %d\n", l, c);
    ret = fscanf(id_save_coup, "%s %s %d %d", &trash[3], &color[0], &l, &c);
  }
  printf("[annuler_dernier_coup] fin de boucle : ligne = %d, colonne = %d\n", l, c);
  
  // modification du fichier de sauvegarde et création du nouveau
  FILE * id_new_save;
  id_new_save = fopen("save/saveCoupTmp2.txt", "wt");
  if (id_new_save == NULL) {
    printf("[annuler_dernier_coup] erreur lors de l'ouverrture de \"save/saveCoupTmp2.txt\"\n");
    return 1;
  } else {
    printf("[annuler_dernier_coup] ouverrture de \"save/saveCoupTmp2.txt\"\n");
  }
  fseek(id_save_coup,0, SEEK_SET);
  ret = fscanf(id_save_coup, "%s %s %d %d", &trash[3], &color[0], &l2, &c2);
  while ((ret != EOF) && (ret != 0)) {
    if (l2 != l && c2 != c) {
      fprintf(id_new_save, "%s %s %d %d\n", &trash[3], &color[0], l2, c2);
    }
    printf("[annuler_dernier_coup] trash = %s\n", &trash[3]);
    printf("[annuler_dernier_coup] color = %s\n", &color[0]);
    printf("[annuler_dernier_coup] ligne = %d, colonne = %d\n", l2, c2);
    ret = fscanf(id_save_coup, "%s %s %d %d", &trash[3], &color[0], &l2, &c2);
  }
  printf("[annuler_dernier_coup] fin de boucle : ligne = %d, colonne = %d\n", l, c);
  
  Case caseAModif = obtenir_case(plateau, l, c);
  modifierCase ( caseAModif, 0);
  
  return 0;
}
      
Plateau charger(char nom[36]){
  printf("  <>  [charger] init\n");
  int size;
  Plateau plateau = NULL;
  FILE *id_fich;
  id_fich = fopen(nom, "rt");
  if (id_fich == NULL) {
    printf("Erreur Fichier innexistant ou protégé\n");
    return plateau;
  }
  fseek(id_fich, 9, SEEK_SET);
  fscanf(id_fich, "%d", &size);
  printf("  <>  [charger] size = %d\n", size);
  plateau = creer_plateau(size);
  
  char ligne[size*2];
  fseek(id_fich, 8, SEEK_CUR);
  
  Case case_courrante = NULL;
  // parcour du plateau de jeu
  int tour = 0;
  for(int i = 0; i < (plateau->taille); i++ ){ //Colonne fixé
    int x = 0;
    if (tour > 0) {
      fseek(id_fich, 1, SEEK_CUR);
    }
    fgets(ligne, (size*2)+1, id_fich);
    printf("  <>  [charger] ligne extraite au tour %d = %s\n",tour, ligne);
    for (int j = 0; j < (plateau->taille); j++){ //Ligne fixé
      printf("  <>  [charger] i = %d / j = %d\n", i, j);
      case_courrante = obtenir_case(plateau,i,j);
      printf("  <>  [charger] ligne = %d / colonne = %d\n", case_courrante->pos.ligne, case_courrante->pos.colonne);
      modifierCase(case_courrante, charToInt(ligne[x]));
      case_courrante = case_courrante->lien[2];
      affichage_plateau(plateau);
      printf("  <>  [charger] x = %d\n", x);
      x = x +2;
    }
    tour ++;
    printf("  <>  [charger] tour = %d\n", tour);
  }
	    
	    
//   while (case_courrante_ligne != NULL) {
//     int j = 0;
//     if (tour > 0) {
//       fseek(id_fich, 1, SEEK_CUR);
//     }
//     fgets(ligne, (size*2)+1, id_fich);
//     printf("  <>  [charger] ligne extraite au tour %d = %s\n",tour, ligne);
//     while (case_courrante_colonne != NULL) {
//       printf("  <>  [charger] ligne = %d / colonne = %d\n", case_courrante_ligne->pos.ligne, case_courrante_colonne->pos.colonne);
//       modifierCase(case_courrante_colonne, charToInt(ligne[j]));
//       case_courrante_colonne = case_courrante_colonne->lien[2];
//       affichage_plateau(plateau);
//     
//       printf("  <>  [charger] j = %d\n", j);
//       j = j+2;
//     }
//     // fin de ligne
//     
//     case_courrante_ligne = case_courrante_ligne->lien[3];
//     case_courrante_colonne = case_courrante_ligne;
//     tour ++;
//     printf("  <>  [charger] tour = %d\n", tour);
//   }
    
  
  printf("  <>  [charger] cration du fichier d'historique des coups\n");
  // cration du fichier d'historique des coups
  //////////////////////////////////////////////////////////////////////////////////////// <=========== erreur ici !!!!
  fseek(id_fich, 10, SEEK_CUR);
  fgets(ligne, 15, id_fich);
  FILE * id_save_coup = NULL;
  id_save_coup = fopen("save/saveCoupTmp.txt", "wt");
  printf("  <>  [charger] fichier d'historique des coups ouvert/créer\n");
  while (strcmp(ligne, "\\endhex\n") != 0) {
    printf("  <>  [charger] /= //endhex\n");
    for (int i = 0; i <= nombreCaseCouleur(plateau); i++) {
      printf("  <>  [charger]  i = %d\n", i);
      printf("  <>  [charger]  ligne = %s\n", ligne);
      if (strcmp(ligne, "\\endboard\n") != 0 && strcmp(ligne, "\\endhex\n") != 0) {
	fprintf(id_save_coup, ligne);
      }
      fgets(ligne, 15, id_fich);
    }
  }
 
  return plateau;
}

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
  int size, joueur, choix;
  Plateau plateau = NULL;
  
  // le joueur choisi ça couleur
  choix_couleur(1);
  // le joueur choisi qui commence
  joueur = quiCommence();
  
  // choix de la taille du plateau
  size = 11;
  do {
    printf("la taille par défaut est de 11 par 11\n voulez vous la modifier ?\n	1- oui\n	2-non\n	");
    scanf("%d", &choix);
  } while (choix != 1 && choix != 2);
  
  if (choix == 1) {
    printf("Nouvelle partie :\nentrer la taille du plateau :\n");
    scanf("%d", &size);
  }
  // création du plateau
  plateau = creer_plateau(size);
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
  fprintf(id_save_coup, "\\play %c %d %d\n", couleurToChar(c), c->pos.ligne, c->pos.colonne);
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
  fprintf(id_save_plateau, "\\board\n");
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
  fprintf(id_save_plateau, "\\endboard\n");
  // on ferme le fichier
  fclose(id_save_plateau);
  return 0;
}


int lire(char *chaine, int longueur) {
  printf("[save]	Nom de la sauvegarde (25 char max) : \n");
  // netoyage de la chaine (si il y à des reste d'une fonction précedante
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
    printf("[sauvegarde] erreur fichier save coup\n");
    return 1;
  }
  printf("[sauvegarde] fichier save coup fait\n");
  id_save_plateau = fopen("save/savePlateauTmp.txt", "rt");
  if (id_save_plateau == NULL) {
    printf("[sauvegarde] erreur fichier save plateau\n");
    // erreur lors de l'ouverture du fichier de sauvegarde du plateau donc on fermes le fichier ouvert avant
    fclose(id_save_coup);
    return 1;
  }
  
  
  // choix du nom de la sauvegarde (26 caractere max)
  char nomSauvegarde[25];
  char save[36] = "save/";
  printf("[sauvegarde] init\n");
  // on teste que la saisi s'effectue
  if (lire(nomSauvegarde, 25)) {
  printf("[sauvegarde] erreur lire\n");
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
    printf("[sauvegarde] erreur fichier save\n");
    // si il y a une erreur on ferme les fichiers ouvert avant de sortir
    fclose(id_save_coup);
    fclose(id_save_plateau);
    return 1;
  }
  
  // enregistrement  de l'entête du fichier
  fprintf(id_save, "\\hex\n\\dim %d\n", plateau->taille);
  
  // copie du contenu du fichier de la sauvegarde du plateau vers le fichier de sauvegarde final
  int size = plateau->taille;
  
  char line[size];
  // on lis chaque ligne du fichier source pour l'écrire dans le nouveau fichier
  // La taille de lecture est size * 2 car une ligne du plateau à un caractere et un espace
  while (fgets(line, size*2, id_save_plateau) != NULL) {
    fprintf( id_save, "%s", line);
  }
  // idem pour le fichier de sauvegarde de l'historique
  // taille est ici de 15 car le texte est formater de cette sorte : "/play . 000 000\0" 1000 case de coté maximum
  while (fgets(line, 15, id_save_coup) != NULL) {
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
  fprintf(id_save, "\\endhex");
  // on ferme le fichier de sauvegarde final
  fclose(id_save);
  
  return 0;
}

int suppr_Tmp(){
  int ret, rem;
  rem = 0;
  // variable pour récuperer le code retour
  ret = remove("save/saveCoupTmp.txt");
  if (ret == 0) {
    // pas d'erreur
    printf("[sauvegarde] (remove) fichier save/saveCoupTmp.txt supprimer\n");
  } else {
    // erreur lors de la supression
    printf("[sauvegarde] (remove) fichier save/saveCoupTmp.txt erreur de suppression\n");
    rem = 1;
    
  }
  
  // idem
  
  ret = remove("save/savePlateauTmp.txt");
  if (ret == 0) {
    printf("[sauvegarde] (remove) fichier save/savePlateauTmp.txt supprimer\n");
  } else {
    printf("[sauvegarde] (remove) fichier save/savePlateauTmp.txt erreur de suppression\n");
    rem = 1;
    
  }
  // on ferme le fichier de sauvegarde final
  
  return rem;
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
    suppr_Tmp();
    // on supprime le plateau de jeu 
    supprimerPlateau(plateau);
  }
  // on retourne le booleen de l'abandon
  return (abandon == 1);
}

