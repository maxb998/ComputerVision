#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//bool visitedPx[img.cols][img.rows];

Mat angleEdgeFlt(Mat img)
{
    Mat enhancedImg = img.clone();
    
    for (int i = 0; i < img.cols; i++)
    {
        for (int j = 0; j < img.rows; j++)
        {
            visitedPx[i][j] = false;
        }
    }
    

    for (int row = 1; row < img.rows-1; row++)
    {
        for (int col = 1; col < img.cols-1; col++)
        {
            
        }
    }
    return enhancedImg;
}

void followLine()
{

}
