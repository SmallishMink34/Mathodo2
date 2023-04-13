#include <stdio.h>
#include <stdlib.h>
#include "../Sprites/sprites.h"
#include "../../constante.c"
#include <SDL2/SDL.h>

/**
 * \file world.h
 * \author M Moulias 
 * \brief Fichier qui contient les fonctions liées au monde du jeu
 * \version 0.1
 * \date 2023-04-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef WORLD_H
#define WORLD_H

/**
 * \brief La structure qui contient les données du monde
 * 
 * \param vaisseau Vaisseau du joueur
 * \param mur Météorite
 * \param murs Tableau de météorites 
 * \param nb_murs Nombre de météorites 
 * \param ligneArriver Ligne d'arrivée
 * \param gameover Champ indiquant si l'on est à la fin du jeu
 * \param speed_h Vitesse de déplacement horizontal des éléments du jeu
 * \param startTimer  Timer de départ
 * \param timer  Timer de jeu
 * 
 */
struct world_s{
    sprite_t *vaisseau ; /*!< Représentation du vaisseau */
    sprite_t **murs; /*<Représentation des météorites>*/
    int nb_murs; // Nombre de météorites
    int nb_lines_murs; // Nombre de lignes de météorites
    sprite_t *ligneArriver;
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */
    float speed_h; /*!< Vitesse de déplacement horizontal des éléments du jeu */
    unsigned int startTimer; /*!< Timer de départ */
    unsigned int timer; /*!< Timer de jeu */
    char * str; // String affichant le temps sur le jeu
};
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
 * 
 * \return int 0 si les sprites ne se touchent pas, 1 sinon
 */
int handle_sprite_collide(sprite_t *sp1, sprite_t *sp2, world_t *world, int make_disappear);

/**
 * \brief La fonction initialise les murs du jeu
 * 
 * \param world 
 */
void init_walls(world_t *world);

/**
 * \brief La fonction met à jour les murs du jeu
 * 
 * \param world 
 */
void update_walls(world_t *world);


#endif
