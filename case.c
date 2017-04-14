#include "case.h"



struct s_Position {
    int ligne;
    int colonne;
};

enum e_Couleur {
    ROUGE = 1, 
    NOIR  = 2, 
    VIDE  = 0
};

struct s_Case {
    Position pos;
    Couleur valeur;
    struct Case *lien[6];
};


Case creer_case(int ligne, int colonne) {
    printf("[creer_case] Creation de la case [%d,%d].\n", ligne, colonne); // Aide pour le dev
    
    Case nouvelle_case = malloc(sizeof(struct s_Case));
    
    nouvelle_case->pos.ligne = ligne;
    nouvelle_case->pos.colonne = colonne;
    
    printf("    [creer_case] la case [%d,%d] a bien ete creee.\n", nouvelle_case->pos.ligne, nouvelle_case->pos.colonne);
    
    return nouvelle_case;
}

Case obtenir_case(Plateau plateau, int ligne, int colonne) {
    Case case_chercher = plateau->nord;

    /* on parcours le plateau jusqu'a etre a la bonne ligne */
    while((case_chercher->pos.ligne != ligne) && (ligne != plateau->taille-1)) {
        case_chercher = case_chercher->lien[3];
    }
    /* on parcours le plateau jusqu'a etre a la bonne colonne */
    while((case_chercher->pos.colonne != colonne) && (colonne != plateau->taille-1)) {
        case_chercher = case_chercher->lien[2];
    }

    return case_chercher;
}

void construction_lien_case(Plateau plateau, Case x) {
            if (x->pos.ligne == 0) {
                x->lien[0] = NULL;
                x->lien[1] = NULL;
            }
            if (x->pos.ligne == plateau->taille-1) {
                x->lien[3] = NULL;
                x->lien[4] = NULL;
            }
            if (x->pos.colonne == 0) {
                x->lien[4] = NULL;
                x->lien[5] = NULL;
            }
            if (x->pos.colonne == plateau->taille-1) {
                x->lien[1] = NULL;
                x->lien[2] = NULL;        
            }
}


Case modifierCase(Case caseModifier, Couleur valeur) {
    //On modifie la couleur de la case.
    caseModifier->valeur=valeur;
    return modifierCase;
}

Couleur couleurCase(Case x) {
    return x->valeur;
}

Position obtenirCoordonnee(Case x) {
    return x->pos;
}

void supprimerCase(Case x){
    //Il faut dans un premier temps enlever tous lesl iens avant de supprimer la case.
    free(x);
}
