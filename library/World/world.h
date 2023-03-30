#include <stdio.h>
#include <stdlib.h>
/**
 * \brief Fichier qui contient les données du monde du jeu
 * 
 */

#include "../../constante.c"

#ifndef WORLD_H
#define WORLD_H

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

/**
 * \brief Représentation du monde du jeu
*/
struct world_s{
    sprite_t *vaisseau ; /*!< Représentation du vaisseau */
    sprite_t *mur; /*!< Représentation du météorite */
    sprite_t *ligneArriver;
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */
    int speed_h; /*!< Vitesse de déplacement horizontal des éléments du jeu */

};
/**
 * \brief Type qui correspond aux données du monde
 */

typedef struct world_s world_t;

void update_data(world_t *world);
/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * 
 * \param sprite 
 * \return int 0 si le sprite est dans l'écran, 1 sinon
 */
int isOverScreen(sprite_t *sprite);

int is_game_over(world_t *world);

void print_sprite(sprite_t *sprite);

sprite_t *init_sprite(sprite_t *sprite, int x, int y, int w, int h);

void init_data(world_t * world);

void clean_data(world_t * world);

#endif
