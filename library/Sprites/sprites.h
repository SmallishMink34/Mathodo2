/**
 * \brief Le fichier qui gères les sprites
 */
#include <stdio.h>
#include <stdlib.h>


#ifndef SPRITES_H
#define SPRITES_H
/**
 * \brief Représentation pour stocker les données du vaisseau ou autre sprites
 * 
 */

struct sprite_s{
    int x;
    int y;
    int w;
    int h;
};

typedef struct sprite_s sprite_t;


int isOverScreen(sprite_t *sprite);

void print_sprite(sprite_t *sprite);

/**
 * \brief La fonction initialise les sprites du jeu
 * 
 * \param sprite 
 * \param x 
 * \param y 
 * \param w 
 * \param h 
 */
sprite_t *init_sprite(sprite_t *sprite, int x, int y, int w, int h);

/**
 * \brief La fonction libère les données du sprite
 * 
 * \param sp1 
 * \param sp2 
 * \return int 0 si les sprites ne se touchent pas, 1 sinon
 */
int sprites_collide(sprite_t *sp1, sprite_t *sp2);

#endif