#include "../../sdl2-light.h"
#include "../World/world.h"
#include "../../constante.c"

#ifndef DISPLAY_H
#define DISPLAY_H
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

void init_textures(SDL_Renderer *renderer, textures_t *textures);

/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param texture la texture liée au fond
*/
void apply_background(SDL_Renderer *renderer, SDL_Texture *texture);

/**
 * \brief La fonction qui applique la texture \a texture sur le renderer \a renderer en fonction des données du sprite \a sprite
 * 
 * \param texture
 * \param renderer 
 * \param sprite 
 */
void apply_sprite(SDL_Renderer * renderer, SDL_Texture *texture, sprite_t *sprite);

/**
 * \brief La fonction qui applique la texture \a texture sur le renderer \a renderer en fonction des coordonnées \a x et \a y
 * 
 * \param renderer 
 * \param texture 
 * \param x 
 * \param y 
 */
void apply_wall(SDL_Renderer * renderer, SDL_Texture *texture, int x, int y);


/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer le renderer lié à l'écran de jeu
 * \param world les données du monde
 * \param textures les textures
 */
void refresh_graphics(SDL_Renderer *renderer, world_t *world,textures_t *textures);

/**
 * \brief La fonction nettoie les textures
 * \param textures les textures
*/

void clean_textures(textures_t *textures);

/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des textures, nettoyage des données
* \param window la fenêtre du jeu
* \param renderer le renderer
* \param textures les textures
* \param world le monde
*/

void clean(SDL_Window *window, SDL_Renderer * renderer, textures_t *textures, world_t * world);

#endif