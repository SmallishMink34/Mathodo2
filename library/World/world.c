#include "world.h"


void update_data(world_t *world){
    world->ligneArriver->y += (int)world->speed_h;
    update_walls(world);
    if (isOverScreen(world->vaisseau)){
        if (world->vaisseau->x < 0) world->vaisseau->x = 0;
        if (world->vaisseau->x + world->vaisseau->w > SCREEN_WIDTH) world->vaisseau->x = SCREEN_WIDTH - world->vaisseau->w;
        if (world->vaisseau->y < 0) world->vaisseau->y = 0;
        if (world->vaisseau->y + world->vaisseau->h > SCREEN_HEIGHT) world->vaisseau->y = SCREEN_HEIGHT - world->vaisseau->h;
    }
    for(int i = 0; i < world->nb_murs; i++){
        if (handle_sprite_collide(world->vaisseau, world->murs[i], world, 0) == 1){
            break;
        }
    }

    if (handle_sprite_collide(world->vaisseau, world->ligneArriver, world, 0) == 1){ // si le vaisseau touche la ligne d'arrivée
        world->gameover = 1;
    }
    world->timer = SDL_GetTicks();
}


int is_game_over(world_t *world){
    return world->gameover;
}


void init_data(world_t * world){
    //on n'est pas à la fin du jeu
    world->gameover = 0;
    world->speed_h = (float)INITIAL_SPEED;
    // Initialisation du vaisseau
    world->vaisseau = init_sprite(world->vaisseau, SCREEN_WIDTH/2 - SHIP_SIZE/2, SCREEN_HEIGHT - SHIP_SIZE, SHIP_SIZE, SHIP_SIZE);
    // world->mur = init_sprite(world->mur, 0, 0, 3*METEORITE_SIZE, 7*METEORITE_SIZE);
    world->ligneArriver = init_sprite(world->ligneArriver, 0, -960 , SCREEN_WIDTH, FINISH_LINE_HEIGHT);
    init_walls(world);
    print_sprite(world->vaisseau);
    world->startTimer = SDL_GetTicks();
    world->timer = SDL_GetTicks();
}


void clean_data(world_t *world){
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
    free(world->vaisseau);
    free(world->ligneArriver);
    free(world->murs);

    printf("clean_data");   
}


int handle_sprite_collide(sprite_t *sp1, sprite_t *sp2, world_t *world, int make_disappear){
    if (sprites_collide(sp1, sp2)){
        world->gameover = 1;
        printf("collision");
        return 1;
    }else{
        return 0;
    }
}


void init_walls(world_t *world){
    world->nb_murs = 6;
    world->murs = malloc(sizeof(sprite_t) * 10);
    world->murs[0] = init_sprite(world->murs[0], 48, 0, 3*METEORITE_SIZE, 6*METEORITE_SIZE);
    world->murs[1] = init_sprite(world->murs[1], 252, 0, 3*METEORITE_SIZE, 6*METEORITE_SIZE);
    world->murs[2] = init_sprite(world->murs[2], 16, -352, 1*METEORITE_SIZE, 5*METEORITE_SIZE);
    world->murs[3] = init_sprite(world->murs[3], 188, -352, 7*METEORITE_SIZE, 5*METEORITE_SIZE);
    world->murs[4] = init_sprite(world->murs[4], 48, -672, 3*METEORITE_SIZE, 6*METEORITE_SIZE);
    world->murs[5] = init_sprite(world->murs[5], 252, -672, 3*METEORITE_SIZE, 6*METEORITE_SIZE);

}

void update_walls(world_t *world){
    for (int i = 0; i < world->nb_murs; i++){
        world->murs[i]->y += world->speed_h;
    }
}