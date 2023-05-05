#include <stdio.h>
#include <stdlib.h>
#include "../../src/include/SDL2/SDL.h"

#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES 

#define LARGEUR_FENETRE 704
#define HAUTEUR_FENETRE 704


struct btn{
    SDL_Rect rect;
}

typedef struct btn_t ;

btn_t *init_btn(int x, int y, int w, int h);
int collidePoint(btn_t *btn, int x, int y);

#endif