/**
 * \file main.c
 * \brief Programme principal initial du niveau 1
 * \author Mathieu Constant
 * \version 1.0
 * \date 18 mars 2021
 */

#include "sdl2-light.h"
#include <stdio.h>
#include <stdlib.h>
#include "library/Display/Display.h"
#include "library/World/world.h"
#include "library/utility/utility.h"


/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */

void handle_events(SDL_Event *event,world_t *world){
    Uint8 *keystates;
    while( SDL_PollEvent( event ) ) {
        
        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_QUIT ) {
            //On indique la fin du jeu
            world->gameover = 1;
        }
       
         //si une touche est appuyée
         if(event->type == SDL_KEYDOWN){
             //si la touche appuyée est 'D'

             switch (event->key.keysym.sym)
             {
             case SDLK_d:
             
                world->vaisseau->x += MOVING_STEP;
                break;
            case SDLK_q:
                world->vaisseau->x -= MOVING_STEP;
                break;
            case SDLK_z:
                world->speed_h = 4;

                printf("%f\n", world->speed_h);
                break;
            case SDLK_s:
                world->speed_h = INITIAL_SPEED;
                break;
            case SDLK_ESCAPE:
                world->gameover = 1;
                break; 
             default:
                break;
             }
            //  print_sprite(world->vaisseau);
        }
    }
}

/**
 * \brief La fonction initialise les textures nécessaires à l'affichage graphique du jeu
 * \param screen la surface correspondant à l'écran de jeu
 * \param textures les textures du jeu
*/

/**
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des textures, initialisation des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param textures les textures
 * \param world le monde
 */

void init(SDL_Window **window, SDL_Renderer ** renderer, ressources_t *textures, world_t * world){
    init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    // Initialisation du ttf
    init_ttf();
    init_ressource(*renderer,textures);

}


/**
 *  \brief programme principal qui implémente la boucle du jeu
 */


int main( int argc, char* args[] )
{
    SDL_Event event;
    world_t world;
    ressources_t textures;
    SDL_Renderer *renderer;
    SDL_Window *window;

    //initialisation du jeu
    init(&window,&renderer,&textures,&world);
    
    while(!is_game_over(&world)){ //tant que le jeu n'est pas fini

        //gestion des évènements
        handle_events(&event,&world);

        //mise à jour des données liée à la physique du monde
        update_data(&world);

        //rafraichissement de l'écran
        refresh_graphics(renderer,&world,&textures);

        // pause de 10 ms pour controler la vitesse de rafraichissement
        pause(10);
    }
    
    //nettoyage final
    clean(window,renderer,&textures,&world);
    
    
    return 0;
}
