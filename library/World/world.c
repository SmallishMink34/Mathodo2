#include "world.h"
#include "../utility/utility.h"

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
        }else if (handle_sprite_collide(world->vaisseau, world->murs[i], world, 0) == 2){
            printf("CHangement de sens\n");
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
    world->vaisseau = init_sprite(world->vaisseau, SCREEN_WIDTH/2 - SHIP_SIZE/2, SCREEN_HEIGHT - SHIP_SIZE, SHIP_SIZE, SHIP_SIZE, 0);
    init_walls(world);
    world->ligneArriver = init_sprite(world->ligneArriver, 0, -world->nb_lines_murs*METEORITE_SIZE-30 , SCREEN_WIDTH, FINISH_LINE_HEIGHT, 0);
    
    print_sprite(world->vaisseau);
    world->startTimer = SDL_GetTicks();
    world->timer = SDL_GetTicks();
    world->str = malloc(sizeof(char)*100);
}


void clean_data(world_t *world){
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
    free(world->vaisseau);
    free(world->ligneArriver);
    free(world->murs);
    free(world->str);
    
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
    world->nb_murs = 0;
    world->murs = malloc(sizeof(sprite_t) * MAX_LENGTH*MAX_LINES);
    world->nb_lines_murs = 0;
    char **txt = lirefile("maps/default.txt", &world->nb_lines_murs);

    for (int i = 0; i < world->nb_lines_murs; i++) {
        for (int j = 0; j < MAX_LENGTH; j++) {
            switch (txt[i][j])
            {
            case '1':
                world->murs[world->nb_murs] = init_sprite(world->murs[world->nb_murs], j*METEORITE_SIZE, (i*METEORITE_SIZE)-(METEORITE_SIZE*world->nb_lines_murs), METEORITE_SIZE, METEORITE_SIZE, 1);
                world->nb_murs++;
                break;
            case '2':
                world->murs[world->nb_murs] = init_sprite(world->murs[world->nb_murs], j*METEORITE_SIZE, (i*METEORITE_SIZE)-(METEORITE_SIZE*world->nb_lines_murs), METEORITE_SIZE, METEORITE_SIZE, 2);
                world->nb_murs++;
                break;

            default:
                break;
            }
            
        }
    }
    printf("aaaa");

}

void update_walls(world_t *world){
    for (int i = 0; i < world->nb_murs; i++){
        world->murs[i]->y += world->speed_h;
    }
}
