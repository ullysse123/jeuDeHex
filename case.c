#include "case.h"
#include "plateau.h"
#include <stdbool.h>


Case creer_case(int ligne, int colonne) {
    printf("[creer_case] Creation de la case [%d,%d].\n", ligne, colonne); // Aide pour le dev
    
    Case nouvelle_case = malloc(sizeof(struct s_Case));
    
    nouvelle_case->pos.ligne = ligne;
    nouvelle_case->pos.colonne = colonne;
    nouvelle_case->murDeb=false;
    nouvelle_case->murFin=false;
    
    printf("    [creer_case] la case [%d,%d] a bien ete creee.\n", nouvelle_case->pos.ligne, nouvelle_case->pos.colonne);
    
    return nouvelle_case;
}

Case modifierCase(Case caseModifier, Couleur valeur) {
    //On modifie la couleur de la case.
    caseModifier->valeur=valeur;
    return caseModifier;
}

Couleur couleurCase(Case x) {
    return x->valeur;
}

Position obtenirCoordonnee(Case x) {
    return x->pos;
}

void supprimerCase(Case x){
    //Pour supprimer une case, je redirige tous les liens vers la case elle meme, puis je la supprime.
    for (int i=0;i<6;i++){
        x->lien[i]=x;
    }
    free(x);
}
