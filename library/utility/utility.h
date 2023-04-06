/**
 * \file utility.h
 * \author M Moulias 
 * \brief Fichier qui contient les fonctions utilitaires
 * \version 0.1
 * \date 2023-04-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdarg.h>

#ifndef Utility_h
#define Utility_h

/**
 * \brief Concatène plusieurs chaines de caractères
 * 
 * \param dest 
 * \param num_args 
 * \param ... 
 * \return char* 
 */
char * strcats(char* dest, int num_args, ...);

/**
 * \brief Convertit un entier en chaine de caractère
 * 
 * \param n 
 * \return char* 
 */
char * int_to_str(int n);

#endif