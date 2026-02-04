#include "audio.h"

void load_game_audio()
{
    load_sound_effect("coins", "coins.ogg");
    load_sound_effect("harvest", "harvested.ogg");
    load_sound_effect("start", "start.ogg");
    load_sound_effect("quit", "quit.ogg");
    load_sound_effect("won", "won.ogg");
    load_sound_effect("defeated", "defeated.ogg");
    load_sound_effect("click", "click.ogg");

    load_music("bgm", "mainbgm.ogg");
    load_music("dungeon", "dungeon.ogg");
}

void play_sfx(const string &name, double volume)
{
    play_sound_effect(name, volume);
}

void play_bgm(const string &name, int times)
{
    stop_music();
    play_music(name, times);
}