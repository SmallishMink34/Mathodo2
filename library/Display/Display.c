#include "Display.h"
#include "../../constante.c"
#include "../utility/utility.h"
#include <math.h>

void init_ressource(SDL_Renderer *renderer, ressources_t *textures){
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

    init_ressource_element(renderer, textures);
}

void init_ressource_element(SDL_Renderer *renderer, ressources_t *textures){
    textures->meteorite = load_image( "ressources/meteorite.bmp",renderer);
    textures->e_rotate = load_image("ressources/Elements/reverse.bmp", renderer);
}

void apply_background(SDL_Renderer *renderer, SDL_Texture *texture, world_t *world, int parallax){
    if(texture != NULL){
        apply_texture(texture, renderer, 0, -1800+world->parallax/parallax, world->angle*180/M_PI);

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
                }
            }
        }
    }
}


void refresh_graphics(SDL_Renderer *renderer, world_t *world,ressources_t *textures){
    //on vide le renderer
    clear_renderer(renderer);
    
    //application des textures dans le renderer
    apply_background(renderer, textures->background, world, 7);
    apply_background(renderer, textures->background2, world, 3);
    apply_background(renderer, textures->background3, world, 9);

    if (!world->isMenu){
        apply_sprite(renderer, textures->ship, world->vaisseau, world);
        apply_sprite(renderer, textures->finishLine, world->ligneArriver, world);
        apply_walls(renderer, textures->meteorite, world, textures);
        apply_sprite(renderer, textures->soleil, world->soleil, world);
        if (timer_update_s(world) != 0){
            world->str[0] = '\0';
            world->str = strcats(world->str, 3, "temps: ",int_to_str((int)world->timer/1000), "s");
        }
        apply_text(renderer, 10, 10, 100, 33, world->str, textures->font, textures->color); 
        apply_sprite(renderer, textures->BarreProgression, world->BarreProgression, world);
        apply_sprite(renderer, textures->vaisseauMini, world->vaisseauMini, world);
        apply_sprite(renderer, textures->soleilBarre, world->soleilBarre, world);
        
    }else{
        apply_text(renderer, 10, 10, 100, 33, "Menu", textures->font, textures->color);
        printf("aaa");
    }
    
    
    update_screen(renderer);
    
}

int timer_update_s(world_t *world){
    if (world->timer%1000 <=  110|| world->timer%1000 >= 985){
        return world->timer%1000;
    }
    return 0;
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