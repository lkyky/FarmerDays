#ifndef FARM_H
#define FARM_H
#include "splashkit.h"
#include "crop.h"
#include "player.h"
#include "audio.h"
#include <vector>

using std::vector;

/**
 * The planted crop's data.
 * 
 * @field crop The crop's data.
 * @field quantity The planted crops' quantity.
 * @field time_remaining The time remaining for the planted crops.
 */
struct planted_crop
{
    crop_data crop;
    int quantity;
    int time_remaining;
};

/**
 * The farm's data.
 * 
 * @field max_capacity The farm's crops maximum capacity.
 * @field used_capacity The farm's currently used capacity.
 * @field planted The currently planted crops.
 */
struct farm_data
{
    int max_capacity;
    int used_capacity;
    vector<planted_crop> planted;
};

/**
 * Updates crop growth timers by a given number of seconds.
 * 
 * @param farm The farm's data.
 * @param seconds Elapsed time in seconds to apply.
 */
void update_farm_timer(farm_data &farm, int seconds);

/**
 * Updates the farm based on real elapsed time using tick counts.
 * 
 * @param farm The farm's data.
 * @param player The player's data.
 * @param last_ms Timestamp of the last time in ms.
 */
void update_farm_with_time(farm_data &farm, player_data &player, uint32_t &last_ms);

/**
 * The logic of growing a crop in the farm.
 * 
 * @param list The currently available list of crops.
 * @param farm The farm's data.
 * @param player The player's data.
 * @param last_ms Timestamp of the last time in ms.
 */
void grow_crop(const crop_list &list, farm_data &farm, player_data &player, uint32_t &last_ms);

/**
 * The action of viewing the current field condition to see what crops are growing.
 * 
 * @param farm The farm's data.
 */
void view_field(const farm_data &farm);

/**
 * The action of harversting crops that are ready automatically once timer is over.
 * 
 * @param farm The farm's data.
 * @param player The player's data.
 */
void harvest_ready_crops(farm_data &farm, player_data &player);

/**
 * Finds the crop price based on name from the list.
 * 
 * @param list The currently available list of crops.
 * @param name The crop's name.
 */
int find_crop_price(const crop_list &list, const string &name);

/**
 * Sells the crop based on name and quantity.
 * 
 * @param list The currently available list of crops.
 * @param player The player's data.
 */
void sell_crop(const crop_list &list, player_data &player);
#endif