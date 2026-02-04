#ifndef MARKET_MENU_H
#define MARKET_MENU_H
#include "splashkit.h"
#include "utilities.h"
#include "player.h"
#include "crop.h"
#include "farm.h"

/**
 * The menu option to let users to pick if what they want to do after entering the market.
 *
 * @option EXIT_MARKET
 * @option SELL_CROP
 * @option UPGRADE_WEAPON
 * @option BUY_POTION
 */
enum market_menu_option
{
    EXIT_MARKET,
    SELL_CROP,
    UPGRADE_WEAPON,
    BUY_POTION
};

/**
 * Show the menu in market to let users pick what they would like to do.
 *
 * @return int the chosen option.
 */
market_menu_option read_market_menu_option();

/**
 * Asks the player if they would like to upgrade their current weapon.
 * 
 * @param weapon The weapon's data.
 * @param player The player's data.
 */
void upgrade_weapon(weapon_data &weapon, player_data &player);

/**
 * Asks the player if they would like to buy HP potion to refil HP.
 * 
 * @param player The player's data.
 */
void buy_potion(player_data &player);

/**
 * The market menu logic where players can choose to sell crops, upgrade weapon or buy potion.
 * 
 * @param crop The crop list they player have.
 * @param player The player's data.
 * @param weapon The weapon's data.
 * @param farm The farm's data.
 * @param last_ms Timestamp of the last time in ms.
 */
void market_menu(crop_list &crop, player_data &player, weapon_data &weapon, farm_data &farm, uint32_t &last_ms);

#endif