#include "plateau.h"
#include <time.h>
#include <string.h>
#include <stdio.h>

// void jouer();

//Plateau charger (FILE *fichier);

// Plateau annuler (Plateau plateau, FILE* fichier);

Case jouer(Plateau plateau, Couleur joueur) {
  
  int ligne, colonne;
  Case caseJouer;
  
  printf("  <>  <>  [jouer] debut fonction jouer\n");
  printf("Joueur ");
  if (joueur == 1) {
    printf("ROUGE :\n");
  } else {
    printf("NOIR :\n");
  }
  
  do {
    printf("==================\n");
    printf("entrez les coordonnees :\n(entre 1 et %d)\n", plateau->taille);
    do {
      printf("	ligne :");
      scanf("%d", &ligne);
      
      if (ligne < 1 || ligne > plateau->taille) {
	printf("ligne hors tableau !\n");
      }
    } while (ligne < 1 || ligne > plateau->taille) ;
    
    do {
      printf("	colonne :");
      scanf("%d", &colonne);
      
      if (colonne < 1 || colonne > plateau->taille) {
	printf("colonne hors tableau !\n");
      }
    } while (colonne < 1 || colonne > plateau->taille) ;
    caseJouer = obtenir_case(plateau, ligne-1, colonne-1);
    if (caseJouer->valeur != 0) {
      printf("Case déjà occupé !\n");
    }
    if (ligne < 1 || ligne > plateau->taille) {
      printf("ligne hors tableau !\n");
    }
  } while (caseJouer->valeur != 0 );
  
  caseJouer = modifierCase(caseJouer, joueur);
  
  return caseJouer;
  
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



int charToInt(char c) {
  switch (c){
    case 'r' :
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

void annuler(Case c) {
  c = modifierCase(c, '.');
}

// int annuler_dernier_coup(Plateau plateau) {
//   
//   // création fichier nouveau historique
//   FILE * id_save_coup2 = NULL;
//   id_save_coup2 = fopen("save/saveCoupTmp2.txt", "wt");
//   if (id_save_coup2 != NULL) {
//     printf("[annuler_dernier_coup] création de \"save/saveCoupTmp2.txt\"\n");
//   }
// 
//   // ouverture historique
//   FILE * id_save_coup = NULL;
//   id_save_coup = fopen("save/saveCoupTmp.txt", "rt");
//   if (id_save_coup == NULL) {
//     printf("[annuler_dernier_coup] erreur lors de l'ouverrture de \"save/saveCoupTmp.txt\"\n");
//     fclose(id_save_coup2);
//     return 1;
//   } else {
//     printf("[annuler_dernier_coup] ouverrture de \"save/saveCoupTmp.txt\"\n");
//   }
// 
//   
//   // init variable
//   int nbLigne = nombreCaseCouleur(plateau);
//   printf("[nbLigne] %d\n", nbLigne);
//   
//   char chaine[16] = "";
//   
// //   char trash[5] = "";
// //   char color = ' ';
// //   int l = 0;
// //   int c = 0;
// //   int ret = 0;
//     
//   
//   // boucle de lecture du fichier
//   printf("[init curseur]\n");
//   fseek(id_save_coup, 0, SEEK_SET);
//   int verif = 0;
// //   for (int i = 0; i < (nbLigne - 1); i ++) {
// //     printf("[for]\n");
// //     verif ++;
// //     ret = fscanf(id_save_coup, "%s", trash);
// //     ret = fscanf(id_save_coup, "%c", &color);
// //     ret = fscanf(id_save_coup, "%d", &l);
// //     ret = fscanf(id_save_coup, "%d", &c);
// //     fprintf(id_save_coup2,"%s %c %d %d\n", trash, color, l, c);
// //     printf("[prev for] ligne = %s %c %d %d//ret = %d\n", trash, color, l, c, ret);
// //     
// //   }
//     printf("[avant while]><><><><\n");
//   fgets(chaine, 17, id_save_coup);
//   
//     printf("[while]><><><><\n");
//   while (fgets(chaine, 17, id_save_coup) == NULL) {
//     printf("[while]><><><><\n");
//     printf("[while]>%s\n", chaine);
//   }
//   printf("[end for] verfi = %d\n", verif);
//     printf("[end for] ligne = %s\n", chaine);
//   return 0;
// }

// int annuler_dernier_coup(Plateau plateau) {
//   FILE * id_save_coup = NULL;
//   char trash[3]  = {};
//   char color[0] = {};
//   int l = 0;
//   int c = 0;
//   int l2 = 0;
//   int c2 = 0;
//   int ret = 0;
//   id_save_coup = fopen("save/saveCoupTmp.txt", "rt");
//   if (id_save_coup == NULL) {
//     printf("[annuler_dernier_coup] erreur lors de l'ouverrture de \"save/saveCoupTmp.txt\"\n");
//     return 1;
//   } else {
//     printf("[annuler_dernier_coup] ouverrture de \"save/saveCoupTmp.txt\"\n");
//   }
//   fseek(id_save_coup,0, SEEK_SET);
//   ret = fscanf(id_save_coup, "%s %s %d %d", &trash[3], &color[0], &l, &c);
//   while ((ret != EOF) && (ret != 0)) {
//     printf("[annuler_dernier_coup] trash = %s\n", &trash[3]);
//     printf("[annuler_dernier_coup] color = %s\n", &color[0]);
//     printf("[annuler_dernier_coup] ligne = %d, colonne = %d\n", l, c);
//     ret = fscanf(id_save_coup, "%s %s %d %d", &trash[3], &color[0], &l, &c);
//   }
//   printf("[annuler_dernier_coup] fin de boucle : ligne = %d, colonne = %d\n", l, c);
//   
//   // modification du fichier de sauvegarde et création du nouveau
//   FILE * id_new_save;
//   id_new_save = fopen("save/saveCoupTmp2.txt", "wt");
//   if (id_new_save == NULL) {
//     printf("[annuler_dernier_coup] erreur lors de l'ouverrture de \"save/saveCoupTmp2.txt\"\n");
//     return 1;
//   } else {
//     printf("[annuler_dernier_coup] ouverrture de \"save/saveCoupTmp2.txt\"\n");
//   }
//   fseek(id_save_coup,0, SEEK_SET);
//   do {
//     ret = fscanf(id_save_coup, "%s %s %d %d", &trash[3], &color[0], &l2, &c2);
//     if (l2 != l && c2 != c) {
//       fprintf(id_new_save, "%s %s %d %d\n", &trash[3], &color[0], l2, c2);
//     }
//     printf("[annuler_dernier_coup] trash = %s\n", &trash[3]);
//     printf("[annuler_dernier_coup] color = %s\n", &color[0]);
//     printf("[annuler_dernier_coup] ligne = %d, colonne = %d\n", l2, c2);
//   } while ((ret != EOF) && (ret != 0));
//   printf("[annuler_dernier_coup] fin de boucle : ligne = %d, colonne = %d\n", l, c);
//   
//   Case caseAModif = obtenir_case(plateau, l, c);
//   modifierCase ( caseAModif, 0);
//   
//   return 0;
// }  
   
Plateau charger(char nom[36]){
  printf("  <>  [charger] init\n");
  int size;
  Plateau plateau = NULL;
  FILE *id_fich;
  id_fich = fopen(nom, "r");
  if (id_fich == NULL) {
    printf("Erreur Fichier innexistant ou protégé\n");
    return plateau;
  }
  fseek(id_fich, 9, SEEK_SET);
  fscanf(id_fich, "%d", &size);
  printf("  <>  [charger] size = %d\n", size);
  plateau = creer_plateau(size);

  char ligne[size*2]; // cahine de reception de la lecture du fichier
  fseek(id_fich, 0, SEEK_SET); // on se repositionne au début du fichier
  
  Case case_courrante = NULL;
  // parcour du plateau de jeu
  int tour = 0;
  fgets(ligne, (size*2) +2, id_fich);
  fgets(ligne, (size*2) +2, id_fich);
  fgets(ligne, (size*2) +2, id_fich);
  int iline = 0; // lecture des lignes du fichier
  
  
  while (iline < size) {
    tour = 0;
    fgets(ligne, (size*2) +2, id_fich);
    clean(ligne);
    iline ++;
    printf("VALEUR ligne = %s / iline = %d\n", ligne, iline);
    for (tour = 0; tour < size*2; tour = tour +2){
      case_courrante = obtenir_case(plateau,iline - 1, tour/2);
      printf("[coordonnee] %d %d\n", iline-1, tour/2);
      printf("VALEUR ligne[%d] = %c\n", tour, ligne[tour]);
      modifierCase(case_courrante, charToInt(ligne[tour]));
    }
  }
  
  //creation de l'historique
  
  //creation du fichier
  FILE * id_save_coup;
  id_save_coup = fopen("save/saveCoupTmp.txt", "wt");
  
  // lecture du fichier de sauvegarde
  int i = 0;
  fgets(ligne, (size*2) +2, id_fich);
  tour = nombreCaseCouleur(plateau);
  printf("[tour] %d\n", tour);
  for (i = 0; i < tour; i++) {
    printf("entrée 2 while\n");
    fgets(ligne, (size*2) +2, id_fich);
    printf("VALEUR ligne = %s / i = %d\n", ligne, i);
    fprintf(id_save_coup,"%s", ligne);
    clean(ligne);
  }
  fclose(id_fich);
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
  int size, choix;
  Plateau plateau = NULL;
  
  
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

  return plateau;
}

int sauvegarde_coup_tmp(Case c) {
  // ouverrture du fichier temporaire de sauvegarde d'un coup jouer
  FILE * id_save_coup = NULL;
  id_save_coup = fopen("save/saveCoupTmp.txt", "at");
  // vérification de l'ouverture, si impossible renvoi 1
  if (id_save_coup == NULL) return 1;
  // on enregistre le nouveau coup jouer à la suite du fichier
  fprintf(id_save_coup, "\n\\play %c %d %d", couleurToChar(c), c->pos.ligne, c->pos.colonne);
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
	fprintf(id_save_plateau, "r ");
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
  fprintf(id_save_plateau, "\\endboard");
  // on ferme le fichier
  fclose(id_save_plateau);
  return 0;
}


int lire(char *chaine, int longueur) {
  printf("[save]	Nom de la sauvegarde (25 char max) : \n");
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
//   if (lire(nomSauvegarde, 25)) {
//   printf("[sauvegarde] erreur lire\n");
//     return 1; // erreur lors de la saisie
//   }
  printf("entrez le nom de la sauvegarde (sans espace(s)) :\n");
  scanf("%s", nomSauvegarde);
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
  } else {
    printf("[sauvegarde] fichier save creer\n");
  }
    
  
  // enregistrement  de l'entête du fichier
  fprintf(id_save, "\\hex\n\\dim %d\n", plateau->taille);
  printf("[sauvegarde] enregistrement  de l'entête du fichier\n");
  
  // copie du contenu du fichier de la sauvegarde du plateau vers le fichier de sauvegarde final
  int size = plateau->taille;
  printf("[sauvegarde] copie du contenu du fichier de la sauvegarde du plateau size = %d\n", plateau->taille);
  
  char line[size*2];
  // on lit chaque ligne du fichier source pour l'écrire dans le nouveau fichier
  // La taille de lecture est size * 2 car une ligne du plateau à un caractere et un espace
  while (fgets(line, (size*2), id_save_plateau) != NULL) {
    printf("[sauvegarde] <> while %s\n", line);
    fprintf( id_save, "%s", line);
  }

  // idem pour le fichier de sauvegarde de l'historique
  // taille est ici de 15 car le texte est formater de cette sorte : "/play . 000 000\0" 1000 case de coté maximum
  while (fgets(line, 17, id_save_coup) != NULL) {
    printf("[sauvegarde] <> while <coup> %s\n", line);
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
  fprintf(id_save, "\n\\endhex");
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

