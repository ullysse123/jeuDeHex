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
//     printf("EST VIDE ?\n");
    return x == NULL;
}

//Fonction peut gagner
bool peutGagner (Arbre x,Couleur c){
    return c == estFini(x->plateau);
}

//Fonction ajouter fils ? ( Va rajouter tous les fils possible d'un arbre )
Arbre ajouterFils (Arbre x,Couleur c){
//     printf("Je rentre dans ajouterFils\n");
    Arbre parent = x;
    Arbre cur;
    Case traitement;
    int taille = parent->plateau->taille;
    int i=0;
    int xCoord=0;
    int yCoord=0;
    //On créer un fils par possibilité de coup suivant
    while (xCoord<taille){
//         printf("Taille : %d, xCoord = %d, yCoord = %d, i= %d\n",taille,xCoord,yCoord,i);
        while (yCoord<taille){
//             printf("Taille : %d, xCoord = %d, yCoord = %d\n",taille,xCoord,yCoord);
            if(couleurCase(obtenir_case(parent->plateau,xCoord,yCoord))==VIDE){
//                 printf("Rassure moi je rentre ici ?\n");
                cur = creerArbre(parent->plateau->taille);
                parent->fils[i] = cur;
                cur->pere = parent;
                cur->plateau = copierPlateau(parent->plateau);
                traitement=obtenir_case(cur->plateau,xCoord,yCoord);
                traitement=modifierCase(traitement,c);
                cur->tour=parent->tour+1;
                i++;
                affichage_plateau(cur->plateau);
            }
            yCoord++;
//             printf("Taille : %d, xCoord = %d, yCoord = %d\n",taille,xCoord,yCoord);
        }
        yCoord=0;
        xCoord++;
//         printf("Taille : %d, xCoord = %d, yCoord = %d\n",taille,xCoord,yCoord);
    }
//     printf("Je sors du while\n");
    while(i<taille*taille){
        //Tous les fils non alloué reçoivent NULL
        parent->fils[i]=NULL;
        i++;
    }
//     printf("Je sors de ajouterFils\n");
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
    free(cur);
}

//Fonction supprimer arbre
void supprimerArbre(Arbre cur){
    if(estVide(cur)) return;
    else{
        for (int i = 0; i < ((cur->plateau->taille * cur->plateau->taille)-(cur->tour)+1); i++){
            supprimerArbre(cur->fils[i]);
        }
        supprimerFeuille(cur);
    }
}

//Fonction monterArbre
void monterArbre(Arbre cur, Couleur Pair, Couleur Impaire){
//     printf("Je Rentre dans monterArbre\n");
    if(estVide(cur)){
//         printf("Je Sors de monterArbre\n");
        return;
    }
    else{
//         printf("On Commence Traitement\n");
        //On creer le fils en fonction de la couleur qui doit jouer
        if ((cur->tour+1)%2 == 0){
//             printf("Tour Impaire\n");
            cur = ajouterFils(cur,Pair);
        }else{
//             printf("Tour Paire\n");
            cur = ajouterFils(cur,Impaire);
        }
        for (int i = 0; i < ((cur->plateau->taille * cur->plateau->taille)-(cur->tour)+1); i++){
//             printf("Appelle recursif vers fils %d alors qu nous somme au niveau Tour : %d\n",i,cur->tour);
            monterArbre(cur->fils[i],Pair,Impaire);
        }
//         printf("Fin Traitement\n");
    }
//     printf("Sortie Final\n");
}

//Fonction marquerFilsPlusBas
void marquerFilsPlusBas(Arbre cur,Couleur c){

    if(estVide(cur))
        return;
    else{

//         if(cur->fils[0] == NULL){
//             //Si on est au plus bas on teste si la feuille peut gagner
//             if(estFini(cur->plateau) == c) cur->peutGagner=true;
//         }
//((cur->plateau->taille * cur->plateau->taille)-(cur->tour)+1)        
        for (int i = 0; i < ((cur->plateau->taille * cur->plateau->taille)-(cur->tour)+1); i++){

            marquerFilsPlusBas(cur->fils[i],c);
        }
        if(estFini(cur->plateau) == c) cur->peutGagner=true;
    }
}

