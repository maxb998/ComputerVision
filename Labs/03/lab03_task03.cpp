#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void callbackFunction(int event, int x, int y, int flags, void* userdata)
{
    if (event == EVENT_LBUTTONUP)
    {
        Mat img = *(Mat*)userdata;

        cout << "The selected pixel is at position: [" << x << ", " << y << "]" << endl;
        // cicly to get the 9x9 square of pixel around the selected one
        int count = 0;
        int mean[] = {0,0,0};
        for (int i = y-4; i < y+5; i++)
        {
            for (int j = x-4; j < x+5; j++)
            {
                // check if the indexes i and j are within the matrix bounds
                if ((i >= 0) && (i < img.rows) && (j >= 0) && (j < img.cols))
                {
                    count++;
                    for (int k = 0; k < 3; k++)
                        mean[k] += (int)img.at<Vec3b>(i,j)[k];
                }
            }
        }
        for (int k = 0; k < 3; k++)
            mean[k] /= count;
        cout << "mean = [" << mean[0] << "," << mean[1] << "," << mean[2] << "]" << endl;
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
