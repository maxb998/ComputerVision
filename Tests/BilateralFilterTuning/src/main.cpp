#include <iostream>
#include <fstream>
#include <tunableBilateral.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    // Check whether the input arguments are the right amount
    if (argc != 2)
        throw invalid_argument("Usage: <path>/bilTune <images pattern>");
    
    viewDemoRoulette(string(argv[1]));
    
}