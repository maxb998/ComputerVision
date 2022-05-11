#include <iostream>
#include <fstream>
#include <image_stiching.hpp>

using namespace std;

void checkFileExists(string filename);

int main(int argc, char** argv)
{
    // Check whether the input arguments are the right amount
    if (argc != 3)
        throw invalid_argument("Usage: <path>/lab04 \"<PATH & PATTERN>\" <fov>");
    
    // Check if a files path is specified
    string path = string(argv[1]);
    double fov = 0;
    if (isdigit(*argv[2]))
        fov = stod(argv[2]);
    
    // init
    StichImages imgs(path);

    // launch task01
    imgs.cylindricalConversion(fov);

}