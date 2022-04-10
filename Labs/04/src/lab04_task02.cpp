#include "lab04_tasks.hpp"

#define MIN_LINE_LENGTH 10

using namespace cv;
using namespace std;

uchar followVerticalLine(Mat &img, int row, int col, int iterNum, float slope, Point first)
{
    int nextRow = row + 1;  // move to row below

    if (nextRow < img.rows) // check if nextRow is still in the image
    {
        int colPriorityOrder[3] = {-1, -1, -1}; // -1 means that one checked it won't even consider the column

        if (slope > 0.5)        // between 22.5° and 45° angle line
        {
            colPriorityOrder[0] = col+1;
            colPriorityOrder[1] = col;
        }
        else if (slope < -0.5)   // between -45° and -22.5° angle line
        {
            colPriorityOrder[0] = col-1;
            colPriorityOrder[1] = col;
        }
        else                    // between -22.5° and 22.5° angle line
        {
            colPriorityOrder[0] = col;
            colPriorityOrder[1] = col-1;
            colPriorityOrder[2] = col+1;
        }

        for (int i = 0; i < 3; i++)
        {
            if ((colPriorityOrder[i] > -1) && (colPriorityOrder[i] < img.cols))
            {
                if (img.at<uchar>(nextRow, colPriorityOrder[i]) == 255) // check if the selected pixel is part of an edge
                {
                    float newSlope = (float)(colPriorityOrder[i]-first.x)/(float)(nextRow-first.y); // slope calculation

                    uchar newColor = followVerticalLine(img, nextRow, colPriorityOrder[i], iterNum+1, newSlope, first); // recursive call

                    img.at<uchar>(nextRow, colPriorityOrder[i]) = newColor; // color set

                    return newColor;
                }
            }
        }
    }

    // if this point is reached, either there are no more pixel to check because the algorithm reached the end of the image
    // or the line is over.
    // so the function returns 240 if the line is long enough or it returns 15 if the line is too short
    // the reason behind the choice of the values lies in the binary value of the code:
    //      0  => 00000000
    //      15 => 00001111
    //      240=> 11110000
    //      255=> 11111111
    // it just feels better for no reason

    if (iterNum > MIN_LINE_LENGTH)
        return (uchar)240;  // the line is valid
    else
        return (uchar)15;   // line to short
}

Mat myFindStraightlines(Mat img) // had to specify it was mine because there is one with the same name in openCV Mat
{
    Mat enhancedImg = img.clone();
    
    for (int row = 0; row < img.rows; row++)
    {
        for (int col = 0; col < img.cols; col++)
        {
            if (enhancedImg.at<uchar>(row,col) == 255)
            {
                enhancedImg.at<uchar>(row,col) = followVerticalLine(enhancedImg, row, col, 0, 0., Point(col,row));
            }
        }
    }


    return enhancedImg;
}

void task02(string filename)
{
    // Load img and apply canny
    Mat img = imread(filename), cannyImg = Mat::zeros(img.size(), CV_8UC1);
    Canny(img, cannyImg, 500, 410);

    Mat newImg = myFindStraightlines(cannyImg);
    
    imshow("Canny Image", cannyImg);
    imshow("Processed Image", newImg);
    
    waitKey(0);
}