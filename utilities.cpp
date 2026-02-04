#include "splashkit.h"
#include "utilities.h"

using std::to_string;
using std::stoi;
using std::stod;

string read_string(string prompt)
{
    play_sfx("click", 0.7);
    write(prompt);
    return read_line();
}

int read_integer(string prompt)
{
    play_sfx("click", 0.7);
    string input = read_string(prompt);
    while(!is_integer(input))
    {
        write_line("Please enter a whole number.");
        input = read_string(prompt);
    }
    return stoi(input);
}

int read_integer(string prompt, int low, int high)
{
    play_sfx("click", 0.7);
    int input = read_integer(prompt);
    while(input < low || input > high)
    {
        write_line("Please enter a value between " + to_string(low) + " - " + to_string(high));
        input = read_integer(prompt);
    }
    return input;
}

double read_double(string prompt)
{
    play_sfx("click", 0.7);
    string input = read_string(prompt);
    while(!is_double(input))
    {
        write_line("Please enter a number.");
        input = read_string(prompt);
    }
    return stod(input);
}

string to_lower(const string &converted)
{
    string result = converted;
    for (int i = 0; i < result.length(); ++i)
    {
        result[i] = tolower(static_cast<unsigned char>(result[i]));
    }
    return result;
}