#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL_mixer.h>
#include <stdbool.h>

// Initialise le système audio
bool initAudio();

// Charge la musique de fond
Mix_Music* loadBackgroundMusic(const char* path); // on charge la musique de fond

// Charge le son du clic
Mix_Chunk* loadClickSound(const char* path); // on charge le son du clic

// Charge le son de la roulette
Mix_Chunk* loadSpinSound(const char* path); // on charge le son de la roulette

// Joue un son (pour le clic)
void playClickSound(Mix_Chunk* sound); // on fait le son du clic

// Joue le son de la roulette
void playSpinSound(Mix_Chunk* sound); // la roue tourne, faut bien qu'il y ai un son

// Libère les ressources audio et ferme le système audio
void closeAudio(Mix_Music* backgroundMusic, Mix_Chunk* clickSound, Mix_Chunk* spinSound); // Fermeture du système audio

#endif // AUDIO_H
