#ifndef MONSTER_H
#define MONSTER_H
#include "splashkit.h"
#include "utilities.h"
#include "player.h"

/**
 * The monster's data
 * 
 * @field monster_name The monster's given name.
 * @field monster_hp The monster's initial hp.
 * @field monster_attack The monster's attack power.
 * @field reward_coins The reward coins after defeating the monster.
 */
struct monster_data
{
    string monster_name;
    int monster_hp;
    int monster_attack;
    int reward_coins;
};

/**
 * Generates a random integer within a specific range.
 * 
 * @param min The minimum value.
 * @param max The maximum value.
 * 
 * @return A random integer between min and max.
 */
int rand_range(int min, int max);

/**
 * Creates a monster with stats scaled to the player's level.
 * 
 * @param player_level The current level of the player.
 * 
 * @return A new monster_data instance.
 */
monster_data spawn_monster(int player_level);

/**
 * Calculates the damage dealt by the monster.
 * 
 * @param monster The monster dealing the damage.
 * @return The calculated damage value.
 */
int monster_damage(const monster_data &monster);

/**
 * Calculates the damage dealy by the player.
 * 
 * @param weapon The weapon's data.
 * @return The calculate damage value.
 */
int player_damage(const weapon_data &weapon);

#endif