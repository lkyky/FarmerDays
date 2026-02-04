#include "market_menu.h"

market_menu_option read_market_menu_option()
{
    write_line("0. Exit Market");
    write_line("1. Sell Crop");
    write_line("2. Upgrade Weapon");
    write_line("3. Buy Potion");

    return (market_menu_option)read_integer("Choice: ", 0, 3);
}

void upgrade_weapon(weapon_data &weapon, player_data &player)
{
    string choice = read_string("Upgrade " + weapon.weapon_name + " for " + to_string(weapon.upgrade_cost) + "? [Y/N] ");
    if (choice == "Y" || choice == "y")
    {
        if (!can_afford(player, weapon.upgrade_cost))
        {
            write_line("Insufficient coins.");
            return;
        }
        spend_coins(player, weapon.upgrade_cost);

        player.coin -= weapon.upgrade_cost;
        weapon.weapon_level++;
        weapon.base_damage += 2;
        weapon.upgrade_cost += 50 * weapon.weapon_level;

        write_line("Leveled up " + weapon.weapon_name + " !!");
        write_line("Current weapon level: " + to_string(weapon.weapon_level));
        write_line("Current weapon damage: " + to_string(weapon.base_damage));
        write_line("Coins left: " + to_string(player.coin));
    }
    else
    {
        write_line("Teleporting back to home..");
        return;
    }
}

void buy_potion(player_data &player)
{
    const int POTION_COST = 100;

    string choice = read_string("Do you want to spend 100 coins to buy HP Potion? [Y/N] ");

    if (choice != "Y" && choice != "y")
    {
        return;
    }

    else
    {
        if (!can_afford(player, POTION_COST))
        {
            write_line("Insufficient coins.");
            return;
        }

        spend_coins(player, POTION_COST);
        player.hp = 100;

        write_line("1 HP Potion Bought!");
        write_line("HP is now 100");
    }
}

void market_menu(crop_list &crop, player_data &player, weapon_data &weapon, farm_data &farm, uint32_t &last_ms)
{
    int choice;
    do
    {
        update_farm_with_time(farm, player, last_ms);
        write_line("\nWhat would you like to do in the market? ");
        choice = read_market_menu_option();
        switch (choice)
        {
        case EXIT_MARKET:
            play_sfx("click", 0.7);
            write_line("Teleporting back to home..");
            break;
        case SELL_CROP:
        {
            play_sfx("click", 0.7);
            sell_crop(crop, player);
            break;
        }
        case UPGRADE_WEAPON:
            play_sfx("click", 0.7);
            upgrade_weapon(weapon, player);
            break;
        case BUY_POTION:
            play_sfx("click", 0.7);
            buy_potion(player);
            break;
        }

    } while (choice != EXIT_MARKET);
}