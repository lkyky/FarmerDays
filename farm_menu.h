#ifndef FARM_MENU_H
#define FARM_MENU_H
#include "splashkit.h"
#include "utilities.h"
#include "farm.h"
#include "audio.h"

/**
 * The menu option to let users to pick if what they want to do after entering the farm.
 * 
 * @option EXIT_FARM
 * @option GROW_CROP
 * @option ADD_NEW_CROP
 * @option VIEW_FIELD
 */
enum farm_menu_option
{
    EXIT_FARM,
    FARM_GROW_CROP,
    ADD_NEW_CROP,
    VIEW_FIELD
};

/**
 * The menu in the farm where users can choose to plant crops, add crops or view field.
 * 
 * @param crop The list of currently available crops.
 * @param farm The data of the farm.
 * @param player The data of the player.
 * @param last_ms The last time in milliseconds.
 */
void farm_menu(crop_list &crop, farm_data &farm, player_data &player, uint32_t &last_ms);

#endif