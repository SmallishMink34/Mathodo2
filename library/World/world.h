#include <stdio.h>
#include <stdlib.h>
#include "../Sprites/sprites.h"
#include "../../constante.c"
/**
 * \brief Fichier qui contient les données du monde du jeu
 * 
 */

#ifndef WORLD_H
#define WORLD_H


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

/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param les données du monde
 */
void update_data(world_t *world);
/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */

int is_game_over(world_t *world);

/**

/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */

void init_data(world_t * world);

/**
 * \brief La fonction libère les données du monde
 * 
 * \param world les données du monde
 */
void clean_data(world_t * world);

/**
 * \brief La fonction indique si le sprite est en collision avec un autre sprite
 * 
 * \param sp1 
 * \param sp2 
 * \param world 
 * \param make_disappear 
 */
void handle_sprite_collide(sprite_t *sp1, sprite_t *sp2, world_t *world, int make_disappear);

#endif
