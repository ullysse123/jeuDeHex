#include <stdio.h>
#include <stdlib.h>

#include "affichage.h"

void affichage_entete_menu(){
    //Petite fonction affichant la banderole "Jeu De Hex"

    //couleur("31");
    
    printf(" \xE2\x95\x94");
    int i;
    for(i = 0; i<50; i++)
        printf("\xE2\x95\x90");
    printf("\xE2\x95\x97\n");

    printf(" \xE2\x95\x91    ___             ______       _   _            \xE2\x95\x91\n");
    printf(" \xE2\x95\x91   |_  |            |  _  \\     | | | |           \xE2\x95\x91\n");
    printf(" \xE2\x95\x91     | | ___ _   _  | | | |___  | |_| | _____  __ \xE2\x95\x91\n");
    printf(" \xE2\x95\x91     | |/ _ \\ | | | | | | / _ \\ |  _  |/ _ \\ \\/ / \xE2\x95\x91\n");
    printf(" \xE2\x95\x91 /\\__/ /  __/ |_| | | |/ /  __/ | | | |  __/>  <  \xE2\x95\x91\n");
    printf(" \xE2\x95\x91 \\____/ \\___|\\__,_| |___/ \\___| \\_| |_/\\___/_/\\_\\ \xE2\x95\x91\n");
    printf(" \xE2\x95\x91                                                  \xE2\x95\x91\n");
    
    printf(" \xE2\x95\xA0");
    for(i = 0; i<50; i++)
        printf("\xE2\x95\x90");
    printf("\xE2\x95\xA3\n");
}

void affichage_entete(){
    //Petite fonction affichant la banderole "Jeu De Hex"

    //couleur("31");
    
    printf(" \xE2\x95\x94");
    int i;
    for(i = 0; i<50; i++)
        printf("\xE2\x95\x90");
    printf("\xE2\x95\x97\n");

    printf(" \xE2\x95\x91    ___             ______       _   _            \xE2\x95\x91\n");
    printf(" \xE2\x95\x91   |_  |            |  _  \\     | | | |           \xE2\x95\x91\n");
    printf(" \xE2\x95\x91     | | ___ _   _  | | | |___  | |_| | _____  __ \xE2\x95\x91\n");
    printf(" \xE2\x95\x91     | |/ _ \\ | | | | | | / _ \\ |  _  |/ _ \\ \\/ / \xE2\x95\x91\n");
    printf(" \xE2\x95\x91 /\\__/ /  __/ |_| | | |/ /  __/ | | | |  __/>  <  \xE2\x95\x91\n");
    printf(" \xE2\x95\x91 \\____/ \\___|\\__,_| |___/ \\___| \\_| |_/\\___/_/\\_\\ \xE2\x95\x91\n");
    printf(" \xE2\x95\x91                                                  \xE2\x95\x91\n");
    
    printf(" \xE2\x95\x9A");
    for(i=0; i<50; i++)
        printf("\xE2\x95\x90");
    printf("\xE2\x95\x9D\n");
}

void res_affichage_menu() {
    clrscr();
    affichage_entete_menu();
}

void res_affichage() {
    clrscr();
    affichage_entete();
}

void affichage_menu_principal() {
    printf(" \xE2\x95\x91 MENU PRINCIPAL                                   \xE2\x95\x91\n");
    printf(" \xE2\x95\x91    (1) LANCER UNE NOUVELLE PARTIE                \xE2\x95\x91\n");
    printf(" \xE2\x95\x91    (2) CHARGER UNE PARTIE EXISTANTE              \xE2\x95\x91\n");
    printf(" \xE2\x95\x91    (3) QUITTER LE JEU                            \xE2\x95\x91\n");

    printf(" \xE2\x95\x9A");
    int i;
    for(i = 0; i<50; i++)
        printf("\xE2\x95\x90");
    printf("\xE2\x95\x9D\n");
}

