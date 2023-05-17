/**
 * \file Display.h
 * \author M Moulias 
 * \brief Fichier qui contient les fonctions liées au son du jeu
 * \version 0.1
 * \date 2023-04-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../../src/include/SDL2/SDL_mixer.h"

/**
 * @brief Initialise le mixer
 * 
 */
void init_mixer();   

/**
 * @brief Initialise la musique donnée en paramètre
 * 
 * @param path 
 * @return Mix_Music* 
 */
Mix_Music* init_music(char * path);

/**
 * @brief Joue la musique donnée en paramètr, -1 pour jouer a l'infini
 * 
 * @param music 
 * @param loop 
 */
void play_music(Mix_Music* music, int loop);