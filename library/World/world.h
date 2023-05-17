#include <stdio.h>
#include <stdlib.h>
#include "../Sprites/sprites.h"
#include "../../constante.c"
#include "../../src/include/SDL2/SDL.h"
#include <stdbool.h>
#include "../menu/menu.h"
#include "../mixer/mixer.h"

/**
 * \file world.h
 * \author M Moulias 
 * \brief Fichier qui contient les fonctions liées au monde du jeu
 * \version 0.1
 * \date 2023-04-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef WORLD_H
#define WORLD_H

/**
 * @brief La structure qui contient les données d'une progression barre
 * 
 */
struct progressBarre_s{
    SDL_Rect* Barre;
    SDL_Rect* Contours;
    SDL_Rect* Base;
    int pourcent;
};

typedef struct progressBarre_s progressBarre_t;

/**
 * \brief La structure qui contient les données du monde
 * 
 * \param vaisseau Vaisseau du joueur
 * \param mur Météorite
 * \param murs Tableau de météorites 
 * \param nb_murs Nombre de météorites 
 * \param ligneArriver Ligne d'arrivée
 * \param gameover Champ indiquant si l'on est à la fin du jeu
 * \param speed_h Vitesse de déplacement horizontal des éléments du jeu
 * \param startTimer  Timer de départ
 * \param timer  Timer de jeu
 * 
 */
struct world_s{
    sprite_t *vaisseau ; /*!< Représentation du vaisseau */
    sprite_t **murs; /*<Représentation des météorites>*/
    sprite_t **murs2; /*<Représentation des météorites et de l'air>*/

    sprite_t *vaisseau1;
    sprite_t *vaisseau2;
    sprite_t *vaisseau3;
    sprite_t *vaisseau4;

    btn_t *play;
    btn_t *exit;
    btn_t *magasin;
    btn_t *sound;

    Mix_Music* musique;
    
    int actualship;
    btn_t **ships;
    btn_t *exit_shp;

    sprite_t *BarreProgression;
    sprite_t *vaisseauMini;
    sprite_t *soleilBarre;
    sprite_t *soleil;
    sprite_t *air;
    sprite_t *coins;
    sprite_t *exit_shop;

    sprite_t **Spr_ship;
    progressBarre_t* pgb;
    bool *isBought;
    bool *isSelected;
    int *shopPrice;
    int nb_murs; // Nombre de météorites
    int nb_lines_murs; // Nombre de lignes de météorites
    sprite_t *ligneArriver;
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */
    float speed_h; /*!< Vitesse de déplacement horizontal des éléments du jeu */
    unsigned int startTimer; /*!< Timer de départ */
    unsigned int startTimer2; /*!< Timer de départ (flip) */
    unsigned int timer; /*!< Timer de jeu */
    char * temps_str; // String affichant le temps sur le jeu
    char * coins_str;
    char * coin_menu_str;


    double angle; // Angle de rotation de la map
    int isFlipping; // Indique si l'on est en train de faire une rotation de l'écran et dans quelle sens (0 : non droite, 1 : vers la droite, -1 : vers la gauche, -2 : non gauche)
    int gamestate;

    int mouseX;
    int mouseY;
    int money;
    int money2;

    int parallax;
    bool invicibility;

    
};
typedef struct world_s world_t;

/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */

void init_data(world_t * world);

/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param les données du monde
 */
void update_data(world_t *world);
/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */

int is_game_over(world_t *world);

/**
 * @brief Detecte si le vaisseau va en dehors de l'écran
 * 
 * @param world 
 */
void outBorder(world_t *world);

/**
 * @brief Actualise le timer de jeu
 * 
 * @param world 
 * @return int 
 */
int timer_update_s(world_t *world);

/**
 * \brief La fonction libère les données du monde
 * 
 * \param world les données du monde
 */
void clean_data(world_t * world);

/**
 * \brief La fonction qui retounre le monde
 * 
 * \param world 
 */
void flipScreen(world_t *world);

/**
 * \brief La fonction fais une action en fonction de la collision entre deux sprites
 * 
 * \param sp1 Généralement le vaisseau
 * \param sp2 Généralement la météorite
 * \param world Le monde
 * \param make_disappear Indique si l'on doit faire disparaître les sprites en cas de collision 
 */
void collide(sprite_t *sp1, sprite_t *sp2, world_t *world);


/**
 * \brief La fonction initialise les murs du jeu
 * 
 * \param world 
 */
void init_walls(world_t *world);

/**
 * \brief La fonction met à jour les murs du jeu
 * 
 * \param world 
 */
void update_walls(world_t *world);

/**
 * @brief La fonction qui enlève un mur
 * 
 * @param world 
 * @param index 
 */
void remove_wall(world_t *world, int index);

/**
 * \brief La fonction qui execute toutes les actions du jeu
 * 
 * \param world 
 */
void allEvents(world_t *world);

/**
 * @brief La fonction qui initialise le menu
 * 
 * @param world 
 */
void init_menu(world_t *world);

/**
 * @brief La fonction qui initialise le shop
 * 
 * @param world 
 */
void init_shop(world_t * world);

/**
 * @brief La fonction qui initialise la progression barre
 * 
 * @param x 
 * @param y 
 * @param w 
 * @param h 
 * @param pourcent 
 * @return progressBarre_t* 
 */
progressBarre_t *init_progressbarre(int x, int y, int w, int h, int pourcent);

/**
 * @brief La fonction qui met à jour la progression barre
 * 
 * @param pgb 
 * @param pourcent 
 */
void updateProgressBarre (progressBarre_t *pgb, int pourcent);
#endif
