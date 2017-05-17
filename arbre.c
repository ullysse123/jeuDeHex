#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "case.h"
#include "plateau.h"

typedef struct s_Element{
    int valeur;
} * Element;

typedef struct s_Arbre{
    struct s_Arbre * parent;
    struct s_Arbre *gauche;
    struct s_Arbre *droite;
    int valeur;
} *Arbre;

//Codage d'un arbre binaire basique pour commencer, je l'adapterai par la suite a nos besoins ( ABANDON CAR SUJET COMPRIS )

//Ce qu'il va falloir faire :
    //Creer un arbre des possibles stockant chaque coups pouvant etre jouer, chaque sous arbre contiens les coup suivant pouvant etre joué, ... Jusqu'a ce qu'il y ai plus de coup ou l'IA peut gagner
    //Créer une structure ayant taillePlateau branches.
    //Racine, plateau vide ( chaque sous arbres correspond au tour suivant : Tour 0 arbre vide, Tour 1 arbre avec une case joué, ... )
    //On génère l'arbre sous arbres par sous arbres, pour cela simuler N*N plateau, on ajoute que les plateau ou l'IA eut gagner
    //SE REFERER AU SCHEMA DE LA DOC TECHNIQUE SUR LA DERNIERE PAGE

//Fonction qui seront nécessaire
    //Créer arbre qui créer un arbre vide
    //Construction qui déroule la construction de l'arbre final
    //Ajouter arbre qui va pour chaque sous arbres génerer les coups suivant
    //Fonction peutGagner qui va verifier si l'IA peut encore gagner avec la configuration d'un Arbre
    //supprimerArbre fonction récursive qui va supprimer les arbres en partant du niveau le plus bas.
    //estVide fonction qui est verifie si un arbre est vide
    
//Pour la structure :
    //Faire un tableau de lien vers N*N sous arbres
    //Stocker un boolean nous indiquant si l'arbre peut gagner ( OPTIONNEL )
    //Stocker un boolean nous indiquant si l'abre est vide
    //Stocker un plateau

//Pour estVide :
    //Verifier si le booleen un true

//Pour créer arbre
    //Allouer taille nécessaire
    //Initialiser tous les liens a NULL
    //Insérer un plateau vide
    //Initialiser nos boolean

//Pour Construction
    //Créer notre racine d'abre vide
    //Faire fonctionner notre algorithme pour N*N
        //Créer un arbre
        //Le brancher a son père
        //Lui attribuer son père et jouer un coup
        //Faire sa jusqu'a ce que le père est tous les coup suivant de fait.
    //Mettre a jour le boolean avec la fonction peut encore gagner pour tous les niveau les plus bas
    //Remontter si tous les fils d'un arbre ne peuvent pas gagner alors le père ne peut pas non plus gagner ...
    //Supprimer tous les arbres qui ne peuvent pas gagner

//Pour peut gagner
    //Utiliser la fonction estFini et verifier si c'est bien l'IA qui a gagner
    //Si oui changer le booleen

//Pour supprimerArbre
    //Se rendre au feuille les plus basse est supprimer chacune des feuilles jusqu'a etre a la recine ( Récursif idéal ou itératif tordu )
    
//Changer racine
    //Changer la branche principal une fois un coup joué pour être sur de gagner.
    //Supprimer le père ainsi que tous les fils autre que notre nouvelles racine et ses fils

//Pour l'IA au final
    //On aura plus cas exploiter l'arbre pour tenter de trouver le chemin le plus court au final
    //Dès qu'un coup est jouer, on met a jour la racine de l'arbre
    //On fait chercher a l'arbre le chemin le plus court pour gagner
    //Il joue le coup et sa rechangera la racine ...
    //Au final le joueur sera baiser et galèrera sa race a gagner XD
    //Cest la joix ! Trouver toute cette merde a 5H30 du matin ! Je m'aime. Après j'y suis depuis 2h du mat' XD
    //La fatigue quoi, je coderai sa après le sommeil le plus proche que j'aurai donc surement après la nuit du 17 car la je vais pas pioncer sa sert a rien je serai trop décaler niveau sommeil.
    //Bwef Bwef direction un jeux vidéo le temps que les coupins se réveille, je vais etre un zombie demain  Genial mais au moins le livreur me reveillera pas.
    //Je m'arrette la car je parle solo en commentaire c'est chelou.

Arbre creerArbre(){
    Arbre x = (Arbre)malloc(sizeof(struct s_Arbre));
    x->parent = NULL;
    x->gauche = NULL;
    x->droite = NULL;
    x->valeur = -1;
    return x;
}

bool arbreVide(Arbre x){
    if ( x == NULL ) return true;
    else return ( x->valeur == -1 );
}

Arbre arbreGauche(Arbre x){
    return x->gauche;
}

Arbre arbreDroit(Arbre x){
    return x->droite;
}

Arbre arbreParent(Arbre x){
    return x->parent;
}

Arbre ajouterFeuille(Arbre *x,int v){
    Arbre (*cur) = x;
    Arbre parent = NULL;
    //Tant que l'on ne trouve pas de feuille arbreVide
    while ( !arbreVide(*cur) ){
        //Si la valeur est égale on sort
        if( (*cur)->valeur == v)return;
        parent = *cur;
        //Si la valeur est plus grande, on va à droite sinon à gauche
        cur=((*cur)->valeur>v)?&((*cur)->gauche):&((*cur)->droite);
    }
    //Si le parent n'est pas null, on attribue le parent
    if ( parent != NULL ){
        if ( parent->valeur>v ) parent->gauche = (*cur);
        else parent->droite = (*cur);
    }
    //On alloue la feuille et on change le parent et le root avec la valeur
    (*cur) = creerArbre();
    (*cur)->parent = parent;
    (*cur)->valeur = v;
}

void afficherArbre(Arbre x){
    
}

int main(){
    
    return 0;
}