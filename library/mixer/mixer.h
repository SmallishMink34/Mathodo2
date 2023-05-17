#include "../../src/include/SDL2/SDL_mixer.h"

void init_mixer();   

Mix_Music* init_music(char * path);

void play_music(Mix_Music* music, int loop);