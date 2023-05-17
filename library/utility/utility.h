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
#include "../../constante.c"
#ifndef Utility_h
#define Utility_h


/**
 * \brief Concatène plusieurs chaines de caractères
 * 
 * \param dest 
 * \param num_args 
 * \param ... Nombre d'arguments variables
 * \return char* 
 */
char * strcats(char* dest, int num_args, ...);

/**
 * @brief Modify un str par un autre
 * 
 * @param str 
 * @param str2 
 */
void modify_str(char *str, char *str2);
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

/**
 * @brief Retourne le nombre de chiffres d'un entier
 * 
 * @param n 
 * @return int 
 */
int number_of_numbers(int n);
#endif