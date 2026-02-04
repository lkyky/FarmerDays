#include "player.h"

player_data new_player(string player_name, int level, int coin, int hp)
{
    player_data player;
    player.player_name = player_name;
    player.level = level;
    player.coin = coin;
    player.hp = hp;
    return player;
}

weapon_data new_weapon(string weapon_name, int weapon_level, int base_damage, int upgrade_cost)
{
    weapon_data weapon;
    weapon.weapon_name = weapon_name;
    weapon.weapon_level = weapon_level;
    weapon.base_damage = base_damage;
    weapon.upgrade_cost = upgrade_cost;
    return weapon;
}

void add_to_inventory(player_data &player, const crop_data &crop, int qty)
{
    inventory_node *cur = player.inventory_head;
    while (cur != nullptr)
    {
        if (cur->crop_name == crop.crop_name)
        {
            cur->quantity += qty;
            return;
        }
        cur = cur->next;
    }

    inventory_node *node = new inventory_node;
    node->crop_name = crop.crop_name;
    node->quantity = qty;
    node->next = player.inventory_head;
    player.inventory_head = node;
}

bool remove_from_inventory(player_data &player, const string &crop_name, int qty)
{
    if (qty  <= 0)
    {
        return false;
    }

    inventory_node *cur = player.inventory_head;
    inventory_node *prev = nullptr;

    while (cur != nullptr)
    {
        if (cur->crop_name == crop_name)
        {
            if (qty > cur->quantity)
            {
                write_line("Insufficient crop to remove.");
                return false;
            }
            cur->quantity -= qty;

            if (cur->quantity == 0)
            {
                if (prev == nullptr)
                {
                    player.inventory_head = cur->next;
                }
                else
                {
                    prev->next = cur->next;
                }
                delete cur;
            }
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    write_line("Crop not found.");
    return false;
}

void view_inventory(const player_data &player)
{
    write_line("--- Inventory ---");

    inventory_node *cur = player.inventory_head;
    if (cur == nullptr)
    {
        write_line("Empty");
        return;
    }

    while (cur != nullptr)
    {
        write_line(cur->crop_name + " x" + to_string(cur->quantity));
        cur = cur->next;
    }
}

bool can_afford(const player_data &player, int cost)
{
    return player.coin >= cost;
}

void spend_coins(player_data &player, int cost)
{
    play_sfx("coins", 1.0);
    player.coin -= cost;
    if (player.coin < 0)
    {
        player.coin = 0;
    }
}