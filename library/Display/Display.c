#include "Display.h"
#include "../../constante.c"

void init_textures(SDL_Renderer *renderer, textures_t *textures){
    textures->background = load_image( "ressources/space-background.bmp",renderer);
    textures->ship = load_image( "ressources/spaceship.bmp",renderer);
    textures->meteorite = load_image( "ressources/meteorite.bmp",renderer);
    textures->finishLine = load_image( "ressources/finish_line.bmp",renderer);
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


void refresh_graphics(SDL_Renderer *renderer, world_t *world,textures_t *textures){

    //on vide le renderer
    clear_renderer(renderer);
    
    //application des textures dans le renderer
    apply_background(renderer, textures->background);
    /* A COMPLETER */
    apply_sprite(renderer, textures->ship, world->vaisseau);

    apply_sprite(renderer, textures->finishLine, world->ligneArriver);

    for (int i = 0; i < world->mur->w/METEORITE_SIZE ; i++){
        for (int i2 = 0; i2 < world->mur->h/METEORITE_SIZE ; i2++){
            apply_wall(renderer, textures->meteorite, world->mur->x+i*METEORITE_SIZE, world->mur->y+i2*METEORITE_SIZE);
        }
    }
    

    // on met à jour l'écran
    update_screen(renderer);
}


void clean(SDL_Window *window, SDL_Renderer * renderer, textures_t *textures, world_t * world){
    clean_data(world);
    clean_textures(textures);
    clean_sdl(renderer,window);
}

void clean_textures(textures_t *textures){
    SDL_DestroyTexture(textures->background);
    SDL_DestroyTexture(textures->ship);
    SDL_DestroyTexture(textures->meteorite);
    SDL_DestroyTexture(textures->finishLine);
}