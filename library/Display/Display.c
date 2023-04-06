#include "Display.h"
#include "../../constante.c"
#include "../utility/utility.h"

void init_ressource(SDL_Renderer *renderer, ressources_t *textures){
    textures->background = load_image( "ressources/space-background.bmp",renderer);
    textures->ship = load_image( "ressources/spaceship.bmp",renderer);
    textures->meteorite = load_image( "ressources/meteorite.bmp",renderer);
    textures->finishLine = load_image( "ressources/finish_line.bmp",renderer);
    textures->font = load_font("ressources/font/arial.ttf", 14);
    textures->color = (SDL_Color){255, 255, 255, 255};
}

void apply_background(SDL_Renderer *renderer, SDL_Texture *texture){
    if(texture != NULL){
      apply_texture(texture, renderer, 0, 0);
    }
}

void apply_sprite(SDL_Renderer * renderer, SDL_Texture *texture, sprite_t *sprite){
    if(texture != NULL){
        SDL_Rect rect;
        rect.x = sprite->x;
        rect.y = sprite->y;
        rect.w = sprite->w;
        rect.h = sprite->h;
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }
}

void apply_wall(SDL_Renderer * renderer, SDL_Texture *texture, int x, int y){
    if(texture != NULL){
        SDL_Rect rect;
        rect.x = x;
        rect.y = y;
        rect.w = METEORITE_SIZE;
        rect.h = METEORITE_SIZE;
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }
}

void apply_walls(SDL_Renderer * renderer, SDL_Texture *texture, world_t *world){
    for (int i = 0; i < world->nb_murs; i++){
        for (int i3 = 0; i3 < world->murs[i]->w/METEORITE_SIZE ; i3++){
            for (int i2 = 0; i2 < world->murs[i]->h/METEORITE_SIZE ; i2++){
                apply_wall(renderer, texture, world->murs[i]->x+i3*METEORITE_SIZE, world->murs[i]->y+i2*METEORITE_SIZE);
            }
        }
    }
}


void refresh_graphics(SDL_Renderer *renderer, world_t *world,ressources_t *textures){
    char * str = malloc(sizeof(char)*100);
    //on vide le renderer
    clear_renderer(renderer);
    
    //application des textures dans le renderer
    apply_background(renderer, textures->background);

    apply_sprite(renderer, textures->ship, world->vaisseau);

    apply_sprite(renderer, textures->finishLine, world->ligneArriver);

    apply_walls(renderer, textures->meteorite, world);
    apply_text(renderer, 10, 10, 100, 33, strcats(str, 3, "temps: ",int_to_str((int)world->timer/1000), "s"), textures->font, textures->color); 
    
    // on met à jour l'écran
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