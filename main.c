#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "jouer.h"

void affichage_entete(){
    //Petite fonction affichant la banderole "Jeu De Hex"
    printf("================================================\n");
    printf("\n");
    printf("   ___             ______       _   _            \n");
    printf("  |_  |            |  _  \\     | | | |           \n");
    printf("    | | ___ _   _  | | | |___  | |_| | _____  __ \n");
    printf("    | |/ _ \\ | | | | | | / _ \\ |  _  |/ _ \\ \\/ / \n");
    printf("/\\__/ /  __/ |_| | | |/ /  __/ | | | |  __/>  <  \n");
    printf("\\____/ \\___|\\__,_| |___/ \\___| \\_| |_/\\___/_/\\_\\ \n");
    printf("\n");
    printf("================================================\n");
    printf("\n");
    
}

int menu_lancement(){
    //Menu apparaissant au lancement du jeux
    int choix;
    int confirmer;
    printf("\n");
    printf("Bienvenue sur le Jeu De Hex,\nQue souahitez vous faire ?\n");
    printf(" -- LANCER UNE NOUVELLE PARTIE --            (1)\n");
    printf(" -- CHARGER UNE PARTIE EXISTANTE --          (2)\n");
    printf(" -- QUITTER LE JEU --                        (3)\n");
    do{
        do{
            printf("Selectionnez votre choix :\n");
            scanf("%d",&choix);
            printf("\n");
        }while(choix<1 || choix>3);
        printf("Confirmez vous votre choix ? Si oui tapez 1 sinon le chiffre de votre choix\n");
        scanf("%d",&confirmer);
        printf("\n");
    }while(confirmer != 1);
    printf("\n");
    return choix;
}

int menu_jeu(){
    //Menu apparaissant durant une partie a chaque tours
    int choix;
    int confirmer;
    printf("\n");
    printf("Coup joue,\nQue souhaitez vous faire ?\n");
    printf(" -- PASSER AU TOUR SUIVANT --                (1)\n");
    printf(" -- ANULER LE DERNIER COUP JOUE --           (2)\n");
    printf(" -- ABANDONNER LA PARTIE --                  (3)\n");
    do{
        do{
            printf("Selectionnez votre choix :\n");
            scanf("%d",&choix);
            printf("\n");
        }while(choix<1 || choix>3);
        printf("Confirmez vous votre choix ? Si oui tapez 1 sinon le chiffre de votre choix\n");
        scanf("%d",&confirmer);
        printf("\n");
    }while(confirmer != 1);
    printf("\n");
    return choix;
}

int menu_fin(){
    //Menu apparaissant à la fin d'une partie
    int choix;
    int confirmer;
    printf("\n");
    printf("Que souhaitez vous faire maintenant ?\n");
    printf(" -- LANCER UNE NOUVELLE PARTIE --            (1)\n");
    printf(" -- CHARGER UNE PARTIE EXISTANTE --          (2)\n");
    printf(" -- QUITTER LE JEU --                        (3)\n");
    do{
        do{
            printf("Selectionnez votre choix :\n");
            scanf("%d",&choix);
            printf("\n");
        }while(choix<1 || choix>3);
        printf("Confirmez vous votre choix ? Si oui tapez 1 sinon le chiffre de votre choix\n");
        scanf("%d",&confirmer);
        printf("\n");
    }while(confirmer != 1);
    printf("\n");
    return choix;
}

int demande_save(){
    int choix;
    printf("\n");
    printf("Souhaitez vous effectuer une sauvegarde de votre partie ? Si oui tapez 1 sinon le chiffre de votre choix\n");
    scanf("%d",&choix);
    if( choix != 1) choix=0;
    return choix;
}

int main(){
    int i;
    affichage_entete();
    i = menu_lancement();
    //Menu de lancement :
        //Nouvelle Partie
        //Charger Partie
        //Quitter le jeux
    
    //Si Nouvelle partie
        //Lancer une nouvelle parie
    //Si Charger Partie
        //Charger la partie
    //Si quitter
        //Fermer le programme
    
    //Tant que Arret est faux
        //Jouer
        //Afficher plateau
        //Menu de jeux :
            //Valider coup  
            //Annuler le coup
            //Sauvegarder
            //Abandonner ( demande une si il veut sauvegarder )
        //Si il veux sauvegarder
            //Sauvegarder
        //Si il veux valider
            // sauvegarde temporaire du coup jouer
            //Passe au joueur suivant
            //Verifier si est fini et recuperer la couleur
            //Si est fini = NOIR ou ROUGE alors Arret deviens vrai
        //Sinon si il veux abandonner
            //Lancer abandonner
            //Supprimer fichier temp
            //Passer arret a vrai
        //Sinon si il veut annuler
            //Annuler et laisser reboucler
    
    //Si la couleur est différente de vide
        //Afficher le gagnant et le plateau
    
    //Menu de fin:
        //Nouvelle partie
        //Charger Partie
        //Quitter le jeux
    
    //Si il quitte
        //Supprimer fichier temp
    
    //En fonction du choix reboucler
        
    return 0;
}
