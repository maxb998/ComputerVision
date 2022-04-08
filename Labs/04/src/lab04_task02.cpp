#include "lab04_tasks.hpp"

using namespace cv;
using namespace std;

Mat myFindStraightlines(Mat img) // had to specify it was mine because there is one with the same name in openCV Mat
{
    Mat enhancedImg = Mat::zeros(img.size(), CV_8UC1);
    
    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            if (enhancedImg.at<uchar>(i,j) == 255)
            {
                followLine(enhancedImg, i, j);
            }
        }
    }
    
    
    return enhancedImg;
}

void followLine(Mat &img, int row, int col)
{
    
}

void task02(string filename)
{
    // Load img and apply canny
    Mat img = imread(filename), cannyImg = Mat::zeros(img.size(), CV_8UC1);
    Canny(img, cannyImg, 540, 410);


}