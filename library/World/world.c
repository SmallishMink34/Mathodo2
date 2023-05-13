#include "world.h"
#include "../utility/utility.h"

void update_data(world_t *world){
    if (world->isMenu==0){
        world->ligneArriver->y += (int)world->speed_h;
        world->soleil->y += (int)world->speed_h;

        world->vaisseauMini->dy -= world->speed_h/(MAX_LINES*METEORITE_REAL_SIZE+700)*400;
        world->vaisseauMini->y = (int)world->vaisseauMini->dy;

        outBorder(world);

        world->parallax += (int)world->speed_h;

        update_walls(world);
        world->money2 = world->money;
        if (!world->invicibility){
            for(int i = 0; i < world->nb_murs; i++){
                collide(world->vaisseau, world->murs[i], world);
            }
        }
        collide(world->vaisseau, world->ligneArriver, world);
        if (timer_update_s(world) != 0){
            world->temps_str[0] = '\0';
            world->temps_str = strcats(world->temps_str, 3, "temps: ",int_to_str((int)world->timer/1000), "s");
        }
        allEvents(world);
        world->timer = SDL_GetTicks() - world->startTimer;; 
    }else if(world->isMenu == 1){
        world->startTimer = SDL_GetTicks();
    }
}

void init_data(world_t * world){
    //on n'est pas à la fin du jeu
    world->gameover = 0;
    world->speed_h = (float)INITIAL_SPEED;
    init_walls(world);
    world->ligneArriver = init_sprite(world->ligneArriver, 0, -world->nb_lines_murs*METEORITE_SIZE-30 , SCREEN_WIDTH, FINISH_LINE_HEIGHT, 'z', 0);
    InitMenu(world);
    print_sprite(world->vaisseau);
    // Initialisation du vaisseau
    world->vaisseau = init_sprite(world->vaisseau, SCREEN_WIDTH/2 - SHIP_SIZE/2, SCREEN_HEIGHT - SHIP_SIZE-15, SHIP_SIZE, SHIP_SIZE, '0', 0);
    world->ligneArriver = init_sprite(world->ligneArriver, 0, -world->nb_lines_murs*METEORITE_REAL_SIZE-30 , SCREEN_WIDTH, FINISH_LINE_HEIGHT, 'z', 0);
    world->BarreProgression = init_sprite(world->BarreProgression, 10, SCREEN_HEIGHT - 500, 50, 400, 'y', 0);
    world->vaisseauMini = init_sprite(world->vaisseauMini, 10, SCREEN_HEIGHT - 130, 20, 20, 'x', 0);
    world->soleilBarre = init_sprite(world->soleilBarre, 0, SCREEN_HEIGHT - 510, 40, 40, 'x', 0);
    world->soleil = init_sprite(world->soleil, SCREEN_WIDTH/2-1800/2, -world->nb_lines_murs*METEORITE_REAL_SIZE-1400, 1800, 1800, 'z', 0);
    world->air = init_sprite(world->air, -2000, -2000, 0, 0, 'x', 0);
    world->coins = init_sprite(world->coins, SCREEN_WIDTH-40, 10, 30, 30, 'x', 0);

    world->vaisseauMini->y = SCREEN_HEIGHT - (110);
    world->vaisseauMini->dy = SCREEN_HEIGHT - (110);
    world->timer = SDL_GetTicks();
    world->temps_str = malloc(sizeof(char)*100); // Allocation de la mémoire pour le string temps


    world->coins_str = malloc(sizeof(char)*100); // Allocation de la mémoire pour le string coins
    world->coins_str[0] = '\0';
    world->coins_str = strcats(world->coins_str, 1, "0");

    world->angle = 0.0;
    world->isFlipping = 0;
    world->isMenu = 1;

    world->mouseX = 0;
    world->mouseY = 0;
    world->money = 0;
    world->parallax = 0;
    world->invicibility = false;
}



void outBorder(world_t *world){
    if (isOverScreen(world->vaisseau)){
        if (world->vaisseau->x < 0) world->vaisseau->x = 0;
        if (world->vaisseau->x + world->vaisseau->w > SCREEN_WIDTH) world->vaisseau->x = SCREEN_WIDTH - world->vaisseau->w;
        if (world->vaisseau->y < 0) world->vaisseau->y = 0;
        if (world->vaisseau->y + world->vaisseau->h > SCREEN_HEIGHT) world->vaisseau->y = SCREEN_HEIGHT - world->vaisseau->h;
    }
}

int is_game_over(world_t *world){
    return world->gameover;
}

int timer_update_s(world_t *world){
    if ((world->timer)%1000 <=  110|| (world->timer)%1000 >= 985){
        return (world->timer)%1000;
    }
    return 0;
}

void InitMenu(world_t * world){
    world->play = init_btn(203,129, 218, 97);
    world->exit = init_btn(202,294, 218, 97);
    world->magasin = init_btn(436, 217, 218, 97);
    world->sound = init_btn(0, 0, 100, 100);
}


void collide(sprite_t *sp1, sprite_t *sp2, world_t *world){
    if (sprites_collide(sp1, sp2)){
        printf("aaa: %s\n", sp2->id);
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
        }else if(strcmp(sp2->id, "3") == 0){
            world->money += 1;
            remove_wall(world, sp2->indice);
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

    for (int i = 0; i < world->nb_lines_murs; i++) {
        for (int j = 0; j < MAX_LENGTH; j++) {
            if (txt[i][j] != '0'){
                world->murs[world->nb_murs] = init_sprite(world->murs[world->nb_murs], j*METEORITE_SIZE+2, (i*METEORITE_SIZE)-(METEORITE_SIZE*world->nb_lines_murs), METEORITE_SIZE, METEORITE_SIZE, txt[i][j], world->nb_murs);
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

void remove_wall(world_t *world, int index){
    free(world->murs[index]);
    world->murs[index] = world->air;
    world->murs[index]->indice = index;
}

void allEvents(world_t *world){
    if (world->money2 != world->money){
        world->coins_str[0] = '\0'; // On vide le string
        world->coins_str = strcat(world->coins_str, int_to_str(world->money));
    }

    if (world->isFlipping != 0){
        flipScreen(world);
    }
}

void clean_data(world_t *world){
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
    free(world->vaisseau);
    free(world->ligneArriver);
    free(world->murs);
    free(world->temps_str);
    free(world->vaisseauMini);
    free(world->soleilBarre);
    free(world->soleil);
    free(world->BarreProgression);
    free(world->coins);
    free(world->coins_str);
    free(world->air);
    free(world->play);
    free(world->exit);
    free(world->magasin);
    free(world->sound);

    printf("clean_data");   
}