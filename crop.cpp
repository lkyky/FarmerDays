#include "crop.h"

crop_data new_crop(string name, int growth_time, int price)
{
    crop_data crop;
    crop.crop_name = name;
    crop.growth_time = growth_time;
    crop.price = price;
    return crop;
}

static void ensure_crops_csv_exist(const string &filename)
{
    ifstream in(filename);
    if (in.is_open()) return;

    ofstream out(filename);
    if (!out.is_open()) return;

    out << "name,growth_time,price\n";
}

void init_crop_list(crop_list &list)
{
    list.clear();

    list.push_back({"Carrot", 30, 5});
    list.push_back({"Corn", 50, 8});
    list.push_back({"Lettuce", 20, 4});
    list.push_back({"Mint", 10, 6});
    list.push_back({"Tomato", 40, 7});
    list.push_back({"Wheat", 60, 10});
}

int choose_crop(const crop_list &list)
{
    if (list.size() == 0)
    {
        write_line("No crops available.");
        return -1;
    }

    write_line("\nWhich crop would you like to grow? ");

    for (int i = 0; i < list.size(); i++)
    {
        write_line(to_string(i + 1) + ". " + list[i].crop_name + " | " + to_string(list[i].price) + " coins");
    }

    return read_integer("Crop Choice: ", 1, (int)list.size()) - 1;
}

void load_crops_from_csv(const string &filename, crop_list &list)
{
    list.clear();

    ifstream in(filename);
    if (!in.is_open()) return;

    string line;
    bool first = true;

    while (getline(in, line))
    {
        if (line.empty()) continue;

        if (first)
        {
            first = false;
            if (line.find("name,growth_time") != string::npos) continue;
        }

        stringstream ss(line);
        crop_data c;
        string token;

        if (!getline(ss, c.crop_name, ',')) continue;

        if (!getline(ss, token, ',')) continue;
        c.growth_time = stoi(token);

        if (!getline(ss, token)) continue;
        c.price = stoi(token);

        bool exists = false;
        for (int i = 0; i < (int)list.size(); i++)
        {
            if (to_lower(list[i].crop_name) == to_lower(c.crop_name))
            {
                exists = true;
                break;
            }
        }
        if (!exists)
            list.push_back(c);
    }
}

void save_crops_to_csv(const string &filename, const crop_data &crop)
{
    ensure_crops_csv_exist(filename);

    ofstream out(filename, ios::app);
    if (!out.is_open()) return;

    out << crop.crop_name << ","
        << crop.growth_time << ","
        << crop.price << "\n";
}

void add_new_crop(crop_list &list)
{
    crop_data new_crop;
    new_crop.crop_name = read_string("New crop name: ");
    for (int i = 0; i < (int)list.size(); i++)
    {
        if (to_lower(list[i].crop_name) == to_lower(new_crop.crop_name))
        {
            write_line(new_crop.crop_name + " already exists.");
            return;        
        }
    }
    new_crop.growth_time = read_integer("Growth time (seconds): ");
    new_crop.price = read_integer("Price: ");

    list.push_back(new_crop);
    save_crops_to_csv("crops.csv", new_crop);

    write_line("Crop added successfully!");
}
