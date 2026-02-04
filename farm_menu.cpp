#include "farm_menu.h"

/**
 * Show the menu in farm to let users pick what they would like to do.
 * 
 * @return int the chosen option.
 */
farm_menu_option read_farm_menu_option()
{
    write_line("0. Exit Farm");
    write_line("1. Grow Crop");
    write_line("2. Add New Crop");
    write_line("3. View Field");

    return (farm_menu_option)read_integer("Choice: ", 0, 3);
}

void farm_menu(crop_list &crop, farm_data &farm, player_data &player, uint32_t &last_ms)
{
    int farm_choice;
    do
    {
        update_farm_with_time(farm, player, last_ms);
        write_line("\nWhat would you like to do in the farm? ");
        farm_choice = read_farm_menu_option();
        switch (farm_choice)
        {
            case EXIT_FARM:
                play_sfx("click", 0.7);
                write_line("Teleporting back to home..");
                break;
            case FARM_GROW_CROP:
            {
                play_sfx("click", 0.7);
                grow_crop(crop, farm, player, last_ms);
                break;
            }
            case ADD_NEW_CROP:
                play_sfx("click", 0.7);
                add_new_crop(crop);
                break;
            case VIEW_FIELD:
                play_sfx("click", 0.7);
                update_farm_with_time(farm, player, last_ms);
                view_field(farm);
                break;
        }
        
    }while (farm_choice != EXIT_FARM);
}