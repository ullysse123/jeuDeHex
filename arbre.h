#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "plateau.h"
#include "case.h"

#define TAILLE_MAX 25 //Peut etre modifié mais ne dois pas dépasser 1000

typedef struct s_Arbre{
    
    bool peutGagner; //Variable qui nous servira a faire le menage a la fin
    Plateau plateau; //Stocke un plateau de jeux
    struct s_Arbre* pere;
    struct s_Arbre* fils[TAILLE_MAX*TAILLE_MAX]; //Stocke tous les coups suivant le coup actuelle possible soit plateau->taille - Tour
    int tour; //Stocke le tour auquel correspond un plateau, encore une fois pour faciliter le travail
    
}*Arbre;

/*
 * Fonction creerArbre
 *  _Objectif créer un arbre simple
 *  _Prend en entrée la taille du plateau pour identifier le nombre de lien
 *  _Renvoie l'arbre créée
 */
Arbre creerArbre(int taille);

/*
 * Fonction estVide
 *  _Objectif savoir si l'arbre est vide
 *  _Prend en entrée un arbre
 *  _Renvoie un booleen
 */
bool estVide (Arbre x);

/*
 * Fonction peutGagner
 *  _Objectif Identifier si l'arbre est gagnant ou pas
 *  _Prend en entrée un arbre et la couleur du joueur a tester
 *  _Renvoie un booleen
 */
bool peutGagner (Arbre x,Couleur c);

/*
 * Fonction ajouterFils
 *  _Objectif créer tous les fils d'un arbre avec leur plateau a jour
 *  _Prend en entrée un Arbre ( le père ) et la couleur a placé
 *  _Renvoie l'arbre fait
 */
Arbre ajouterFils (Arbre x,Couleur c);

/*
 * Fonction constructionArbre
 *  _Objectif construire l'arbre final avec toutes les possibilité de jeux gagnante d'une couleur
 *  _Prend en entrée une couleur ( celle de l'IA ) et un entier 0 ou 1 (0 si joueur commence, 1 si IA commence) ainsi que la taille du plateau
 *  _Renvoie un Arbre
 */
Arbre constructionArbre(Couleur c,int quiCommence,int taille);

/*
 * Fonction supprimerArbre
 *  _Objectif supprimer un arbre pour libérer la mémoire allouer
 *  _Prend en entrée un Arbre
 *  _Ne renvoie rien
 */
void supprimerArbre(Arbre x);