#include "plateau.h"

int quiCommence();
void jouer();
void sauvegarde(Plateau plateau);
Plateau charger (FILE *fichier);
Plateau annuler (Plateau plateau, FILE* fichier);
bool abandonner (Plateau plateau);
Plateau nouvellePartie ();

int main(void) {
    
    Plateau *plateau = creer_plateau(4);
    
    affichage_plateau(plateau);
    
    return 0;
}