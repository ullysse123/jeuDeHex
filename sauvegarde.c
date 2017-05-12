#include "plateau.h"
#include "case.h"
#include "sauvegarde.h"
#include <stdbool.h>

void affichage_plateau_sauvegarde(Plateau plateau) {
    Case case_courrante_colonne = plateau->nord;
    Case case_courrante_ligne = plateau->nord;
    while (case_courrante_ligne != NULL) {
        
        while (case_courrante_colonne != NULL) {
            printf("%d ", case_courrante_colonne.valeur);
            case_courrante_colonne = case_courrante_colonne->lien[2];
        }
        printf("\n");
        int i;
        
        case_courrante_ligne = case_courrante_ligne->lien[3];
        case_courrante_colonne = case_courrante_ligne;
        
    }
}