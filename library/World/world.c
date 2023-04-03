#include "world.h"



void update_data(world_t *world){
    world->ligneArriver->y += world->speed_h;
    world->mur->y += world->speed_h;

    if (isOverScreen(world->vaisseau)){
        if (world->vaisseau->x < 0) world->vaisseau->x = 0;
        if (world->vaisseau->x + world->vaisseau->w > SCREEN_WIDTH) world->vaisseau->x = SCREEN_WIDTH - world->vaisseau->w;
        if (world->vaisseau->y < 0) world->vaisseau->y = 0;
        if (world->vaisseau->y + world->vaisseau->h > SCREEN_HEIGHT) world->vaisseau->y = SCREEN_HEIGHT - world->vaisseau->h;
    }
    handle_sprite_collide(world->vaisseau, world->mur, world, 0);
}



int is_game_over(world_t *world){
    return world->gameover;
}


void init_data(world_t * world){
    
    //on n'est pas à la fin du jeu
    world->gameover = 0;
    world->speed_h = INITIAL_SPEED;

    // Initialisation du vaisseau
    world->vaisseau = init_sprite(world->vaisseau, SCREEN_WIDTH/2 - SHIP_SIZE/2, SCREEN_HEIGHT - SHIP_SIZE, SHIP_SIZE, SHIP_SIZE);
    world->mur = init_sprite(world->mur, 0, 0, 3*METEORITE_SIZE, 7*METEORITE_SIZE);
    world->ligneArriver = init_sprite(world->ligneArriver, 0, -40, SCREEN_WIDTH, FINISH_LINE_HEIGHT);

    print_sprite(world->vaisseau);
}




void clean_data(world_t *world){
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
    free(world->vaisseau);
    free(world->mur);
    free(world->ligneArriver);
    printf("clean_data");   
}


void handle_sprite_collide(sprite_t *sp1, sprite_t *sp2, world_t *world, int make_disappear){
    if (sprites_collide(sp1, sp2)){
        world->speed_h = 0;
        
    }else{
        world->speed_h = INITIAL_SPEED;
    }
}
