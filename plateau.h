#ifndef __PLATEAU__H__
#define __PLATEAU__H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "case.h"


//Structure de notre plateau, contient la taille, les cases des differents angles.
typedef struct s_Plateau {
    int taille;
    struct s_Case* nord;
    struct s_Case* sud;
    struct s_Case* est;
    struct s_Case* ouest;
}*Plateau;

/*
 * Fonction créer plateau
 *  _Objectif créer notre plateau de jeu de taille variable
 *  _Prend en entrée la taille du la largeur/longueur du plateau souhaité
 *  _Renvoie un plateau créer
 */
Plateau creer_plateau(int taille);

/*
 * Fonction construction lien case :
 *  _Objectif créer les différents lien entre les cases
 *  _Prend en entrée un Plateau et une case
 *  _Ne renvoie rien.
 */
void construction_lien_case(Plateau plateau, Case x);

Case obtenir_case(Plateau plateau, int ligne, int colonne);

/*
 * Fonction affichage plateau
 *  _Objectif afficher notre plateau de jeu
 *  _Prend en entrée un plateau
 *  _Ne renvoie rien
 */
void affichage_plateau(Plateau plateau);

/*
 * Fonction est fini
 *  _Objectif indiquer quand la partie est fini et qui est le vainqueur
 *  _Prend en entrée un plateau
 *  _Renvoie une couleur
 */
Couleur estFini(Plateau plateau);

/*
 * Fonction taille plateau
 *  _Objectif renvoyer la taille de notre plateau
 *  _Prend en entrée un plateau
 *  _Renvoie une taille
 */
int taillePlateau(Plateau plateau);

/*
 * Fonction plus grand groupe
 *  _Objectif nous donner a taille du plus grand groupement d'hexagone d'une meme couleur
 *  _Prend en entrée un plateau
 *  _Renvoie un entier
 */
int plusGrandGroupe(Plateau plateau);

/*
 * Fonction nombre case couleur
 *  _Objectif nous indiquer le nombre de case coloré présente sur le plateau
 *  _Prend en entrée un plateau
 *  _Renvoie un entier
 */
int nombreCaseCouleur(Plateau plateau);

/*
 * Fonction supprimer plateau
 *  _Objectif libérer l'espace prix par notre plateau
 *  _Prend en entrée un plateau
 *  _ne renvoie rien
 */
void supprimerPlateau(Plateau plateau);

/*
 * Fonction d'affichage de la couleur
 *  _Objectif change la couleur par un caractere affin de l'afficher
 *  _Prend en entrée une case
 *  _renvoie un caractere
 */
char couleurToChar(Case c);

/*
 * Fonction qui copie un plateau
 *  _Objectif copier un plateau
 *  _Prend en entrée un plateau a copié
 *  _renvoie le plateau copié
 */
Plateau copierPlateau(Plateau x);

#endif