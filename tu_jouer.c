#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "jouer.h"

int main(){
    Plateau plateau;
    plateau = charger("save/connard.txt");
    affichage_plateau(plateau);
    return 0;
}