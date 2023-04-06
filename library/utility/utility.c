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