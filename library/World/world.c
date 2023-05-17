#include "world.h"

#include "../utility/utility.h"

void update_data(world_t *world){
    if (world->gamestate==0){
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
        world->timer = SDL_GetTicks() - world->startTimer;
        
    }else if(world->gamestate == 1){
        world->startTimer = SDL_GetTicks();
    }
}

void init_data(world_t * world){
    //on n'est pas à la fin du jeu
    world->gameover = 0;
    world->speed_h = (float)INITIAL_SPEED;
    init_walls(world);
    world->ligneArriver = init_sprite(world->ligneArriver, 0, -world->nb_lines_murs*METEORITE_SIZE-30 , SCREEN_WIDTH, FINISH_LINE_HEIGHT, 'z', 0);

    world->money = 2000; // Initialisation de l'argent ici car necessaire dans init_menu

    init_menu(world);
    
    init_shop(world);
    
    // Initialisation du vaisseau
    world->vaisseau = init_sprite(world->vaisseau, SCREEN_WIDTH/2 - SHIP_SIZE/2, SCREEN_HEIGHT - SHIP_SIZE-15, SHIP_SIZE, SHIP_SIZE, '0', 0);
    
    world->ligneArriver = init_sprite(world->ligneArriver, 0, -world->nb_lines_murs*METEORITE_REAL_SIZE-30 , SCREEN_WIDTH, FINISH_LINE_HEIGHT, 'z', 0);
    world->BarreProgression = init_sprite(world->BarreProgression, 10, SCREEN_HEIGHT - 500, 50, 400, 'y', 0);
    world->vaisseauMini = init_sprite(world->vaisseauMini, 10, SCREEN_HEIGHT - 130, 20, 20, 'x', 0);
    world->soleilBarre = init_sprite(world->soleilBarre, 0, SCREEN_HEIGHT - 510, 40, 40, 'x', 0);
    world->soleil = init_sprite(world->soleil, SCREEN_WIDTH/2-1800/2, -world->nb_lines_murs*METEORITE_REAL_SIZE-1400, 1800, 1800, 'z', 0);
    world->air = init_sprite(world->air, -2000, -2000, 0, 0, 'x', 0);
    world->coins = init_sprite(world->coins, SCREEN_WIDTH-40, 10, 30, 30, 'x', 0);
    world->exit_shop = init_sprite(world->exit_shop, 670, 500, 100, 100, 'x', 0);
    world->pgb = init_progressbarre(SCREEN_WIDTH-200, SCREEN_HEIGHT-30, 190, 20, 100/(INITIAL_SPEED+6)*world->speed_h);

    world->vaisseauMini->y = SCREEN_HEIGHT - (110);
    world->vaisseauMini->dy = SCREEN_HEIGHT - (110);
    world->timer = SDL_GetTicks();
    world->temps_str = malloc(sizeof(char)*100); // Allocation de la mémoire pour le string temps
    world->coins_str = malloc(sizeof(char)*100); // Allocation de la mémoire pour le string coins
    world->coins_str[0] = '\0';
    world->coins_str = strcats(world->coins_str, 1, "0");
    world->actualship = 0;

    world->musique = init_music("ressources/sons/music.mp3");
    play_music(world->musique, -1);

    world->angle = 0.0;
    world->isFlipping = 0;
    world->gamestate = 1;

    world->mouseX = 0;
    world->mouseY = 0;
    
    world->parallax = 0;
    world->invicibility = false;


    print_sprite(world->vaisseau);
}

