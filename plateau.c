#include "plateau.h"
#include "case.h"


struct s_Plateau {
    int taille;
    Case nord;
    Case sud;
    Case est;
    Case ouest;
};


Plateau creer_plateau(int taille) {
     printf("[creer_plateau] Creation du plateau.\n"); // Aide pour le dev
    Plateau plateau = malloc(sizeof(struct s_Plateau));
    plateau->taille = 4;

    /* construction du sommet nord */
    plateau->nord = creer_case(0,0);

    /* on relie les sommets entre eux pour simplifier la construction du plateau */
    construction_lien_case(plateau, plateau->nord);

    /* on construit les autres case du plateau en les ajoutants directement au plateau */
    Case nouvelle_case;

    int ligne, colonne;
    for(ligne = 0; ligne < taille; ligne++) {
        for(colonne = 0; colonne < taille; colonne++) {
            /* on saute le sommet nord, il est deja creer */
            if ((ligne == 0 && colonne == 0))
                continue;
                /* on creer la case et on edite les liens */
                nouvelle_case = creer_case(ligne, colonne);
                construction_lien_case(plateau, nouvelle_case);
        }
        printf("\n");
    }

    return plateau;
}

void affichage_plateau(Plateau plateau) {
    Case case_courrante_colonne = plateau->nord;
    Case case_courrante_ligne = plateau->nord;
    int nombre_espace = 1;
    while (case_courrante_ligne != NULL) {
        
        while (case_courrante_colonne != NULL) {
            printf("[%d, %d]", case_courrante_colonne->pos.ligne, case_courrante_colonne->pos.colonne);
            case_courrante_colonne = case_courrante_colonne->lien[2];
        }
        printf("\n");
        int i;
        for(i=0; i<nombre_espace*3; i++)
            printf(" ");
        
        case_courrante_ligne = case_courrante_ligne->lien[3];
        case_courrante_colonne = case_courrante_ligne;
        
        nombre_espace++;
    }
}



// Couleur estFini(Plateau *plateau);
// int taillePlateau(Plateau *plateau);
// int plusGrandGroupe(Plateau *plateau);
// void afficherPlateau(Plateau *plateau);
// int nombreCaseCouleur(Plateau *plateau);
// void supprimerPlateau(Plateau *plateau);
