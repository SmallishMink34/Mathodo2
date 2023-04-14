#include "sprites.h"
#include "../../constante.c"
#include <string.h>
int isOverScreen(sprite_t *sprite){
    if(sprite->x < 0 || sprite->x + sprite->w > SCREEN_WIDTH || sprite->y < 0 || sprite->y + sprite->h > SCREEN_HEIGHT){
        return 1;
    }
    return 0;
}

void print_sprite(sprite_t *sprite){
    printf("x = %d, y = %d, w = %d, h = %d\n", sprite->x, sprite->y, sprite->w, sprite->h);
}


sprite_t *init_sprite(sprite_t *sprite, int x, int y, int w, int h, char id){
    sprite = malloc(sizeof(sprite_t));
    sprite->x = x;
    sprite->y = y;
    sprite->w = w;
    sprite->h = h;
    sprite->id = malloc(sizeof(char) * 10);
    strcpy(sprite->id, &id);

    return sprite;
}

int sprites_collide(sprite_t *sp1, sprite_t *sp2){
    if (sp1->x + sp1->w < sp2->x){
        return 0;
    }else if(sp1->x > sp2->x + sp2->w){
        return 0;
    }else if(sp1->y + sp1->h < sp2->y){
        return 0;
    }else if(sp1->y > sp2->y + sp2->h){
        return 0;
    }
    return 1;
}