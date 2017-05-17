#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "plateau.h"
#include "case.h"

#define TAILLE_MAX 25 //Peut etre modifié mais ne dois pas dépasser 1000

typedef struct s_Arbre{
    
    bool peutGagner; //Variable qui nous servira a faire le menage a la fin
    Plateau plateau; //Stocke un plateau de jeux
    struct s_Arbre* fils[TAILLE_MAX*TAILLE_MAX]; //Stocke tous les coups suivant le coup actuelle possible soit plateau->taille - Tour
    int tour; //Stocke le tour auquel correspond un plateau, encore une fois pour faciliter le travail
    
}*Arbre;
