/**
 * \file sprites.h
 * \author M Moulias 
 * \brief Fichier qui contient les fonctions liée aux sprites du jeu
 * \version 0.1
 * \date 2023-04-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <stdlib.h>


#ifndef SPRITES_H
#define SPRITES_H

/**
 * \brief La structure qui contient les données du sprite
 * 
 * \param x
 * \param y
 * \param w
 * \param h
 */
struct sprite_s{
    int x;
    int y;
    int w;
    int h;
    char * id;
};

typedef struct sprite_s sprite_t;

/**
 * \brief La fonction indique si le sprite est hors de l'écran
 * 
 * \param sprite 
 * \return int 
 */
int isOverScreen(sprite_t *sprite);

/**
 * \brief La fonction affiche le sprite
 * 
 * \param sprite 
 */
void print_sprite(sprite_t *sprite);

/**
 * \brief La fonction initialise les sprites du jeu
 * 
 * \param sprite 
 * \param x 
 * \param y 
 * \param w 
 * \param h 
 * \return sprite_t* 
 */
sprite_t *init_sprite(sprite_t *sprite, int x, int y, int w, int h, char id);

/**
 * \brief La fonction indique si les sprites se touchent
 * 
 * \param sp1 
 * \param sp2 
 * \return int 0 si les sprites ne se touchent pas, 1 sinon
 */
int sprites_collide(sprite_t *sp1, sprite_t *sp2);

#endif