#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
using std::string;

#include "audio.h"

/**
 * Read a string from the user
 * 
 * @param prompt the message to show the user
 * @returns the string entered at the terminal
 */
string read_string(string prompt);

/**
 * Read an integer from the user
 * 
 * @param prompt the message to show the user
 * @returns the integer entered
 */
int read_integer(string prompt);

/**
 * Read an integer from the user within a range
 * 
 * @param prompt the message to show the user
 * @param low An integer representing the smallest value to return
 * @param high An integer representing the largest value to return
 * @returns the integer entered
 */
int read_integer(string prompt, int low, int high);

/**
 * Read a double from the user
 * 
 * @param prompt the message to show the user
 * @returns the double entered
 */
double read_double(string prompt);

/**
 * Converts a string to lowercase.
 * 
 * @param converted The string to convert to lowercase.
 * 
 * @return A new string containing the converted lowercase version.
 */
string to_lower(const string &converted);

#endif