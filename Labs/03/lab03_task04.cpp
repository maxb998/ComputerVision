#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    Mat img = imread("robocup.jpg");

    imshow("robocup", img);

    Mat flt(img.size(), img.type()), mask = Mat::zeros(img.size(), CV_8UC1);

    // using an average filter in order to get automatically the average values needed
    boxFilter(img,flt,-1,Size(9,9));

    Vec3b T(40,50,60), avg(41,120,150), lowT = avg - T, highT = avg + T;
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

    imshow("flt",flt);
    imshow("Mask", mask);

    waitKey(0);
	return 0;
}
