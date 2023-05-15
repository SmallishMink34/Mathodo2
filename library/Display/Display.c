#include "Display.h"
#include "../../constante.c"
#include "../utility/utility.h"
#include <math.h>

void init_ressource(SDL_Renderer *renderer, ressources_t *textures){
    textures->bmenu = load_image( "ressources/image-menu.bmp",renderer);
    textures->bshop = load_image( "ressources/Elements/shop.png",renderer);
    textures->ship = load_image( "ressources/spaceship.bmp",renderer);
    textures->background = load_image( "ressources/Elements/backgrounds/1.png",renderer);
    textures->background2 = load_image( "ressources/Elements/backgrounds/3.png",renderer);
    textures->background3 = load_image( "ressources/Elements/backgrounds/2.png",renderer);
    textures->ship = load_image( "ressources/Elements/Ship_1.png",renderer);
    
    textures->finishLine = load_image( "ressources/finish_line.bmp",renderer);
    textures->font = load_font("ressources/font/arial.ttf", 14);
    textures->color = (SDL_Color){255, 255, 255, 255};

    textures->BarreProgression = load_image( "ressources/Elements/BarreProgression.png",renderer);
    textures->vaisseauMini = textures->ship;

    textures->soleilBarre = load_image( "ressources/Elements/soleil.png",renderer);
    textures->soleil = load_image( "ressources/Elements/soleil.png",renderer);

    textures->buy = load_image( "ressources/Elements/shop/buy.png",renderer);
    textures->nomoney = load_image( "ressources/Elements/shop/nomoney.png",renderer);
    textures->sell = load_image( "ressources/Elements/shop/sell.png",renderer);

    textures->nb_init = 9;
    init_ressource_element(renderer, textures);
    
}

void init_ressource_element(SDL_Renderer *renderer, ressources_t *textures){
    textures->meteorite = load_image( "ressources/meteorite.bmp",renderer);
    textures->e_rotate = load_image("ressources/Elements/reverse.bmp", renderer);
    textures->coins = load_image("ressources/Elements/coin.png", renderer);
    textures->nb_init += 3;
}

void apply_background_parralax(SDL_Renderer *renderer, SDL_Texture *texture, world_t *world, int parallax){
    if(texture != NULL){
        apply_texture(texture, renderer, 0, (int)(-1800+(world->parallax/parallax)), world->angle*180/M_PI);
    }
}

void apply_background(SDL_Renderer *renderer, SDL_Texture *texture, world_t *world){
    if(texture != NULL){
        apply_texture(texture, renderer, 0, 0, world->angle*180/M_PI);
    }
}

void apply_sprite(SDL_Renderer * renderer, SDL_Texture *texture, sprite_t *sprite, world_t *world){
    if(texture != NULL){
        SDL_Rect rect;
        rect.x = SCREEN_WIDTH/2 + (sprite->x - SCREEN_WIDTH/2) * cos(world->angle) - (sprite->y - SCREEN_HEIGHT/2) * sin(world->angle);
        rect.y = SCREEN_HEIGHT/2 + (sprite->x - SCREEN_WIDTH/2) * sin(world->angle) + (sprite->y - SCREEN_HEIGHT/2) * cos(world->angle);

        rect.w = sprite->w;
        rect.h = sprite->h;

        SDL_RenderCopyEx(renderer, texture, NULL, &rect, world->angle*180/M_PI, NULL, SDL_FLIP_NONE);
    }
}

void apply_sprite_fixed(SDL_Renderer * renderer, SDL_Texture *texture, sprite_t *sprite, world_t *world){
    if(texture != NULL){
        SDL_Rect rect;
        rect.x = sprite->x;
        rect.y = sprite->y;

        rect.w = sprite->w;
        rect.h = sprite->h;

        SDL_RenderCopyEx(renderer, texture, NULL, &rect, world->angle*180/M_PI, NULL, SDL_FLIP_NONE);
    }
}

void apply_wall(SDL_Renderer * renderer, SDL_Texture *texture, int x, int y,world_t *world){
    if(texture != NULL){
        SDL_Rect rect;
        rect.x = SCREEN_WIDTH/2 + (x - SCREEN_WIDTH/2) * cos(world->angle) - (y - SCREEN_HEIGHT/2) * sin(world->angle);
        rect.y = SCREEN_HEIGHT/2 + (x - SCREEN_WIDTH/2) * sin(world->angle) + (y - SCREEN_HEIGHT/2) * cos(world->angle);
        rect.w = METEORITE_SIZE;
        rect.h = METEORITE_SIZE;
        if (SDL_RenderCopyEx(renderer, texture, NULL, &rect, world->angle*180/M_PI, NULL, SDL_FLIP_NONE) != 0){
            printf("ok\n");
        }
    }
}

