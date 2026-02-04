#ifndef PLAYER_H
#define PLAYER_H
#include "splashkit.h"
#include "crop.h"
#include "audio.h"
#include <vector>

/**
 * The player's inventory data.
 * 
 * @field crop_name The crop's name.
 * @field quantity The crop's quantity.
 * @field next A pointer to the next node in the inventory list.
 */
struct inventory_node
{
    string crop_name;
    int quantity;
    inventory_node *next;
};

/**
 * The player's data.
 * 
 * @field player_name The player's name.
 * @field level The player's level.
 * @field coin The player's current coins quantity.
 * @field hp The player's current hp.
 */
struct player_data
{
    string player_name;
    int level, coin, hp, total_planted_crops;
    inventory_node *inventory_head;
};

/**
 * The weapon's data.
 * 
 * @field weapon_name The weapon's name.
 * @field weapon_level The weapon's level.
 * @field base_damage The base damage of the weapon.
 * @field upgrade_cost The upgrade cost needed for the weapon.
 */
struct weapon_data
{
    string weapon_name;
    int weapon_level;
    int base_damage;
    int upgrade_cost;
};

/**
 * Adds crop to the player's inventory list.
 * 
 * @param player The player's data.
 * @param crop The crop's data.
 * @param qty Quantity of the crop.
 */
void add_to_inventory(player_data &player, const crop_data &crop, int qty);

/**
 * Removes a specific quantity of crop from the player's inventory.
 * 
 * @param player The players's data.
 * @param crop_name The name of the crop to remove.
 * @param qty Quantity of the crop.
 * 
 * @return true if the crop was successfully removed.
 */
bool remove_from_inventory(player_data &player, const string &crop_name, int qty);

/**
 * Display the content of the player's inventory.
 * 
 * @param player The player's data.
 */
void view_inventory(const player_data &player);

/**
 * Checks if the player has enough coins to afford something.
 * 
 * @param player The player's data.
 * @param cost The cost to compare.
 * @return true if the player has enough coins.
 */
bool can_afford(const player_data &player, int cost);

/**
 * Minus coins from the player.
 * 
 * @param player The player's data.
 * @param cost The amount of coins to minus.
 */
void spend_coins(player_data &player, int cost);

#endif