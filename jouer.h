#ifndef __JOUER__H__
#define __JOUER__H__

#include <stdio.h>
#include <stdlib.h>
#include <stdool.h>

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
void jouer();

/*
 * Fonction sauvegarde
 *  _Objectif sauvegarder le plateau dans un fichier
 *  _Prend en entrée le plateau de jeu
 *  _Ne renvoie rien
 */
void sauvegarde(Plateau plateau);

/*
 * Fonction charger
 *  _Objectif charger un plateau a l'aide d'un fichier de sauvegarde
 *  _Prend en entrée un fichier
 *  _Renvoie un plateau
 */
Plateau charger (FILE *fichier);

/*
 * Fonction annuler
 *  _Objectif annuler le dernier coup joué
 *  _Prend en entrée le plateau de jeux et un fichier
 *  _Renvoie un plateau
 */
Plateau annuler (Plateau plateau, FILE* fichier);

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
 * Fonction affichage_plateau_sauvegarde
 *  _Objectif formate l'affichage pour la sauvegarde
 *  _Prend un ptateau en entrée
 *  _Renvoie l'affichage du tableau
 */
void affichage_plateau_sauvegarde(Plateau plateau);

#endif