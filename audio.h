#ifndef AUDIO_H
#define AUDIO_H
#include "splashkit.h"

/**
 * loads all available game audio into memory
 */
void load_game_audio();

/**
 * Plays a sound effect.
 * 
 * @param name The name of the sound effect to play.
 * @param volume The playback volume
 */
void play_sfx(const string &name, double volume = 1.0);

/**
 * Plays background music.
 * 
 * @param name The name of the background music to play.
 * @param times The number of times the music should loop.
 */
void play_bgm(const string &name, int times);

#endif