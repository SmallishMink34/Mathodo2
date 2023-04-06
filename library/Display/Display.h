/**
 * \file Display.h
 * \author M Moulias 
 * \brief Fichier qui contient les fonctions liée à l'affichage du jeu
 * \version 0.1
 * \date 2023-04-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../../sdl2-light.h"
#include "../../sdl2-ttf-light.h"
#include "../World/world.h"
#include "../../constante.c"
#include <stdio.h>
#include <stdlib.h>

#ifndef DISPLAY_H
#define DISPLAY_H


/**
 * \brief La structure qui contient les textures du jeu
 * 
 * \param background
 * \param ship
 * \param meteorite
 * \param finishLine
 * \param font
 * \param color
 * 
 */
struct ressources_s{
    SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture* ship; /*!< Texture liée à l'image du vaisseau. */
    SDL_Texture* meteorite; /*!< Texture liée à l'image du météorite. */
    SDL_Texture* finishLine; /*!< Texture liée à l'image de la ligne d'arrivée. */
    TTF_Font *font; // Font
    SDL_Color color; // Color
    /* A COMPLETER */
};

typedef struct ressources_s ressources_t;

/**
 * \brief La fonction initialise les textures du jeu
 * 
 * \param renderer 
 * \param textures 
 */
void init_ressource(SDL_Renderer *renderer, ressources_t *textures);

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
void refresh_graphics(SDL_Renderer *renderer, world_t *world,ressources_t *textures);

/**
 * \brief La fonction nettoie les textures
 * \param textures les textures
*/
void clean_textures(ressources_t *textures);

/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des textures, nettoyage des données
* \param window la fenêtre du jeu
* \param renderer le renderer
* \param textures les textures
* \param world le monde
*/
void clean(SDL_Window *window, SDL_Renderer * renderer, ressources_t *textures, world_t * world);

#endif