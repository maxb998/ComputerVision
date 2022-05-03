#include <iostream>
#include <fstream>
#include <image_stiching.hpp>

using namespace std;

void checkFileExists(string filename);

int main(int argc, char** argv)
{
    // Check whether the input arguments are the right amount
    if (argc != 3)
        throw invalid_argument("Usage: <path>/lab04 <task n°> <(OPTIONAL)image path>");
    
    // Check if a files path is specified, otherwise tries to take the image in the default location
    string imgPath1 = string(argv[1]), imgPath2 = string(argv[2]);
    checkFileExists(imgPath1);
    checkFileExists(imgPath2);

    // launch task01
    

}

void checkFileExists(string filename)
{
    FILE *file;
    
    if (!(file = fopen(filename.c_str(), "r")))
        throw invalid_argument(filename + " not found"); 
    fclose(file);
}