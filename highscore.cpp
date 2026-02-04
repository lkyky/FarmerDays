#include "highscore.h"

int calculate_score(const player_data &player)
{
    return player.coin + (player.level * 200) + (player.total_planted_crops * 5);
}

static bool parse_csv_line(const string &line, highscore_entry &entry)
{
    stringstream ss(line);
    string token;

    if (!getline(ss, entry.name, ','))
        return false;

    if (!getline(ss, token, ','))
        return false;
    entry.score = stoi(token);

    if (!getline(ss, token, ','))
        return false;
    entry.level = stoi(token);

    if (!getline(ss, token, ','))
        return false;
    entry.coins = stoi(token);

    if (!getline(ss, token, ','))
        return false;
    entry.total_planted_crops = stoi(token);

    return true;
}

vector<highscore_entry> load_highscore(const string &filename)
{
    vector<highscore_entry> scores;
    ifstream in(filename);

    if (!in.is_open())
        return scores;

    string line;
    bool first_line = true;

    while (getline(in, line))
    {
        if (line.empty())
            continue;

        if (first_line)
        {
            first_line = false;
            if (line.find("name,score") != string::npos)
                continue;
        }

        highscore_entry entry;
        if (parse_csv_line(line, entry))
            scores.push_back(entry);
    }

    return scores;
}

void save_highscore(const string &filename, const vector<highscore_entry> &scores)
{
    ofstream out(filename);

    if (!out.is_open())
        return;

    out << "name,score,level,coins,total_planted_crops\n";

    for (int i = 0; i < scores.size(); i++)
    {
        const highscore_entry &entry = scores[i];

        out << entry.name << ","
            << entry.score << ","
            << entry.level << ","
            << entry.coins << ","
            << entry.total_planted_crops << "\n";
    }
}

bool record_highscore(const string &filename, const player_data &player, int max)
{
    if (player.level == 1 && player.coin == 500 && player.total_planted_crops == 0)
    {
        return false;
    }
    
    vector<highscore_entry> scores = load_highscore(filename);

    int new_score = calculate_score(player);
    string player_name_lower = to_lower(player.player_name);

    int existing_index = -1;
    for (int i = 0; i < (int)scores.size(); i++)
    {
        if (to_lower(scores[i].name) == player_name_lower)
        {
            existing_index = i;
            break;
        }
    }

    int recorded_score = new_score;

    if (existing_index != -1)
    {
        if (new_score > scores[existing_index].score)
        {
            scores[existing_index].score = new_score;
            scores[existing_index].level = player.level;
            scores[existing_index].coins = player.coin;
            scores[existing_index].total_planted_crops = player.total_planted_crops;
        }
        else
        {
            recorded_score = scores[existing_index].score;
        }
    }
    else
    {
        highscore_entry entry;
        entry.name = player.player_name;
        entry.level = player.level;
        entry.coins = player.coin;
        entry.total_planted_crops = player.total_planted_crops;
        entry.score = new_score;

        scores.push_back(entry);
    }

    sort(scores.begin(), scores.end(),
        [](const highscore_entry &a, const highscore_entry &b)
        {
            return a.score > b.score;
        });

    if ((int)scores.size() > max)
        scores.resize(max);

    bool made_leaderboard = false;
        for (int i = 0; i < (int)scores.size(); i++)
        {
            if (to_lower(scores[i].name) == player_name_lower && scores[i].score == recorded_score)
            {
                made_leaderboard = true;
                break;
            }
        }

    save_highscore(filename, scores);
    return made_leaderboard;
}

void show_highscore(const string &filename, int max)
{
    auto scores = load_highscore(filename);

    if (scores.empty())
    {
        write_line("=== Leaderboard ===");
        write_line("No high scores yet.");
        return;
    }

    sort(scores.begin(), scores.end(),
        [](const highscore_entry &a, const highscore_entry &b)
        {
            return a.score > b.score;
        });

    if ((int)scores.size() > max)
        scores.resize(max);

    write_line("=== Leaderboard (Top " + to_string(max) + ") ===");
    for (int i = 0; i < (int)scores.size(); i++)
    {
        const auto &entry = scores[i];
        write_line(to_string(i + 1) + ". " + entry.name +
            " | Score: " + to_string(entry.score) + 
            " | Level: " + to_string(entry.level) +
            " | Coins: " + to_string(entry.coins) +
            " | Crops: " + to_string(entry.total_planted_crops));
    }
}