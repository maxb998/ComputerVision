#include "lab06_tasks.hpp"

using namespace cv;
using namespace std;

void task01(string filename1, string filename2)
{
    Mat img1 = imread(filename1), img2 = imread(filename2);
    
    BFMatcher * bfm = BFMatcher::create();
    

    waitKey(0);
}