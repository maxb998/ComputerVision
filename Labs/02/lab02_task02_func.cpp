#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "lab02_task02_func.h"


cv::Mat maxFilter(cv::Mat img, int kerWidth, int kerHeigth) 
{
    // Check if the arguments are correct
    if ( kerWidth%2 != 1 || kerHeigth%2 != 1 || kerWidth < 0 || kerHeigth < 0) 
    {
        throw std::invalid_argument( "Incorrect kernel values" );
    }

    // Matrix that will contain the result
    cv::Mat halfFiltered(img.size(), img.type()); 

    // Apply filter with kernel size = (kerHeigth,1)
    for (int row = 0; row < img.rows; row++)
    {
        for (int col = 0; col < img.cols; col++)
        {
            uchar maxVal = 0;
            for (int i = row-(kerHeigth/2); i < row+(kerHeigth/2)+1; i++)
            {
                if ((i >= 0) && (i < img.rows))
                {
                    if(maxVal < img.at<uchar>(i,col))
                    {
                        maxVal = img.at<uchar>(i,col);
                    }
                }
            }
            halfFiltered.at<uchar>(row,col) = maxVal;
        }
    }
    cv::Mat filtered(img.size(), img.type()); 
    // Apply filter with kernel size = (1,kerWidth)
    for (int row = 0; row < halfFiltered.rows; row++)
    {
        for (int col = 0; col < halfFiltered.cols; col++)
        {
            uchar maxVal = 0;
            for (int i = col-(kerWidth/2); i < col+(kerWidth/2)+1; i++)
            {
                if ((i >= 0) && (i < halfFiltered.cols))
                {
                    if(maxVal < halfFiltered.at<uchar>(row,i))
                    {
                        maxVal = halfFiltered.at<uchar>(row,i);
                    }
                }
            }
            filtered.at<uchar>(row,col) = maxVal;
        }
    }
    return filtered;  
}
// squared kernel overload
cv::Mat maxFilter(cv::Mat img, int kerSize) { return maxFilter(img, kerSize, kerSize); }

cv::Mat minFilter(cv::Mat img, int kerWidth, int kerHeigth)
{
    // Check if the arguments are correct
    if ( kerWidth%2 != 1 || kerHeigth%2 != 1 || kerWidth < 0 || kerHeigth < 0) 
    {
        throw std::invalid_argument( "Incorrect kernel values" );
    }

    // Matrix that will contain the result
    cv::Mat halfFiltered(img.size(), img.type()); 

    // Apply filter with kernel size = (kerHeigth,1)
    for (int row = 0; row < img.rows; row++)
    {
        for (int col = 0; col < img.cols; col++)
        {
            uchar minVal = 255;
            for (int i = row-(kerHeigth/2); i < row+(kerHeigth/2)+1; i++)
            {
                if ((i >= 0) && (i < img.rows))
                {
                    if(minVal > img.at<uchar>(i,col))
                    {
                        minVal = img.at<uchar>(i,col);
                    }
                }
            }
            halfFiltered.at<uchar>(row,col) = minVal;
        }
    }
    cv::Mat filtered(img.size(), img.type()); 
    // Apply filter with kernel size = (1,kerWidth)
    for (int row = 0; row < halfFiltered.rows; row++)
    {
        for (int col = 0; col < halfFiltered.cols; col++)
        {
            uchar minVal = 255;
            for (int i = col-(kerWidth/2); i < col+(kerWidth/2)+1; i++)
            {
                if ((i >= 0) && (i < halfFiltered.cols))
                {
                    if(minVal > halfFiltered.at<uchar>(row,i))
                    {
                        minVal = halfFiltered.at<uchar>(row,i);
                    }
                }
            }
            filtered.at<uchar>(row,col) = minVal;
        }
    }
    return filtered; 
}
// squared kernel overload
cv::Mat minFilter(cv::Mat img, int kerSize) { return minFilter(img, kerSize, kerSize); }