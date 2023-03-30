#include "world.h"

/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param les données du monde
 */

void update_data(world_t *world){
    world->ligneArriver->y += INITIAL_SPEED - world->speed_h;
    world->mur->y += INITIAL_SPEED - world->speed_h;
}

/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */

int is_game_over(world_t *world){
    return world->gameover;
}

void print_sprite(sprite_t *sprite){
    printf("x = %d, y = %d, w = %d, h = %d\n", sprite->x, sprite->y, sprite->w, sprite->h);
}

/**
 * \brief La fonction initialise les sprites du jeu
 * 
 * \param sprite 
 * \param x 
 * \param y 
 * \param w 
 * \param h 
 */
sprite_t *init_sprite(sprite_t *sprite, int x, int y, int w, int h){
    sprite = malloc(sizeof(sprite_t));
    sprite->x = x;
    sprite->y = y;
    sprite->w = w;
    sprite->h = h;
    return sprite;
}

/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */


void init_data(world_t * world){
    
    //on n'est pas à la fin du jeu
    world->gameover = 0;
    world->speed_h = 0;

    // Initialisation du vaisseau
    world->vaisseau = init_sprite(world->vaisseau, SCREEN_WIDTH/2 - SHIP_SIZE/2, SCREEN_HEIGHT - SHIP_SIZE, SHIP_SIZE, SHIP_SIZE);
    world->mur = init_sprite(world->mur, 0, 0, 3*METEORITE_SIZE, 7*METEORITE_SIZE);
    world->ligneArriver = init_sprite(world->ligneArriver, 0, -40, SCREEN_WIDTH, FINISH_LINE_HEIGHT);

    print_sprite(world->vaisseau);
}


/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */


void clean_data(world_t *world){
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
    free(world->vaisseau);
}


