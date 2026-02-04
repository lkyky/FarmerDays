#ifndef HIGHSCORE_H
#define HIGHSCORE_H
#include "splashkit.h"
#include "player.h"

#include <sstream>
using std::stringstream;
#include <fstream>
using std::ifstream;
using std::ofstream;
#include <algorithm>
using std::sort;

/**
 * Highscore entry
 * 
 * @field name Player's name.
 * @field score Player's highest score.
 * @field level Player's highest level.
 * @field coins Player's coin.
 * @field total_planted_crops The total number of crops planted from the player.
 */
struct highscore_entry
{
    string name;
    int score;
    int level;
    int coins;
    int total_planted_crops;
};

/**
 * Calculates the player's score based on current statistics.
 * 
 * @param player The player's data.
 * 
 * @return The calculated score.
 */
int calculate_score(const player_data &player);

/**
 * Loads high scores from csv file
 * 
 * @param filename The name of the csv file.
 * 
 * @return A vector containing all successfully parsed high score entries.
 */
vector<highscore_entry> load_highscore(string &filename);

/**
 * Save the high score to the csv file
 * 
 * @param filename The name of the csv file.
 * @param scores The highscores recorded.
 */
void save_highscore(const string &filename, const vector<highscore_entry> &scores);

/**
 * Record a player's highscore in the csv file.
 * 
 * @param filename The name of the csv file.
 * @param player The player's data.
 * @param max Maximum number of entries allowed on the leaderboard.
 * 
 * @return true if the player appears on the final leaderboard.
 */
bool record_highscore(const string &filename, const player_data &player, int max = 10);

/**
 * Show the available highscores when called.
 * 
 * @param filename The name of the csv file.
 * @param max Maximum number of entries allowed on the leaderboard.
 */
void show_highscore(const string &filename, int max = 10);

#endif