#ifndef CROP_H
#define CROP_H
#include "splashkit.h"
#include "utilities.h"
#include <vector>

#include <sstream>
using std::stringstream;
#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

/**
 * The crop's data.
 * 
 * @field crop_name The crop's name.
 * @field growth_time The time needed to grow the crop. (sec)
 * @field price The price cost for the crop. (coin)
 */
struct crop_data
{
    string crop_name;
    int growth_time, price;
};

using crop_list = std::vector<crop_data>;

/**
 * The initial available list of crops that can be grown.
 * 
 * @option Carrot
 * @option Corn
 * @option Lettuce
 * @option Mint
 * @option Tomato
 * @option Wheat
 */
void init_crop_list(crop_list &list);

/**
 * Choose crop from the list to grow.
 * 
 * @param list The lists of currently available crops.
 */
int choose_crop(const crop_list &list);

/**
 * Add other new crop to the list.
 * 
 * @param list The list of currently available crops.
 */
void add_new_crop(crop_list &list);

/**
 * Load crop list from csv file.
 * 
 * @param filename The name of the csv file.
 * @param list The list of currently available crops.
 */
void load_crops_from_csv(const string &filename, crop_list &list);

/**
 * Save latest crop to csv file.
 * 
 * @param filename The name of the csv file.
 * @param crop The information of crops.
 */
void save_crops_to_csv(const string &filename, const crop_data &crop);

#endif