#include "menu.h"

#include <stdio.h>
#include <stdlib.h>

btn_t *init_btn(int x, int y, int w, int h){
    btn_t *btn = malloc(sizeof(btn_t));
    btn->rect.x = x;
    btn->rect.y = y;
    btn->rect.w = w;
    btn->rect.h = h;

    return btn;
}

int collidePoint(btn_t *btn, int x, int y){
    if (btn->rect.x > x && btn->rect.x + btn->rect.w < x && btn->rect.y > y && btn->rect.y + btn->rect.h < y;) return 1;
    return 0;
}