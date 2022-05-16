#include <iostream>
#include <fstream>
#include <lab08_tasks.hpp>

using namespace std;

void checkFileExists(string filename);

int main(int argc, char** argv)
{
    // Check whether the input arguments are the right amount
    if (argc != 2)
        throw invalid_argument("Usage: <path>/lab04 \"<PATH & PATTERN>\"");
    
    // Check if a files path is specified
    string path = string(argv[1]);

    customCalibrateCamera(path);
}