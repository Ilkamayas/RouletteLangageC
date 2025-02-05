#include "audio.h"
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>

bool initAudio() {
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){ // on ouvre les fichiers sons
        printf("Erreur Mix_OpenAudio: %s\n", Mix_GetError());
        exit(EXIT_FAILURE);       // si erreur avec les sons, on sort
    }
    return true;
}

Mix_Music* loadBackgroundMusic(const char* path) {
    Mix_Music* music = Mix_LoadMUS(path); // on charge la musique de fond
    if(!music){
        printf("Erreur chargement musique fond: %s\n", Mix_GetError());
    }
    return music;
}

Mix_Chunk* loadClickSound(const char* path) {
    Mix_Chunk* sound = Mix_LoadWAV(path); // on charge le son du clic
    if(!sound){
        printf("Erreur chargement son clic: %s\n", Mix_GetError());
    }
    return sound;
}

Mix_Chunk* loadSpinSound(const char* path) {
    Mix_Chunk* sound = Mix_LoadWAV(path); // on charge le son de la roulette
    if(!sound){
        printf("Erreur chargement son spin: %s\n", Mix_GetError());
    }
    return sound;
}

void playClickSound(Mix_Chunk* sound) {
    if(sound){
        Mix_PlayChannel(-1, sound, 0); // on fait le son du clic
    }
}

void playSpinSound(Mix_Chunk* sound) {
    if(sound){
        Mix_PlayChannel(-1, sound, 0); // la roue tourne, faut bien qu'il y ai un son
    }
}

void closeAudio(Mix_Music* backgroundMusic, Mix_Chunk* clickSound, Mix_Chunk* spinSound) {
    if(backgroundMusic) Mix_FreeMusic(backgroundMusic);
    if(clickSound)      Mix_FreeChunk(clickSound);
    if(spinSound)       Mix_FreeChunk(spinSound);
    Mix_CloseAudio();             // Fermeture du système audio
}