void apply_walls(SDL_Renderer * renderer, SDL_Texture *texture, world_t *world, ressources_t *res){
    for (int i = 0; i < world->nb_murs; i++){
        for (int i3 = 0; i3 < world->murs[i]->w/METEORITE_SIZE ; i3++){
            for (int i2 = 0; i2 < world->murs[i]->h/METEORITE_SIZE ; i2++){
                if (strcmp(world->murs[i]->id, "1") == 0){
                    apply_wall(renderer, res->meteorite, world->murs[i]->x+i3*METEORITE_SIZE, world->murs[i]->y+i2*METEORITE_SIZE, world);
                }else if(strcmp(world->murs[i]->id, "2") == 0){
                    apply_wall(renderer, res->e_rotate, world->murs[i]->x+i3*METEORITE_SIZE, world->murs[i]->y+i2*METEORITE_SIZE, world);
                }else if(strcmp(world->murs[i]->id, "3") == 0){
                    apply_wall(renderer, res->coins, world->murs[i]->x+i3*METEORITE_SIZE, world->murs[i]->y+i2*METEORITE_SIZE, world);
                }
            }
        }
    }
}

void refresh_graphics(SDL_Renderer *renderer, world_t *world,ressources_t *textures){
    //on vide le renderer
    clear_renderer(renderer);
    if (world->gamestate == 0){
        ingame(renderer,world,textures);
    }else if(world ->gamestate==1){
        inmenu(renderer,world,textures);
    }else if(world ->gamestate==2){
        inshop(renderer,world,textures);
    }
    
    update_screen(renderer);
    
}
void inmenu(SDL_Renderer *renderer, world_t *world,ressources_t *textures){
    apply_background(renderer, textures->bmenu, world);
    printf("%d\n", number_of_numbers(world->money));
    apply_text(renderer, (SCREEN_WIDTH-90)-(25*number_of_numbers(world->money)), 20, 25*number_of_numbers(world->money), 50, world->coin_menu_str, textures->font, textures->color);
}

void inshop(SDL_Renderer *renderer, world_t *world, ressources_t *textures){
    apply_background(renderer, textures->bshop, world);
    
    apply_text(renderer, 150, 150, 50, 25, "200$", textures->font, textures->color);
    apply_text(renderer, 360, 145, 50, 25, "500$", textures->font, textures->color);
    apply_text(renderer, 560, 140, 50, 25, "1000$", textures->font, textures->color);
    apply_text(renderer, 370, 315, 50, 25, "2000$", textures->font, textures->color);
    
    for (int i = 0; i<4; i++){
        if (world->shopPrice[i] <= world->money){
            apply_sprite_fixed(renderer, textures->buy, world->Spr_ship[i], world);
        }else{
            apply_sprite_fixed(renderer, textures->nomoney, world->Spr_ship[i], world);
        }
    }

    apply_text(renderer, (SCREEN_WIDTH-90)-(25*number_of_numbers(world->money)), 20, 25*number_of_numbers(world->money), 50, world->coin_menu_str, textures->font, textures->color);

}

void ingame(SDL_Renderer *renderer, world_t *world,ressources_t *textures){
    //application des textures dans le renderer

    // Backgrounds 
    apply_background_parralax(renderer, textures->background, world, 7);
    apply_background_parralax(renderer, textures->background2, world, 3);
    apply_background_parralax(renderer, textures->background3, world, 9);

    apply_sprite(renderer, textures->ship, world->vaisseau, world);
    apply_sprite(renderer, textures->finishLine, world->ligneArriver, world);
    apply_walls(renderer, textures->meteorite, world, textures);
    apply_sprite(renderer, textures->soleil, world->soleil, world);
    apply_text(renderer, 10, 10, 100, 33, world->temps_str, textures->font, textures->color); // Temps de jeu
    apply_text(renderer, SCREEN_WIDTH-(60+10*number_of_numbers(world->money)), 10, 15*number_of_numbers(world->money), 30, world->coins_str, textures->font, textures->color);
    
    // HUD
    apply_sprite_fixed(renderer, textures->BarreProgression, world->BarreProgression, world);
    apply_sprite_fixed(renderer, textures->vaisseauMini, world->vaisseauMini, world);
    apply_sprite_fixed(renderer, textures->soleilBarre, world->soleilBarre, world);
    apply_sprite_fixed(renderer, textures->coins, world->coins, world);
    
    // Update de l'écran
    update_screen(renderer);
    
}

void clean(SDL_Window *window, SDL_Renderer * renderer, ressources_t *textures, world_t * world){
    clean_data(world);
    clean_textures(textures);
    clean_sdl(renderer,window);
}

void clean_textures(ressources_t *textures){
    SDL_DestroyTexture(textures->background);
    SDL_DestroyTexture(textures->ship);
    SDL_DestroyTexture(textures->meteorite);
    SDL_DestroyTexture(textures->finishLine);
    clean_font(textures->font);
}