//Fonction marquerFilsAutre
void marquerFilsAutre(Arbre cur){
    printf("Rentre\n");
    if(estVide(cur)){
        printf("est vide donc sors\n");
        return;
    }
    else{
        
        printf("Avant for appelle rec\n");
        for (int i = 0; i < ((cur->plateau->taille * cur->plateau->taille)-(cur->tour)+1); i++){
            printf("Appelle recursif avec i = %d\n",i);
            marquerFilsAutre(cur->fils[i]);
        }
        
        printf("Avant for verification peutGagner\n");
        for (int i = 0; i < ((cur->plateau->taille * cur->plateau->taille)-(cur->tour)+1); i++){
            printf("Test du peutGagner\n");
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
            marquerFilsAutre(cur->fils[i]);
        }
        supprimerFeuille(cur);
    }
}

//Fonction qui construit l'arbre final
Arbre constructionArbre(Couleur c,int quiCommence,int taille){ //Penser a dessiner déroullement de la construction
    //On créé la racine de notre arbre
    Arbre root = creerArbre(taille);
//     Arbre cur = root
    //Sauvegarde de la position et de l'indice
//     Element save;
    //Pile de sauvegarde
//     Pile p = creerPile();
    //Autres variables
//     int i = 0;
//     int tour;
    //On initialise la couleur en fonction de quiCommence
    Couleur Pair;
    Couleur Impaire;
    if ( quiCommence == 0 ){
        Pair = c;
        Impaire = c%2+1;
    }else{
        Impaire = c;
        Pair = c%2+1;
    }
    //Booleen de fin de boucle
//     bool fini = false;
    
    //Tant que l'on a pas fini de tout créer
//     while(!fini){
//         
//         //On creer le fils en fonction de la couleur qui doit jouer
//         if ((cur->tour+1)%2 = 0){
//             cur = ajouterFils(cur,Pair);
//         }else{
//             cur = ajouterFils(cur,Impaire);
//         }
//         //On sauvegarde l'indice i ainsi que la position 
//         p = push(p,cur,i);
//         //On verifie que l'on peut encore faire des fils
//         if (cur->fils[0]==NULL){
//             save = top(p);
//             p = pop(p);
//             cur = save->x;
//             i = save->indice+1;
//             if(cur->fils[i+1]!=NULL){
//                 p = push(p,cur,i);
//             }
//             cur = cur->fils[i];
//             i = 0;
//         }else{
//             //On verifie si on a traiter tous les fils
//             if (cur->fils[i] == NULL){
//                 save = top(p);
//                 p = pop(p)
//                 cur = save->x;
//                 i = save->indice+1;
//                 if(cur->fils[i+1]!=NULL){
//                     p = push(p,cur,i);
//                 }
//                 cur = cur->fils[i];
//                 i = 0;
//                 
//             }else{
//             //Cas générale
//                 i = 0;
//                 cur = cur->fils[i];
//                 
//             }
//         }
//         //On commence par verifier que l'on a fini ou pas le traitement
//         if ( cur == root && i>=taille*taille ){
//             fini = true;
//         }
//     }
//     printf("Infini ?\n");
    //On monte notre arbre
    monterArbre(root,Pair,Impaire);
//     printf("Infini ?\n");
    //On verifie la dernière ligne pour voir qui peutGagner
//     i = 0;
//     cur = root;
    marquerFilsPlusBas(root,c);
//     printf("Infini ?\n");
    //On remonte de la feuille peutGagner a la racine pour passer tous ses parent a true (while present en simple securité)
    while(!root->peutGagner){
//         printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n-----------------------\nLOOOKKKKK\n-------------------\n\n\n\n\n\n\n\n\n\n\n\n");
        marquerFilsAutre(root);
    }
    printf("Infini ?\n");
    //On parcour l'arbre et on supprime tous les element qui ne peuvent pas gagner en partant du bas en appellant supprimerArbre
    supprimerPerdant(root);
    
    //On retourne l'arbre
    return root;
    
}


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
    


