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
#define MAX_LINES 1000
#define MAX_LENGTH 200

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

/**
 * \brief Lit un fichier et retourne un tableau de lignes
 * 
 * \param filename  Le nom du fichier
 * \param num_lines  Le nombre de lignes
 * \return char** 
 */

char ** lirefile(char *filename, int *num_lines);

#endif