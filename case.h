#ifndef __CASE__H__
#define __CASE__H__
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


//Structure permettant de stocker des coordonnées ligne et colonne
typedef struct s_Position{
    int ligne;
    int colonne;
} Position;

//Enumeration des couleurs du jeu : ROUGE // NOIR // VIDE
typedef enum e_Couleur{
    ROUGE = 1, 
    NOIR  = 2, 
    VIDE  = 0
} Couleur;

//Structure de notre case contenant Position, Couleur et liens
typedef struct s_Case{
    Position pos;
    Couleur valeur;
    bool murDeb;
    bool murFin;
    struct s_Case* lien[6];
}*Case;

/*
 * Fonction créer case :
 *  _Objectif créer une case vierge
 *  _Prend en entrée les coordonnée x et y que l'on souhaite attribuer a la case
 *  _Renvoie une case vierge
 */
Case creer_case(int ligne, int colonne);

/*
 * Fonction modifier case :
 *  _Objectif modifier la couleur de la case
 *  _Prend en entrée la case a modifier et la couleur a lui attribuer
 *  _Renvoie la case modifié
 */
Case modifierCase(Case caseModifier, Couleur valeur);

/*
 * Fonction couleur case :
 *  _Objectif obtenir la couleur de la case
 *  _Prend en entrée une case
 *  _Renvoie la couleur de la case
 */
Couleur couleurCase(Case x);

/*
 * Fonction obtenir coordonnée :
 *  _Objectif connaitre les coordonnée de la case
 *  _Prend en entrée une case
 *  _Renvoie la position de cette case
 */
Position obtenirCoordonnee(Case x);

/*
 * Fonction supprimer case :
 *  _Objectif libérer supprimer la case en libérant l'espace mémoire utiliser et en dé-tissant les lien
 *  _Prend en entrée la case a supprimer
 *  _Ne renvoie rien
 */
void supprimerCase(Case x);

#endif