#include <iostream>
#include <fstream>
#include "lab05_tasks.hpp"

using namespace std;

int main(int argc, char** argv)
{
    // Check whether the input arguments are the right amount
    if (argc != 3)
    {
        throw invalid_argument("Usage: <path>/lab04 <task n°> <image path>");
    }
    
    // Check if a file path is specified, otherwise tries to take the image in the default location
    FILE *file;
    string filename = string(argv[2]);
    
    if (!(file = fopen(argv[2], "r")))
        throw invalid_argument(filename + " not found"); 
    fclose(file);

    // Check whether the task n° is an integer, if it isn't than exception is thrown within the switch-case below
    int task = 0;
    if (isdigit(*argv[1]))
        task = stoi(argv[1]);
    
    switch (task)
    {
    case 1:
        task01(filename);
        break;

    case 2:
        task02(filename);
        break;

    case 3:
        task03(filename);
        break;
    
    default:
        throw invalid_argument("Task n° must be an integer between 1 and 4");
        break;
    }
}