/**
 * \file menu.h
 * \author M Moulias 
 * \brief Fichier qui contient les fonctions liées au menu 
 * \version 0.1
 * \date 2023-04-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include "../../src/include/SDL2/SDL.h"

#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES 

#include <stdbool.h>

struct btn{
    SDL_Rect rect;
};

typedef struct btn btn_t;

btn_t *init_btn(int x, int y, int w, int h);
bool collidePoint(btn_t *btn, int x, int y);

#endif