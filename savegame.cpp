#include "savegame.h"

static bool parse_player_line(const string &line, player_data &player, weapon_data &weapon)
{
    stringstream ss(line);
    string token;

    if (!getline(ss, player.player_name, ',')) return false;

    if (!getline(ss, token, ',')) return false;
    player.level = stoi(token);

    if (!getline(ss, token, ',')) return false;
    player.coin = stoi(token);

    if (!getline(ss, token, ',')) return false;
    player.hp = stoi(token);

    if (!getline(ss, token, ',')) return false;
    player.total_planted_crops = stoi(token);

    if (!getline(ss, weapon.weapon_name, ',')) return false;

    if (!getline(ss, token, ',')) return false;
    weapon.weapon_level = stoi(token);

    if (!getline(ss, token, ',')) return false;
    weapon.base_damage = stoi(token);

    if (!getline(ss, token)) return false;
    weapon.upgrade_cost = stoi(token);

    player.inventory_head = nullptr;
    return true;
}

bool load_player_from_csv(const string &filename, const string &name, player_data &out_player, weapon_data &out_weapon)
{
    ifstream in(filename);
    if (!in.is_open()) return false;

    string line;
    bool first = true;
    string target = to_lower(name);

    while(getline(in, line))
    {
        if (line.empty()) continue;

        if (first)
        {
            first = false;
            if (line.find("name,level") != string::npos) continue;
        }

        player_data temp;
        weapon_data temp_w;
        if (!parse_player_line(line, temp, temp_w)) continue;

        if (to_lower(temp.player_name) == target)
        {
            out_player = temp;
            out_weapon = temp_w;
            return true;
        }
    }
    return false;
}

void save_player_to_csv(const string &filename, const player_data &player, const weapon_data &weapon)
{
    struct save_record
    {
        player_data p;
        weapon_data w;
    };

    vector<save_record> all;

    {
        ifstream in(filename);
        string line;
        bool first = true;

        while (in.is_open() && getline(in, line))
        {
            if (line.empty()) continue;

            if (first)
            {
                first = false;
                if (line.find("name,level") != string::npos) continue;
            }

            save_record rec;

            if (parse_player_line(line, rec.p, rec.w))
                all.push_back(rec);
        }
    }

    string target = to_lower(player.player_name);
    bool updated = false;

    for (int i = 0; i < (int)all.size(); i++)
    {
        if (to_lower(all[i].p.player_name) == target)
        {
            all[i].p.player_name = player.player_name;
            all[i].p.level = player.level;
            all[i].p.coin = player.coin;
            all[i].p.hp = player.hp;
            all[i].p.total_planted_crops = player.total_planted_crops;

            all[i].w.weapon_name = weapon.weapon_name;
            all[i].w.weapon_level = weapon.weapon_level;
            all[i].w.base_damage = weapon.base_damage;
            all[i].w.upgrade_cost = weapon.upgrade_cost;

            updated = true;
            break;
        }
    }

    if (!updated)
    {
        save_record rec;
        rec.p = player;
        rec.w = weapon;
        all.push_back(rec);
    }

    ofstream out(filename);
    out << "name,level,coins,hp,total_planted_crops,weapon_name,weapon_level,weapon_damage,weapon_upgrade_cost\n";

    for (int i = 0; i < (int)all.size(); i++)
    {
        const save_record &rec = all[i];

        out << rec.p.player_name << ","
            << rec.p.level << ","
            << rec.p.coin << ","
            << rec.p.hp << ","
            << rec.p.total_planted_crops << ","
            << rec.w.weapon_name << ","
            << rec.w.weapon_level << ","
            << rec.w.base_damage << ","
            << rec.w.upgrade_cost << "\n";
    }
}

bool load_inventory_from_csv(const string &filename, const string &player_name, player_data &player)
{
    ifstream in(filename);
    if (!in.is_open()) return false;

    string line;
    bool first = true;
    string target = to_lower(player_name);

    bool loaded_any = false;

    while (getline(in, line))
    {
        if (line.empty()) continue;

        if (first)
        {
            first = false;
            if (line.find("name,crop_name") != string::npos) continue;
        }

        stringstream ss(line);
        string name, crop, token;

        if (!getline(ss, name, ',')) continue;
        if (!getline(ss, crop, ',')) continue;
        if (!getline(ss, token)) continue;

        if (to_lower(name) != target) continue;

        int qty = stoi(token);

        crop_data temp;
        temp.crop_name = crop;

        add_to_inventory(player, temp, qty);
        loaded_any = true;
    }
    return loaded_any;
}

void save_inventory_to_csv(const string &filename, const player_data &player)
{
    struct inv_row
    {
        string name;
        string crop;
        int qty;
    };

    vector<inv_row> rows;

    {
        ifstream in(filename);
        string line;
        bool first = true;

        while (in.is_open() && getline(in, line))
        {
            if (line.empty()) continue;

            if (first)
            {
                first = false;
                if (line.find("name,crop_name") != string::npos) continue;
            }

            stringstream ss(line);
            inv_row r;
            string token;

            if (!getline(ss, r.name, ',')) continue;
            if (!getline(ss, r.crop, ',')) continue;
            if (!getline(ss, token)) continue;

            r.qty = stoi(token);
            rows.push_back(r);
        }
    }

    string target = to_lower(player.player_name);

    ofstream out(filename);
    out << "name,crop_name,quantity\n";

    for (int i = 0; i < (int)rows.size(); i++)
    {
        if (to_lower(rows[i].name) == target) continue;

        out << rows[i].name << ","
            << rows[i].crop << ","
            << rows[i].qty << "\n";
    }

    inventory_node *cur = player.inventory_head;
    while (cur != nullptr)
    {
        out << player.player_name << ","
            << cur->crop_name << ","
            << cur->quantity << "\n";

        cur = cur->next;
    }
}