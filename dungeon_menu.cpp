#include "dungeon_menu.h"

int read_combat_choice()
{
    write_line("1. Attack");
    write_line("2. Defend");
    write_line("3. Run");
    return read_integer("Choice: ", 1, 3);
}

void fight_monster(player_data &player, weapon_data &weapon, bool &died_broke)
{
    const int DEATH_PENALTY = 100;
    monster_data monster = spawn_monster(player.level);
    write_line("A " + monster.monster_name + " appeared!");

    while(monster.monster_hp > 0 && player.hp > 0)
    {
        write_line("\nBattle Starts!");
        write_line(player.player_name + "'s HP: " + to_string(player.hp));
        write_line(monster.monster_name + "'s HP: " + to_string(monster.monster_hp));

        int choice = read_combat_choice();

        if (choice == 3)
        {
            if (rand_range(1, 10) <= 7)
            {
                write_line("You escaped!");
                write_line("Teleporting back to home..");
                return;
            }
            else
            {
                write_line("Failed to escape!");
            }
        }
        
        bool defended = (choice == 2);

        if (choice == 1)
        {
            int dmg = player_damage(weapon);
            monster.monster_hp -= dmg;
            if (monster.monster_hp < 0)
            {
                monster.monster_hp = 0;
            }
            write_line("You dealt " + to_string(dmg) + " damage!");
        }
        else if (choice == 2)
        {
            write_line("You defended!");
        }
        
        if (monster.monster_hp > 0)
        {
            int mdmg = monster_damage(monster);
            if (defended)
            {
                mdmg /= 2;
            }
            player.hp -= mdmg;
            
            if (player.hp < 0)
            {
                player.hp = 0;
            }
            write_line(monster.monster_name + " dealt " + to_string(mdmg) + " damage!");
        }

            if (player.hp == 0)
            {
                play_sfx("defeated", 1.0);
                write_line("You were defeated.. Teleporting back to home..");
                if (!can_afford(player, DEATH_PENALTY))
                {
                    player.coin = 0;
                    write_line("Game Over :<");
                    write_line("See you again");
                    died_broke = true;
                    return;
                }

                spend_coins(player, DEATH_PENALTY);
                write_line("You lost " + to_string(DEATH_PENALTY) + " coins!");
            }
    }

    if (monster.monster_hp == 0)
    {
        play_sfx("won", 1.0);
        write_line("You defeated the " + monster.monster_name + "!");
        player.coin += monster.reward_coins;
        write_line("You gained " + to_string(monster.reward_coins) + " coins!");
    }
}
