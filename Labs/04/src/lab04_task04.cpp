#include "lab04_tasks.hpp"

#define START_PARAM_HOUG 30
#define CIRCLES_TO_FIND 1

using namespace cv;
using namespace std;

void task04(string filename)
{
    Mat img = imread(filename), imgGrayscale = imread(filename, IMREAD_GRAYSCALE);
    vector<Vec4f> circles;

    // loop below does a very simple auto tuning of the paramether of the HOUGH_GRADIENT method until the method actually finds a circle
    // First value of the second paramether(which is the one being tuned) is START_PARAM_HOUG
    // Loop stops when it has find CIRCLES_TO_FIND circles
    int i = START_PARAM_HOUG;
    while((i > 0) && (circles.size() < CIRCLES_TO_FIND)) 
    {
        HoughCircles(imgGrayscale, circles, HOUGH_GRADIENT, 1, 5, 300, i, 0, 25);
        i--;

        // DEBUG print value of parameter used to find strongest CIRCLES_TO_FIND circles
        //cout << "iteration n° " << i << endl;   
    }

    cout << "Value of the 2nd parameter that found " << CIRCLES_TO_FIND << " circles: " << i << endl;

    // DEBUG
    // cout << "FOUND "  << circles.size() << " CIRCLES" << endl;

    for (int i = 0; i < circles.size(); i++)
    {
        circle(img, Point(circles[i](0), circles[i](1)), circles[i](2), Scalar(0,0,255), FILLED);
        cout << "radius of circle " << i << " is: " << circles[i](2) << endl;   // prints the radious of the strongest CIRCLES_TO_FIND circles
    }
    
    imshow("CIRCLES", img);
    
    waitKey(0);
}