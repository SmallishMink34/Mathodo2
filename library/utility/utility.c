#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

char * strcats(char* dest, int num_args, ...) {
    va_list args;
    va_start(args, num_args);

    for (int i = 0; i < num_args; i++) {
        char* arg = va_arg(args, char*);
        strcat(dest, arg);
    }

    va_end(args);
    return dest;
}

char * int_to_str(int n) {
    char *str = malloc(sizeof(char) * 10);
    sprintf(str, "%d", n);
    return str;
}

char **lirefile(char *filename, int *num_lines) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    char **lines = malloc(MAX_LINES * sizeof(char *));
    *num_lines = 0;
    char buffer[MAX_LENGTH];
    while (fgets(buffer, MAX_LENGTH, file) != NULL && *num_lines < MAX_LINES) {
        lines[*num_lines] = malloc(MAX_LENGTH * sizeof(char));
        sprintf(lines[*num_lines], "%s", buffer);
        (*num_lines)++;
    }

    fclose(file);
    return lines;
}

int number_of_numbers(int n){
    if (n == 0){
        return 1;
    }
    int count = 0;
    while (n != 0){
        n /= 10;
        count++;
    }
    return count;
}

void modify_str(char *str, char *str2){
    str[0] = '\0';
    strcat(str, str2);
}