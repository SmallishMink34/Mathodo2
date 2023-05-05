#include "world.h"
#include "../utility/utility.h"

void update_data(world_t *world){
    if (!world->isMenu){
        world->ligneArriver->y += (int)world->speed_h;
        update_walls(world);
        if (isOverScreen(world->vaisseau)){
            if (world->vaisseau->x < 0) world->vaisseau->x = 0;
            if (world->vaisseau->x + world->vaisseau->w > SCREEN_WIDTH) world->vaisseau->x = SCREEN_WIDTH - world->vaisseau->w;
            if (world->vaisseau->y < 0) world->vaisseau->y = 0;
            if (world->vaisseau->y + world->vaisseau->h > SCREEN_HEIGHT) world->vaisseau->y = SCREEN_HEIGHT - world->vaisseau->h;
        }
        for(int i = 0; i < world->nb_murs; i++){
            collide(world->vaisseau, world->murs[i], world, 0);
        }
        collide(world->vaisseau, world->ligneArriver, world, 1);

        allEvents(world);

        world->timer = SDL_GetTicks(); 
    }
}


int is_game_over(world_t *world){
    return world->gameover;
}


void init_data(world_t * world){
    //on n'est pas à la fin du jeu
    world->gameover = 0;
    world->speed_h = (float)INITIAL_SPEED;
    // Initialisation du vaisseau
    world->vaisseau = init_sprite(world->vaisseau, SCREEN_WIDTH/2 - SHIP_SIZE/2, SCREEN_HEIGHT - SHIP_SIZE, SHIP_SIZE, SHIP_SIZE, '0');
    init_walls(world);
    world->ligneArriver = init_sprite(world->ligneArriver, 0, -world->nb_lines_murs*METEORITE_SIZE-30 , SCREEN_WIDTH, FINISH_LINE_HEIGHT, 'z');
    
    world->play = init_btn(0, 0, 100, 100);

    print_sprite(world->vaisseau);
    world->startTimer = SDL_GetTicks();
    world->timer = SDL_GetTicks();
    world->str = malloc(sizeof(char)*100);
    world->angle = 0.0;
    world->isFlipping = 0;
    world->isMenu = true;

    world->mouseX = 0;
    world->mouseY = 0;
}


void clean_data(world_t *world){
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
    free(world->vaisseau);
    free(world->ligneArriver);
    free(world->murs);
    free(world->str);
    printf("clean_data");   
}

void collide(sprite_t *sp1, sprite_t *sp2, world_t *world, int make_disappear){
    if (sprites_collide(sp1, sp2)){
        printf("%s\n", sp2->id);
        if (strcmp(sp2->id, "1") == 0){
            world->gameover = 1;
        }else if(strcmp(sp2->id, "2") == 0){
            if (world->isFlipping == 0){
                world->isFlipping = 1;
            }else if(world->isFlipping == -2){
                world->isFlipping = -1;
            }
        }else if(strcmp(sp2->id, "z") == 0){
            world->gameover = 1;
        }
    }
}

void flipScreen(world_t *world){
    if (world->timer - world->startTimer > 1){
        if (world->isFlipping == 1){
            world->angle += M_PI/20;
            if (world->angle > M_PI){
                world->angle = M_PI;
                world->isFlipping = -2;
            }
        }else if(world->isFlipping == -1){
            world->angle -= M_PI/20;
            if (world->angle < 0){
                world->angle = 0;
                world->isFlipping = 0;
            }
        }
        world->startTimer = SDL_GetTicks();
    }
}

void init_walls(world_t *world){
    world->nb_murs = 0;
    world->murs = malloc(sizeof(sprite_t) * MAX_LENGTH*MAX_LINES);
    // char **murs2 = malloc(sizeof(char*) * MAX_LENGTH*MAX_LINES);
    world->nb_lines_murs = 0;
    int nb_elements = 0;
    char **txt = lirefile("maps/default.txt", &world->nb_lines_murs);

    // for (int i = 0; i < world->nb_lines_murs; i++) {
    //     for (int j = 0; j < MAX_LENGTH; j++) {
    //         murs2[nb_elements] = txt[i][j];
    //         nb_elements++;
    //     }
    // }

    for (int i = 0; i < world->nb_lines_murs; i++) {
        for (int j = 0; j < MAX_LENGTH; j++) {
            if (txt[i][j] != '0'){
                world->murs[world->nb_murs] = init_sprite(world->murs[world->nb_murs], j*METEORITE_SIZE+2, (i*METEORITE_SIZE)-(METEORITE_SIZE*world->nb_lines_murs), METEORITE_SIZE, METEORITE_SIZE, txt[i][j]);
                world->nb_murs++;
            }
        }
    }   
}

void wallChoose(world_t *world, char **murs, int posX, int posY){
    return;
}

void update_walls(world_t *world){
    for (int i = 0; i < world->nb_murs; i++){
        world->murs[i]->y += world->speed_h;
    }
}

void allEvents(world_t *world){
    if (world->isFlipping != 0){
        flipScreen(world);
    }
}
