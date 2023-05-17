#include "mixer.h"

#include <stdio.h>
#include <stdlib.h>

void init_mixer(){
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Erreur lors de l'initialisation de SDL Mixer: %s\n", Mix_GetError());
    }
}

Mix_Music* init_music(char * path){
    Mix_Music* musique = Mix_LoadMUS(path);
    if (musique == NULL) {
        printf("Erreur lors du chargement de la musique: %s\n", Mix_GetError());
    }
    printf("musique chargée\n");
    return musique;
}

void play_music(Mix_Music* music, int loop){
    printf("musique jouée\n");  
    Mix_PlayMusic(music, loop);
}