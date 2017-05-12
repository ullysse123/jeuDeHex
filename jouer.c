#include "plateau.h"

int quiCommence();
void jouer();
void sauvegarde(Plateau plateau); // formatage plateau fini
Plateau charger (FILE *fichier);
Plateau annuler (Plateau plateau, FILE* fichier);
// bool abandonner (Plateau plateau);
Plateau nouvellePartie ();

bool abandonner(Plateau plateau) {
  char tmp, save, abandon;
  do {
    printf("confirmer abandon (O-N) ? :\n");
    scanf("%c", &tmp);
    abandon = tmp;
  } while ((abandon != 'O' && abandon != 'o') && (abandon !='N' && abandon != 'n'));
  tmp = ' ';
  if (abandon == 'O' || abandon == 'o') {
    do {
      printf("sauvegarder plateau (O-N) ? :\n");
      scanf("%c", &save);
    } while ((save != 'O' && save != 'o') && (save != 'N' && save != 'n'));
    if (save == 'O' || save == 'o') {
      sauvegarde(plateau);
    }
  }
  return (save == 'O' || save == 'o');
}

void sauvegarde(Plateau plateau) {
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
    return 0;
}