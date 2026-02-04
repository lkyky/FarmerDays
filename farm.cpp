#include "farm.h"

farm_data new_farm(crop_data crops, int max_capacity)
{
    farm_data farm;
    farm.max_capacity = max_capacity;
    return farm;
}

void update_farm_timer(farm_data &farm, int seconds)
{
    if (seconds <= 0)
    {
        return;
    }

    for (int i = 0; i < farm.planted.size(); i++)
    {
        planted_crop &planted = farm.planted[i];
        if (planted.time_remaining > 0)
        {
            planted.time_remaining -= seconds;
            if (planted.time_remaining < 0)
            {
                planted.time_remaining = 0;
            }
        }
    }
}

void update_farm_with_time(farm_data &farm, player_data &player, uint32_t &last_ms)
{
    uint32_t now_ms = current_ticks();
    uint32_t delta_ms = now_ms - last_ms;
    int delta_seconds = (int)(delta_ms / 1000);

    if (delta_seconds > 0)
    {
        update_farm_timer(farm, delta_seconds);
        last_ms += (uint32_t)(delta_seconds * 1000);
    }
    harvest_ready_crops(farm, player);
}

void update_player_level(int planted_now, player_data &player)
{
    int previous_total = player.total_planted_crops;
    player.total_planted_crops += planted_now;

    int old_level = previous_total / 15;
    int new_level = player.total_planted_crops / 15;

    if (new_level > old_level)
    {
        player.level += (new_level - old_level);
    }
}

void grow_crop(const crop_list &list, farm_data &farm, player_data &player, uint32_t &last_ms)
{
    int index = choose_crop(list);
    if(index < 0) return;

    crop_data chosen = list[index];

    int free_slots = farm.max_capacity - farm.used_capacity;
    if (free_slots <= 0)
    {
        write_line("Your farm is full.");
        return;
    }

    int qty = read_integer("Quantity to grow: ", 1, free_slots);

    int total_cost = chosen.price * qty;

    if (!can_afford(player, total_cost))
    {
        write_line("Insufficient coins.");
        write_line("Required coins: " + to_string(total_cost) + 
            " | Current Coins: " + to_string(player.coin));
        return;
    }

    spend_coins(player, total_cost);

    planted_crop planted;
    planted.crop = chosen;
    planted.quantity = qty;
    planted.time_remaining = chosen.growth_time;

    farm.planted.push_back(planted);
    farm.used_capacity += qty;

    write_line("Planted " + to_string(qty) + " " + chosen.crop_name + 
        "(s). Time to grow: " + to_string(chosen.growth_time) + " seconds.");

    update_player_level(qty, player);

    last_ms = current_ticks();
}

void view_field(const farm_data &farm)
{
    write_line("--- Field Status ---");
    if (farm.planted.size() == 0)
    {
        write_line("No crops planted.");
        return;
    }

    for (int i = 0; i < farm.planted.size(); i++)
    {
        const planted_crop &p = farm.planted[i];
        write_line(to_string(i + 1) + ". " + p.crop.crop_name + 
            " x" + to_string(p.quantity) + " | Time Remaining: " + 
            to_string(p.time_remaining) + "s");
    }
}

void harvest_ready_crops(farm_data &farm, player_data &player)
{
    for (int i = 0; i < farm.planted.size();)
    {
        planted_crop &p = farm.planted[i];

        if(p.time_remaining == 0)
        {
            add_to_inventory(player, p.crop, p.quantity);

            farm.used_capacity -= p.quantity;

            load_game_audio();
            play_sfx("harvest", 1.0);
            delay(300);

            write_line("Harvested " + to_string(p.quantity) + " " + p.crop.crop_name);
            write_line("Added to inventory");

            farm.planted.erase(farm.planted.begin() + i);
        }
        else
        {
            i++;
        }
    }
}

int find_crop_price(const crop_list &list, const string &name)
{
    for (int i = 0; i < list.size(); i++)
    {
        if (to_lower(list[i]. crop_name) == name)
        {
            return list[i].price;
        }
    }
    return -1;
}

void sell_crop(const crop_list &list, player_data &player)
{
    if (player.inventory_head == nullptr)
    {
        write_line("Inventory is empty.");
        write_line("Returning to market..");
        return;
    }

    view_inventory(player);
    string name = read_string("Which crop do you wish to sell? (Type the exact name): ");
    string search_name = to_lower(name);

    inventory_node *cur = player.inventory_head;
    while (cur != nullptr && to_lower(cur->crop_name) != search_name)
    {
        cur = cur->next;
    }
    if (cur == nullptr)
    {
        write_line("Invalid crop.");
        return;
    }

    int price = find_crop_price(list, search_name);
    if (price < 0)
    {
        write_line("Invalid crop (price not found).");
        return;
    }

    int qty = read_integer("Quantity to sell: ", 1, cur->quantity);

    int base = price * qty;
    int earnings = (base * 105) / 100;

    player.coin += earnings;

    string sold_name = cur->crop_name;
    remove_from_inventory(player, sold_name, qty);

    write_line("Sold " + to_string(qty) + " " + sold_name + "(s) for " + to_string(earnings) + " coins.");
    write_line("Coins: " + to_string(player.coin));

    play_sfx("coins");
    delay(300);
}