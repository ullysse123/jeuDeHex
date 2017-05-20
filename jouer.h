#ifndef __JOUER__H__
#define __JOUER__H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "plateau.h"


    int suppr_Tmp();

    int sauvegarde_coup_tmp(Case c);
    
/*
 * Fonction qui commence :
 *  _Objectif choisir qui commence soit les joueurs choisissent, soit un random est fait
 *  _Ne prend rien en entrée
 *  _Renvoie un entier
 */
int quiCommence();

/*
 * Fonction jouer :
 *  _Objectif gérer une partie jusqu'a ce que les joueurs choisissent d'abandonner ou qu'un gagnant est trouvé
 *  _Ne prend pas d'entrée
 *  _Ne renvoie rien
 */
Case jouer(Plateau plateau, Couleur joueur);

/*
 * Fonction sauvegarde
 *  _Objectif sauvegarder le plateau dans un fichier
 *  _Prend en entrée le plateau de jeu
 *  _renvoie 1 si erreur , 0 si ok
 */
int sauvegarde(Plateau plateau);

/*
 * Fonction charger
 *  _Objectif charger un plateau a l'aide d'un fichier de sauvegarde
 *  _Prend en entrée un fichier et l'id du joueur courant
 *  _Renvoie un plateau et la valeur du prochain joueur
 */
Plateau charger(char nom[36], int *idJoueur);


/*
 * Fonction abandonner
 *  _Objectif supprimer le plateau et la sauvegarde si le joueur choisie de ne pas la garder/ ou on lui propose de stocker le plateau dans une save pour reprendre plus tard
 *  _Prend en entrée un plateau
 *  _Renvoie un booleen
 */
bool abandonner (Plateau plateau);

/*
 * Fonction nouvellePartie
 *  _Objectif créer le plateau de jeux et lance la partie
 *  _Ne prend pas d'entrée
 *  _Renvoie le plateau créé
 */
Plateau nouvellePartie ();


/*
 * Fonction annuler
 *  _Objectif annule le coup d'une case
 *  _Prend une case
 *  _Ne Renvoie Rien
 */
void annuler(Case c);

int annuler_dernier_coup(Plateau plateau);

#endif
