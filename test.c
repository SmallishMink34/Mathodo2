#include "sdl2-light.h"
#include <stdio.h>
#include <stdlib.h>
#include "library/Display/Display.h"
#include "library/World/world.h"
#include "library/utility/utility.h"
#include "constante.c"

void init(SDL_Window **window, SDL_Renderer ** renderer, ressources_t *textures, world_t * world){
    init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    // Initialisation du ttf
    init_ttf();
    init_ressource(*renderer,textures);
    
}

int test_init_ressource(SDL_Renderer *renderer, ressources_t *textures){
    init_ressource(renderer, textures);
    return 1; // Pas d'erreur
}

int test_apply_background_parralax(SDL_Renderer *renderer, SDL_Texture *texture, world_t *world, int parallax){
    apply_background_parralax(renderer, texture, world, parallax);
    return 1; // Pas d'erreur
}

int test_apply_background(SDL_Renderer *renderer, SDL_Texture *texture, world_t *world){
    apply_background(renderer, texture, world);
    return 1; // Pas d'erreur
}

int test_apply_sprite(SDL_Renderer * renderer, SDL_Texture *texture, sprite_t *sprite, world_t *world){
    apply_sprite(renderer, texture, sprite, world);
    return 1; // Pas d'erreur
}

int test_apply_sprite_fixed(SDL_Renderer * renderer, SDL_Texture *texture, sprite_t *sprite, world_t *world){
    apply_sprite_fixed(renderer, texture, sprite, world);
    return 1; // Pas d'erreur
}

int test_apply_walls(SDL_Renderer *renderer, SDL_Texture *texture, world_t *world,ressources_t *res){
    apply_walls(renderer, texture, world, res);
    return 1; // Pas d'erreur
}

int test_apply_wall(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, world_t *world){
    apply_wall(renderer, texture, x, y, world);
    return 1; // Pas d'erreur
}

int test_refresh_graphics(SDL_Renderer *renderer, world_t *world,ressources_t *textures){
    refresh_graphics(renderer, world, textures);
    return 1; // Pas d'erreur
}

int test_inmenu(SDL_Renderer *renderer, world_t *world, ressources_t *ressources){
    inmenu(renderer, world, ressources);
    return 1; // Pas d'erreur
}

int test_ingame(SDL_Renderer *renderer, world_t *world, ressources_t *ressources){
    ingame(renderer, world, ressources);
    return 1; // Pas d'erreur
}

int test_clean(SDL_Window *window, SDL_Renderer * renderer, ressources_t *textures, world_t * world){
    clean(window, renderer, textures, world);
    return 1; // Pas d'erreur
}

int test_clean_textures(ressources_t *textures){ // Compris dans le test clean
    clean_textures(textures);
    return 1; // Pas d'erreur
}

int test_init_data(world_t * world){
    init_data(world);
    return 1; // Pas d'erreur
}

int test_update_data(world_t * world){
    update_data(world);
    return 1; // Pas d'erreur
}

int test_is_game_over(world_t * world){
    printf("test_is_game_over\n : %d\n", is_game_over(world));
    return 1; // Pas d'erreur
}

int test_outBorder(world_t * world){
    outBorder(world);
    return 1; // Pas d'erreur
}

int test_timer_update(world_t * world){
    timer_update_s(world);
    return 1; // Pas d'erreur
}

int test_clean_data(world_t * world){
    clean_data(world);
    return 1; // Pas d'erreur
}

int test_flipScreen(world_t *world){
    flipScreen(world);
    return 1; // Pas d'erreur
}

int test_collide(sprite_t *sp1, sprite_t *sp2, world_t *world){
    collide(sp1, sp2, world);
    return 1; // Pas d'erreur
}

int test_init_walls(world_t *world){
    init_walls(world);
    return 1; // Pas d'erreur
}

int test_update_walls(world_t *world){
    update_walls(world);
    return 1; // Pas d'erreur
}

int test_remove_wall(world_t *world, int index){
    remove_wall(world, index);
    return 1; // Pas d'erreur
}

int test_allEvents(world_t *world){
    allEvents(world);
    return 1; // Pas d'erreur
}

int test_InitMenu(world_t *world){
    InitMenu(world);
    return 1; // Pas d'erreur
}

int main( int argc, char* args[] ){
    printf("Nombre de test : 23\n");
    SDL_Event event;
    world_t world;
    ressources_t textures;
    SDL_Renderer *renderer;
    SDL_Window *window;

    Uint32 ticks = SDL_GetTicks();
    Uint32 frameTime = 0;

    int compteur_test = 0;

    //initialisation du jeu
    init(&window,&renderer,&textures,&world);
    
    /*--------------------------Display--------------------------*/
    compteur_test += test_init_ressource(renderer, &textures);
    compteur_test += test_apply_background_parralax(renderer, textures.background, &world, 1);
    compteur_test += test_apply_background(renderer, textures.background, &world);
    compteur_test += test_apply_sprite(renderer, textures.ship, world.vaisseau, &world);
    compteur_test += test_apply_sprite_fixed(renderer, textures.ship, world.vaisseau, &world);
    compteur_test += test_apply_walls(renderer, textures.ship, &world, &textures);
    compteur_test += test_apply_wall(renderer, textures.ship, 0, 0, &world);
    compteur_test += test_refresh_graphics(renderer, &world, &textures);
    compteur_test += test_inmenu(renderer, &world, &textures);
    compteur_test += test_ingame(renderer, &world, &textures);

    /*--------------------------World--------------------------*/
    compteur_test += test_init_data(&world);
    compteur_test += test_update_data(&world);
    compteur_test += test_is_game_over(&world);
    compteur_test += test_outBorder(&world);
    compteur_test += test_timer_update(&world);
    compteur_test += test_flipScreen(&world);
    compteur_test += test_collide(world.vaisseau, world.vaisseau, &world);
    compteur_test += test_init_walls(&world);
    compteur_test += test_update_walls(&world);
    compteur_test += test_remove_wall(&world, 0);
    compteur_test += test_allEvents(&world);
    compteur_test += test_InitMenu(&world);
    /*--------------------------Sprite--------------------------*/

    /*--------------------------Utility--------------------------*/

    /*--------------------------menu--------------------------*/
    //mise à jour des données liée à la physique du monde
    update_data(&world);
    
    //rafraichissement de l'écran
    refresh_graphics(renderer,&world,&textures);
    
    if (frameTime < 16) {
        SDL_Delay(16 - frameTime); // 16 ms = 60 fps
    }
    
    
    compteur_test += test_clean(window, renderer, &textures, &world);
    
    printf("\n");
    printf("Nombre de test effectue et valide: %d\n", compteur_test);

}