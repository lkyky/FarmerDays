#include "splashkit.h"
#include "utilities.h"

#include "player.h"
#include "crop.h"
#include "farm.h"
#include "monster.h"
#include "farm_menu.h"
#include "market_menu.h"
#include "dungeon_menu.h"
#include "highscore.h"
#include "audio.h"
#include "savegame.h"

/**
 * The list of options in main menu.
 * 
 * @option EXIT_GAME The option to exit game.
 * @option FARM The option to go to the farm.
 * @option MARKET The option to go to the market.
 * @option DUNGEON The option to go to the dungeon.
 * @option VIEW_INVENTORY The option to go to inventory.
 */
enum main_menu_option
{
    EXIT_GAME,
    FARM,
    MARKET,
    DUNGEON,
    VIEW_INVENTORY
};

/**
 * Show the main menu and get the chosen option from the user.
 * 
 * @return int the chosen option.
 */
main_menu_option read_main_menu_option()
{
    write_line("0. Exit Game");
    write_line("1. Farm");
    write_line("2. Market");
    write_line("3. Dungeon");
    write_line("4. View Inventory");

    return (main_menu_option)read_integer("Select an option (0-4): ", 0, 4);
}

int main()
{
    load_game_audio();
    play_sfx("start", 1.0);
    play_bgm("bgm", -1);

    player_data current_player;
    weapon_data my_weapon;
    current_player.player_name = read_string("Welcome to Farmer Days! \nWhat's your name? ");

    if (load_player_from_csv("players.csv", current_player.player_name, current_player, my_weapon))
    {
        write_line("Welcome back " + current_player.player_name + "!");
    }
    else
    {
        current_player.coin = 500;
        current_player.hp = 100;
        current_player.level = 1;
        current_player.total_planted_crops = 0;
        current_player.inventory_head = nullptr;
        
        my_weapon.weapon_name = "Sword";
        my_weapon.weapon_level = 1;
        my_weapon.upgrade_cost = 50;
        my_weapon.base_damage = 5;

        write_line("New game started for " + current_player.player_name + "!");
    }

    farm_data my_farm;
    my_farm.max_capacity = 100;
    my_farm.used_capacity = 0;

    crop_list crop;
    load_crops_from_csv("crops.csv", crop);

    bool died_broke = false;

    if (crop.empty())
    {
        init_crop_list(crop);

        for (int i = 0; i < (int)crop.size(); i++)
            save_crops_to_csv("crops.csv", crop[i]);
    }

    uint32_t last_ms = current_ticks();

    load_inventory_from_csv("inventory.csv", current_player.player_name, current_player);

    main_menu_option choice;
    do
    {
        update_farm_with_time(my_farm, current_player, last_ms);

        // Top menu showing information of the player
        write_line("\nPlayer Name: " + current_player.player_name + " | Level: " + to_string(current_player.level)
            + " |  Coins: " + to_string(current_player.coin) + " |  HP: " + to_string(current_player.hp));

        choice = read_main_menu_option();

        switch(choice)
        {
            case EXIT_GAME:
            {
                play_sfx("quit", 1.0);
                delay(500);

                bool top = record_highscore("highscores.csv", current_player);
                write_line("\nYour final score: " + to_string(calculate_score(current_player)));
                if (top) write_line("Yay! You made it to the leaderboard!");
                show_highscore("highscores.csv");

                if (!died_broke) 
                {
                    save_player_to_csv("players.csv", current_player, my_weapon);
                }
                else
                {
                    write_line("Progress was reset due to defeat.");
                }
                write_line("See you again!");
                save_inventory_to_csv("inventory.csv", current_player);
            }
            break;
            case FARM:
                play_sfx("click", 0.7);
                write_line("Teleporting to the farm..");
                farm_menu(crop, my_farm, current_player, last_ms);
                break;
            case MARKET:
                play_sfx("click", 0.7);
                write_line("Teleporting to the market..");
                market_menu(crop, current_player, my_weapon, my_farm, last_ms);
                break;
            case DUNGEON:
                write_line("Teleporting to the dungeon..");
                fade_music_out(300);
                play_bgm("dungeon", -1);
                fight_monster(current_player, my_weapon, died_broke);
                fade_music_out(300);
                play_bgm("bgm", -1);
                break;
            case VIEW_INVENTORY:
                play_sfx("click", 0.7);
                write_line("Viewing inventory..");
                view_inventory(current_player);
                break;
        }
    } while (choice != EXIT_GAME);
    return 0;
}