#include "plateau.h"

int quiCommence();
void jouer();
void sauvegarde(Plateau plateau);
Plateau charger (FILE *fichier);
Plateau annuler (Plateau plateau, FILE* fichier);
bool abandonner (Plateau plateau);
Plateau nouvellePartie ();


void affichage_plateau_sauvegarde(Plateau plateau) {
    Case case_courrante_colonne = plateau->nord;
    Case case_courrante_ligne = plateau->nord;
    while (case_courrante_ligne != NULL) {
        
        while (case_courrante_colonne != NULL) {
            printf("%c ", case_courrante_colonne->valeur);
            case_courrante_colonne = case_courrante_colonne->lien[2];
        }
        printf("\n");        
        case_courrante_ligne = case_courrante_ligne->lien[3];
        case_courrante_colonne = case_courrante_ligne;
        
    }
}

int main(void) {
    
    Plateau plateau = creer_plateau(4);
    
    affichage_plateau(plateau);
    
    affichage_plateau_sauvegarde(plateau);
    return 0;
}