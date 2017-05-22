#ifndef AFFICHAGE

#define AFFICHAGE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define clrscr() printf("\033[H\033[2J")

#define couleur(param) printf("\033[%sm",param)

void affichage_entete_menu();

void affichage_entete();

void res_affichage_menu();

void res_affichage();

void affichage_menu_principal();

#endif


