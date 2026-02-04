#include "monster.h"

monster_data new_monster(string monster_name, int monster_hp, int monster_attack, int reward_coins)
{
    monster_data monster;
    monster.monster_name = monster_name;
    monster.monster_hp = monster_hp;
    monster.monster_attack = monster_attack;
    monster.reward_coins = reward_coins;
    return monster;
}

int rand_range(int min, int max)
{
    return min + rnd(max - min + 1);
}

monster_data spawn_monster(int player_level)
{
    vector<string> names = {"Slime", "Goblin", "Skeleton", "Werewolf"};
    string name = names[rnd(names.size())];

    monster_data monster;
    monster.monster_name = name;
    monster.monster_hp = 20 + player_level * 6 + rnd(11);
    monster.monster_attack = 3 + player_level * 2 + rnd(4);
    monster.reward_coins = 15 + player_level * 10 + rnd(11);

    return monster;
}

int monster_damage(const monster_data &monster)
{
    int min_dmg = (monster.monster_attack * 80) / 100;
    int max_dmg = (monster.monster_attack * 120) / 100;
    return rand_range(min_dmg, max_dmg);
}

int player_damage(const weapon_data &weapon)
{
    int min_dmg = (weapon.base_damage * 80) / 100;
    int max_dmg = (weapon.base_damage * 120) / 100;
    int dmg = rand_range(min_dmg, max_dmg);

    // crit 10%
    if (rand_range(1, 10) == 1) dmg *= 2;

    return dmg;
}