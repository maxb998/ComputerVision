#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void callbackFunction(int event, int x, int y, int flags, void* userdata)
{
    if (event == EVENT_LBUTTONUP)
    {
        Mat img = *(Mat*)userdata;

        Mat flt(img.size(), img.type()), mask = Mat::zeros(img.size(), CV_8UC1);

        // using an average filter in order to get automatically the average values needed
        boxFilter(img,flt,-1,Size(9,9));

        Vec3b T(50,100,100), avg = flt.at<Vec3b>(y,x), lowT, highT;
        // check whether the threshold generates overflow on the uchar values
        for (int i = 0; i < 3; i++)
        {
            int checkLow = (int)avg[i]-(int)T[i], checkHigh = (int)avg[i]+(int)T[i];
            if (checkLow >= 0)
                lowT[i] = (uchar)checkLow;
            else
                lowT[i] = 0;
            if (checkHigh <= 255)
                highT[i] = (uchar)checkHigh;
            else
                highT[i] = 255;
        }

        // Check what pixels are within the threshold and draw them white in the mask
        for (int row = 0; row < img.rows; row++)
        {
            for (int col = 0; col < img.cols; col++)
            {
                Vec3b px = flt.at<Vec3b>(row,col);
                if ((px[0] >= lowT[0]) && (px[1] >= lowT[1]) && (px[2] >= lowT[2]) && (px[0] <= highT[0]) && (px[1] <= highT[1]) && (px[2] <= highT[2]))
                {
                    mask.at<uchar>(row,col) = 255;
                }
            }
        }
        imshow("Mask", mask);

        // The step below could be implemented during mask creation, but they are kept separate for clarity purposes(the mask processing is not mandatory for this step)       
        Mat editedImg = img.clone();
        Vec3b newColor(92,37,201);

        for (int row = 0; row < img.rows; row++)
        {
            for (int col = 0; col < img.cols; col++)
            {
                if (mask.at<uchar>(row,col) == 255)
                {
                    editedImg.at<Vec3b>(row,col) = newColor;
                }
            }
        }
        imshow("Edited robocup", editedImg);
    }
    
}

int main(int argc, char** argv)
{
    Mat img = imread("robocup.jpg");

    namedWindow("MAIN", 1);
    imshow("MAIN", img);
    
    setMouseCallback("MAIN", callbackFunction, &img);

    waitKey(0);
	return 0;
}