void restart(world_t *world){
  
    world->vaisseau->x = SCREEN_WIDTH/2 - SHIP_SIZE/2;

    world->vaisseauMini->y = SCREEN_HEIGHT - (110);
    world->vaisseauMini->dy = SCREEN_HEIGHT - (110);

    world->ligneArriver->y = -world->nb_lines_murs*METEORITE_SIZE-30;
    world->soleil->y = -world->nb_lines_murs*METEORITE_SIZE-1400;
    world->nb_murs = 0;
    world->speed_h = (float)INITIAL_SPEED;
    free(world->murs);
    init_walls(world);
    world->angle = 0.0;

    modify_str(world->coin_menu_str, int_to_str(world->money));
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

void init_menu(world_t * world){
    world->play = init_btn(203,129, 218, 97);
    world->exit = init_btn(202,294, 218, 97);
    world->magasin = init_btn(436, 217, 218, 97);
    world->sound = init_btn(0, 0, 100, 100);

    world->coin_menu_str = malloc(sizeof(char)*100); // Allocation de la mémoire pour le string coins
    world->coin_menu_str[0] = '\0';
    world->coin_menu_str = strcats(world->coin_menu_str, 1, int_to_str(world->money));
}

void init_shop(world_t * world){
    world->ships = malloc(sizeof(btn_t*)*4);
    world->ships[0] = init_btn(74,145, 191, 139);
    world->ships[1] = init_btn(287,143, 191, 139);
    world->ships[2] = init_btn(491,138, 191, 139);
    world->ships[3] = init_btn(290,308, 191, 139);

    world->exit_shp = init_btn(670,500,100,100);

    world->vaisseau1 = init_sprite(world->vaisseau1, 140, 170, 60, 60, 0, 'z');
    world->vaisseau2 = init_sprite(world->vaisseau2, 350, 170, 60, 60, 0, 'z');
    world->vaisseau3 = init_sprite(world->vaisseau3, 560, 170, 60, 60, 0, 'z');
    world->vaisseau4 = init_sprite(world->vaisseau4, 360, 340, 60, 60, 0, 'z');


    world->Spr_ship = malloc(sizeof(sprite_t*)*4);
    world->Spr_ship[0] = init_sprite(world->Spr_ship[0], 74,145, 191, 139, 'x', 0);
    world->Spr_ship[1] = init_sprite(world->Spr_ship[1], 287,143, 191, 139, 'x', 0);
    world->Spr_ship[2] = init_sprite(world->Spr_ship[2], 491,138, 191, 139, 'x', 0);
    world->Spr_ship[3] = init_sprite(world->Spr_ship[3], 290,308, 191, 139, 'x', 0);
    
    world->shopPrice = malloc(sizeof(int)*4);
    world->shopPrice[0] = 0;
    world->shopPrice[1] = 500;
    world->shopPrice[2] = 1000;
    world->shopPrice[3] = 2000;

    world->isBought = malloc(sizeof(bool)*4);
    world->isBought[0] = true;
    world->isBought[1] = false;
    world->isBought[2] = false;
    world->isBought[3] = false;

    world->isSelected = malloc(sizeof(bool)*4);
    world->isSelected[0] = true;
    world->isSelected[1] = false;
    world->isSelected[2] = false;
    world->isSelected[3] = false;
}

void collide(sprite_t *sp1, sprite_t *sp2, world_t *world){
    if (sprites_collide(sp1, sp2)){
        if (strcmp(sp2->id, "1") == 0){
            world->gamestate = 1;
            restart(world);
        }else if(strcmp(sp2->id, "2") == 0){
            switch (rand() % 3){ // random entre 1 et 2
                case 1:
                    if (world->isFlipping == 0){
                        world->isFlipping = 1;
                    }else if(world->isFlipping == -2){
                        world->isFlipping = -1;
                    }
                    break;
                case 2:
                    world->money += 10;
                    break;
            }
            remove_wall(world, sp2->indice);
        }else if(strcmp(sp2->id, "z") == 0){
            world->gamestate = 1;
            restart(world);
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
    free(world->ships);
    free(world->Spr_ship);
    free(world->shopPrice);
    free(world->coin_menu_str);
    free(world->exit_shp);  
    Mix_FreeMusic(world->musique);
    Mix_CloseAudio();

    printf("clean_data");   
}

progressBarre_t *init_progressbarre(int x, int y, int w, int h, int pourcent){
    progressBarre_t *pgb;
    pgb = malloc(sizeof(progressBarre_t));
    pgb->Barre = malloc(sizeof(SDL_Rect));
    pgb->Contours = malloc(sizeof(SDL_Rect));
    pgb->Base = malloc(sizeof(SDL_Rect));
    pgb->Barre->x = x;
    pgb->Barre->y = y;
    pgb->Barre->w = (int)(w*((float)pourcent/100.0));
    pgb->Barre->h = h;
    pgb->Contours->x = x-6;
    pgb->Contours->y = y-6;
    pgb->Contours->w = w+12;
    pgb->Contours->h = h+12;
    pgb->Base->x = x;
    pgb->Base->y = y;
    pgb->Base->w = w;
    pgb->Base->h = h;
    pgb->pourcent = pourcent;
    return pgb;
}

void updateProgressBarre (progressBarre_t *pgb, int pourcent){
    pgb->pourcent = pourcent;
    
    pgb->Barre->w = (int)(pgb->Base->w*((float)pourcent/100.0));
}