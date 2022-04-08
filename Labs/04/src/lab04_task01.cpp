#include "lab04_tasks.hpp"

using namespace cv;
using namespace std;

struct cannyData
{
    int highThreshold, lowThreshold;
    Mat originImg, cannyImg;
};

void applyCannyOnSliders(int val, void* userdata)
{
    // Recover passed data
    cannyData i = *(cannyData*) userdata;

    // Apply canny
    Canny(i.originImg, i.cannyImg, (double)i.highThreshold, (double)i.lowThreshold);

    // Show result
    imshow("Canny edges", i.cannyImg);
}

void task01(string filename)
{
    // Init necessary values and read image
    cannyData i;
    i.originImg = imread(filename);
    i.cannyImg = Mat::zeros(i.originImg.size(), CV_8UC1);
    i.highThreshold = 100;
    i.lowThreshold = 100;

    // Show original image
    namedWindow("Street scene");
    imshow("Street scene", i.originImg);

    // Set trackbars
    namedWindow("Canny edges");
    createTrackbar("Threshold 1","Canny edges",&i.highThreshold,750,applyCannyOnSliders, &i);
    createTrackbar("Threshold 2","Canny edges",&i.lowThreshold,750,applyCannyOnSliders, &i);

    applyCannyOnSliders(0, &i);

    waitKey(0);
}