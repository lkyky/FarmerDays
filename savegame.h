#ifndef SAVEGAME_H
#define SAVEGAME_H
#include "splashkit.h"
#include "utilities.h"
#include "player.h"

#include <sstream>
using std::stringstream;
#include <fstream>
using std::ifstream;
using std::ofstream;

/**
 * Loads a player's data and weapon from a csv file.
 * 
 * @param filename The name of the csv file.
 * @param name Name of the player to load.
 * @param out_player Output parameter receiving the player data.
 * @param out_weapon Output parameter receiving the weapon data.
 * 
 * @return true if the player was found and loaded successfully.
 */
bool load_player_from_csv(const string &filename, const string &name, player_data &out_player, weapon_data &out_weapon);

/**
 * Saves a player's data and weapon in a csv file.
 * 
 * @param filename The name of the csv file.
 * @param player The player's data.
 * @param weapon The weapon's data.
 */
void save_player_to_csv(const string &filename, const player_data &player, const weapon_data &weapon);

/**
 * Loads a player's inventory from a csv file.
 * 
 * @param filename The name of the csv file.
 * @param player_name Name of the player whose inventory is loaded.
 * @param player The player's data.
 */
bool load_inventory_from_csv(const string &filename, const string &player_name, player_data &player);

/**
 * Saves a player's inventory data in a csv file.
 * 
 * @param filename The name of the csv file.
 * @param player The player's data.
 */
void save_inventory_to_csv(const string &filename, const player_data &player);

#endif