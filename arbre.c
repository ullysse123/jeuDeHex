#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "case.h"
#include "plateau.h"
#include "arbre.h"

    /////////////////////////////////
    /*Pile de sauvegarde d'un arbre*/
    /////////////////////////////////
    
    //Ne nous sert pas au final

// typedef struct s_Element{
//     Arbre x; //Stock le père a traiter
//     int indice; //Stock l'indice suivant a traiter
//     struct s_Element * next;
// }*Element;
//  
// typedef struct s_Pile{
//     Element top;
// }*Pile;
// 
// Pile creerPile(){
//     Pile p = (Pile)malloc(sizeof(struct s_Pile));
//     p->top = NULL;
//     return p;
// }
// 
// Pile push(Pile p, Arbre x, int i){
//     Element new=(Element)malloc(sizeof(struct s_Element));
//     new->x= x;
//     new->indice= i;
//     new->next = p->top;
//     p->top = new;
//     return(p);
// }
// 
// bool emptyPile(Pile p){
//     return (p->top == NULL);
// }
// 
// Pile pop(Pile p){
//     assert(!empty(p));
//     Element e = p->top;
//     p->top = e->next;
//     free(e);
//     return (p);
// }
// 
// Element top(Pile p){
//     assert(!empty(p));
//     return(p->top);
// }
// 
// void supprimerPile(Pile p){
//     while(!empty(p)){
//         pop(p);
//     }
//     free(p);
// }
    
    ///////////////////////
    /*Fonction de l'arbre*/
    ///////////////////////
    
//Fonction de creation d'un arbre
Arbre creerArbre(int taille){
    Arbre x = (Arbre)malloc(sizeof(struct s_Arbre));
    x->plateau = creer_plateau(taille);
    x->peutGagner = false;
    x->pere = NULL;
    for (int i = 0; i<(x->plateau->taille*x->plateau->taille);i++){
        x->fils[i] = NULL;
    }
    x->tour = 0;
    return x;
}

//Fonction estVide
bool estVide (Arbre x){

    return x == NULL;
}

//Fonction peut gagner
bool peutGagner (Arbre x,Couleur c){
    return c == estFini(x->plateau);
}

//Fonction ajouter fils ? ( Va rajouter tous les fils possible d'un arbre )
Arbre ajouterFils (Arbre x,Couleur c){

    Arbre parent = x;
    Arbre cur;
    Case traitement;
    int taille = parent->plateau->taille;
    int i=0;
    int xCoord=0;
    int yCoord=0;
    //On créer un fils par possibilité de coup suivant
    while (xCoord<taille){

        while (yCoord<taille){

            if(couleurCase(obtenir_case(parent->plateau,xCoord,yCoord))==VIDE){

                cur = creerArbre(parent->plateau->taille);
                parent->fils[i] = cur;
                cur->pere = parent;
                cur->plateau = copierPlateau(parent->plateau);
                traitement=obtenir_case(cur->plateau,xCoord,yCoord);
                traitement=modifierCase(traitement,c);
                cur->tour=parent->tour+1;
                i++;

            }
            yCoord++;

        }
        yCoord=0;
        xCoord++;

    }
;
    while(i<taille*taille){
        //Tous les fils non alloué reçoivent NULL
        parent->fils[i]=NULL;
        i++;
    }

    return x;
}

//SupprimerFeuille
void supprimerFeuille(Arbre cur){

    bool trouve = false;
    int i = -1;
    while(!trouve){
        i++;
        if(cur->pere->fils[i]==cur){
            trouve=true;
        }
    }
    cur->pere->fils[i]=NULL;
    supprimerPlateau(cur->plateau);
    free(cur);
}

//Fonction supprimer arbre
void supprimerArbre(Arbre cur){
    if(estVide(cur)) return;
    else{
        for (int i = 0; i < ((cur->plateau->taille * cur->plateau->taille)-(cur->tour)+1); i++){
            if(!estVide(cur->fils[i])){
                supprimerArbre(cur->fils[i]);
            }
        }
        supprimerPlateau(cur->plateau);
        free(cur);
    }
}

//Fonction monterArbre
void monterArbre(Arbre cur, Couleur Pair, Couleur Impaire){

    if(estVide(cur)){

        return;
    }
    else{

        //On creer le fils en fonction de la couleur qui doit jouer
        if ((cur->tour+1)%2 == 0){

            cur = ajouterFils(cur,Pair);
        }else{

            cur = ajouterFils(cur,Impaire);
        }
        
        for (int i = 0; i < ((cur->plateau->taille * cur->plateau->taille)-(cur->tour)+1); i++){

            monterArbre(cur->fils[i],Pair,Impaire);
        }

    }

}

//Fonction marquerFilsPlusBas
void marquerFilsPlusBas(Arbre cur,Couleur c){

    if(estVide(cur))
        return;
    else{
     
        for (int i = 0; i < ((cur->plateau->taille * cur->plateau->taille)-(cur->tour)+1); i++){

            marquerFilsPlusBas(cur->fils[i],c);
        }
        if(estFini(cur->plateau) == c) cur->peutGagner=true;
    }
}

//Fonction marquerFilsAutre
void marquerFilsAutre(Arbre cur){

    if(estVide(cur)){

        return;
    }
    else{
        

        for (int i = 0; i < ((cur->plateau->taille * cur->plateau->taille)-(cur->tour)+1); i++){

            marquerFilsAutre(cur->fils[i]);
        }
        

        for (int i = 0; i < ((cur->plateau->taille * cur->plateau->taille)-(cur->tour)+1); i++){

            if(!estVide(cur->fils[i])){
                if(cur->fils[i]->peutGagner) cur->peutGagner = true;
            }
        }
    }
}
    
//Fonction supprimerPerdant
void supprimerPerdant(Arbre cur){

    if(estVide(cur)) return;
    else{
        for (int i = 0; i < ((cur->plateau->taille * cur->plateau->taille)-(cur->tour)+1); i++){
            supprimerPerdant(cur->fils[i]);
        }
        if(cur->pere != NULL && cur->fils[0]==NULL){
            supprimerFeuille(cur);
        }
    }
}

//Fonction qui construit l'arbre final
Arbre constructionArbre(Couleur c,int quiCommence,int taille){ //Penser a dessiner déroullement de la construction
    //On créé la racine de notre arbre
    Arbre root = creerArbre(taille);
    
    //On indique quel couleur joue au tour pair et impaire
    Couleur Pair;
    Couleur Impaire;
    if ( quiCommence == 0 ){
        Pair = c;
        Impaire = c%2+1;
    }else{
        Impaire = c;
        Pair = c%2+1;
    }
    
    //On créer l'arbre
    monterArbre(root,Pair,Impaire);

    //On marque les feuille qui peuvent gagner
    marquerFilsPlusBas(root,c);
    
    //On met les noeud qui peuvent gagner
    marquerFilsAutre(root);

    //On supprime ceux qui ne peuvent pas gagner
    supprimerPerdant(root);
    
    return root;
    
}



