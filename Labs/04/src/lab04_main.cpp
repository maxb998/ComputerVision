#include <iostream>
#include <fstream>
#include "lab04_tasks.hpp"

using namespace std;

int main(int argc, char** argv)
{
    // Check whether the input arguments are the right amount
    if (argc != 3)
        throw invalid_argument("Usage: <path>/lab04 <image path> <task n°>");

    // Check whether the file in argv[1] actually exists
    FILE *file;
    string filename(argv[1]);
    if (!(file = fopen(argv[1], "r")))
        throw invalid_argument(filename + " not found");
    fclose(file);

    // Check whether the task n° is an integer, if it isn't than exception is thrown within the switch-case below
    int task = 0;
    if (isdigit(*argv[2]))
        task = stoi(argv[2]);
    
    switch (task)
    {
    case 1:
        task01(filename);
        break;

    case 2:
        break;

    case 3:
        break;

    case 4:
        break;
    
    default:
        throw invalid_argument("Task n° must be an integer between 1 and 4");
        break;
    }
}