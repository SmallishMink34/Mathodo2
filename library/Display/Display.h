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
 * \param bmenu
 * \param ship
 * \param meteorite
 * \param finishLine
 * \param font
 * \param color
 * 
 */
struct ressources_s{
    SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture* bmenu;/*!< Texture liée à l'image du fond du menu. */
    SDL_Texture* background2; /*!< Texture liée à l'image du fond de l'écran. (effet parallax) */
    SDL_Texture* background3; /*!< Texture liée à l'image du fond de l'écran. (effet parallax) */
    SDL_Texture* ship; /*!< Texture liée à l'image du vaisseau. */

    SDL_Texture* meteorite; /*!< Texture liée à l'image du météorite. */
    SDL_Texture* e_rotate; /*!< Texture liée à l'image de l'élément de rotation. */
    SDL_Texture* coins; /*!< Texture liée à l'image des pièces. */
    SDL_Texture* finishLine; /*!< Texture liée à l'image de la ligne d'arrivée. */
    SDL_Texture* BarreProgression; /*!< Texture liée à l'image de l'air. */
    SDL_Texture* vaisseauMini; /*!< Texture liée à l'image du vaisseau. */

    SDL_Texture* soleilBarre; /*!< Texture liée à l'image du soleil. */
    SDL_Texture* soleil; /*!< Texture liée à l'image du soleil. */

    TTF_Font *font; // Font
    SDL_Color color; // Color
    long double angle; /*!< Angle de rotation de l'image. */
    int nb_init; /*!< Nombre d'initialisation. */
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
 * \brief La fonction initialise les textures des elements du jeu
 *  
 * \param renderer 
 * \param textures 
 */
void init_ressource_element(SDL_Renderer *renderer, ressources_t *textures);

/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param texture la texture liée au fond
*/
void apply_background(SDL_Renderer *renderer, SDL_Texture *texture, world_t *world, int parallax);

/**
 * \brief La fonction qui applique la texture \a texture sur le renderer \a renderer en fonction des données du sprite \a sprite (avec rotation)
 * 
 * \param texture
 * \param renderer 
 * \param sprite 
 */
void apply_sprite(SDL_Renderer * renderer, SDL_Texture *texture, sprite_t *sprite, world_t *world);

/**
 * @brief La fonction qui applique la texture \a texture sur le renderer \a renderer en fonction des données du sprite \a sprite (sans rotation)
 * 
 * @param renderer 
 * @param texture 
 * @param sprite 
 * @param world 
 */
void apply_sprite_fixed(SDL_Renderer * renderer, SDL_Texture *texture, sprite_t *sprite, world_t *world);
/**
 * \brief La fonction qui applique la texture \a texture sur le renderer \a renderer en fonction des coordonnées \a x et \a y
 * 
 * \param renderer 
 * \param texture 
 * \param x 
 * \param y 
 */
void apply_wall(SDL_Renderer * renderer, SDL_Texture *texture, int x, int y, world_t *world);

/**
 * \brief La fonction qui applique les textures des murs sur le renderer \a renderer en fonction des données du monde \a world
 * 
 * \param renderer 
 * \param texture 
 * \param world 
 * \param res 
 */
void apply_walls(SDL_Renderer * renderer, SDL_Texture *texture, world_t *world, ressources_t *res);

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

void ingame(SDL_Renderer *renderer, world_t *world,ressources_t *textures);

void inmenu(SDL_Renderer *renderer, world_t *world,ressources_t *textures);

#endif