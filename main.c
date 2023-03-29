/**
 * \file main.c
 * \brief Programme principal initial du niveau 1
 * \author Mathieu Constant
 * \version 1.0
 * \date 18 mars 2021
 */

#include "sdl2-light.h"
#include <stdio.h>

/**
 * \brief Largeur de l'écran de jeu
 */
#define SCREEN_WIDTH 300

/**
 * \brief Hauteur de l'écran de jeu
 */
#define SCREEN_HEIGHT 480


/**
 * \brief Taille d'un vaisseau
 */

#define SHIP_SIZE 32


/**
 * \brief Taille d'un météorite
*/

#define METEORITE_SIZE 32


/**
 * \brief Hauteur de la ligne d'arrivée
 */


#define FINISH_LINE_HEIGHT 10


/**
 * \brief Pas de déplacement horizontal du vaisseau
*/

#define MOVING_STEP 10


/**
  * \brief Vitesse initiale de déplacement vertical des éléments du jeu 
*/

#define INITIAL_SPEED 2




/**
 * \brief Représentation pour stocker les textures nécessaires à l'affichage graphique
*/

struct textures_s{
    SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture* ship; /*!< Texture liée à l'image du vaisseau. */
    SDL_Texture* meteorite; /*!< Texture liée à l'image du météorite. */
    SDL_Texture* finishLine; /*!< Texture liée à l'image de la ligne d'arrivée. */
    /* A COMPLETER */
};


/**
 * \brief Type qui correspond aux textures du jeu
*/

typedef struct textures_s textures_t;


/**
 * \brief Représentation pour stocker les données du vaisseau
 * 
 */
struct sprite_s{
    int x;
    int y;
    int w;
    int h;
};

typedef struct sprite_s sprite_t;

/**
 * \brief Représentation du monde du jeu
*/

struct world_s{
    sprite_t *vaisseau ; /*!< Représentation du vaisseau */
    sprite_t *mur; /*!< Représentation du météorite */
    sprite_t *ligneArriver;
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */
    int speed_h; /*!< Vitesse de déplacement horizontal des éléments du jeu */

};

/**
 * \brief Type qui correspond aux données du monde
 */

typedef struct world_s world_t;


/**
 * \brief Fonction qui affiche les données du vaisseau
 * 
 */

void print_sprite(sprite_t *sprite){
    printf("x = %d, y = %d, w = %d, h = %d\n", sprite->x, sprite->y, sprite->w, sprite->h);
}

/**
 * \brief La fonction initialise les sprites du jeu
 * 
 * \param sprite 
 * \param x 
 * \param y 
 * \param w 
 * \param h 
 */
sprite_t *init_sprite(sprite_t *sprite, int x, int y, int w, int h){
    sprite = malloc(sizeof(sprite_t));
    sprite->x = x;
    sprite->y = y;
    sprite->w = w;
    sprite->h = h;
    return sprite;
}

/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */


void init_data(world_t * world){
    
    //on n'est pas à la fin du jeu
    world->gameover = 0;
    world->speed_h = 0;

    // Initialisation du vaisseau

    
    world->vaisseau = init_sprite(world->vaisseau, SCREEN_WIDTH/2 - SHIP_SIZE/2, SCREEN_HEIGHT - SHIP_SIZE, SHIP_SIZE, SHIP_SIZE);
    world->mur = init_sprite(world->mur, 0, 0, 3*METEORITE_SIZE, 7*METEORITE_SIZE);
    world->ligneArriver = init_sprite(world->ligneArriver, 0, -40, SCREEN_WIDTH, FINISH_LINE_HEIGHT);

    print_sprite(world->vaisseau);
}




/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */


void clean_data(world_t *world){
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
    free(world->vaisseau);
}



/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */

int is_game_over(world_t *world){
    return world->gameover;
}



/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param les données du monde
 */

void update_data(world_t *world){
    world->ligneArriver->y += INITIAL_SPEED - world->speed_h;
    world->mur->y += INITIAL_SPEED - world->speed_h;
}



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
                world->vaisseau->y -= MOVING_STEP;
                world->speed_h = 3;
                break;
            case SDLK_s:
                world->vaisseau->y += MOVING_STEP;
                world->speed_h = -3;
                break;
            case SDLK_ESCAPE:
                world->gameover = 1;
                break; 
             default:
                break;
             }
             print_sprite(world->vaisseau);
             
        }else if(event->type == SDL_KEYUP){
            world->speed_h = 0;
        }
        
    }
}


/**
 * \brief La fonction nettoie les textures
 * \param textures les textures
*/

void clean_textures(textures_t *textures){
    clean_texture(textures->background);
    clean_texture(textures->ship);
    clean_texture(textures->meteorite);
    clean_texture(textures->finishLine);

    /* A COMPLETER */
}



/**
 * \brief La fonction initialise les textures nécessaires à l'affichage graphique du jeu
 * \param screen la surface correspondant à l'écran de jeu
 * \param textures les textures du jeu
*/

void  init_textures(SDL_Renderer *renderer, textures_t *textures){
    textures->background = load_image( "ressources/space-background.bmp",renderer);
    textures->ship = load_image( "ressources/spaceship.bmp",renderer);
    textures->meteorite = load_image( "ressources/meteorite.bmp",renderer);
    textures->finishLine = load_image( "ressources/finish_line.bmp",renderer);
    
    /* A COMPLETER */

    
}


/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param texture la texture liée au fond
*/

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


/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer le renderer lié à l'écran de jeu
 * \param world les données du monde
 * \param textures les textures
 */

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



/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des textures, nettoyage des données
* \param window la fenêtre du jeu
* \param renderer le renderer
* \param textures les textures
* \param world le monde
*/

void clean(SDL_Window *window, SDL_Renderer * renderer, textures_t *textures, world_t * world){
    clean_data(world);
    clean_textures(textures);
    clean_sdl(renderer,window);
}



/**
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des textures, initialisation des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param textures les textures
 * \param world le monde
 */

void init(SDL_Window **window, SDL_Renderer ** renderer, textures_t *textures, world_t * world){
    init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    init_textures(*renderer,textures);
}


/**
 *  \brief programme principal qui implémente la boucle du jeu
 */


int main( int argc, char* args[] )
{
    SDL_Event event;
    world_t world;
    textures_t textures;
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
