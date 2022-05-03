#include <iostream>
#include <fstream>
#include <image_stiching.hpp>

using namespace std;

void checkFileExists(string filename);

int main(int argc, char** argv)
{
    // Check whether the input arguments are the right amount
    if (argc != 2)
        throw invalid_argument("Usage: <path>/lab04 \"<PATH & PATTERN>\"");
    
    // Check if a files path is specified, otherwise tries to take the image in the default location
    string path = string(argv[1]);

    StichImages imgs(path);

    // launch task01
    

}