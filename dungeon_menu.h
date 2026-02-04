#ifndef DUNGEON_MENU_H
#define DUNGEON_MENU_H
#include "splashkit.h"
#include "utilities.h"
#include "player.h"
#include "monster.h"
#include "audio.h"

/**
 * Menu choice of the options when fighting monsters.
 */
int read_combat_choice();

/**
 * Logic of monster fighting.
 * 
 * @param player The player's data.
 * @param weapon The weapon's data.
 * @param died_broke If the player's coin is <= 0 after the fight.
 */
void fight_monster(player_data &player, weapon_data &weapon, bool &died_broke);

#endif