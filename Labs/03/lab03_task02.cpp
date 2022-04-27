#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void callbackFunction(int event, int x, int y, int flags, void* userdata)
{
    if (event == EVENT_LBUTTONUP)
    {
        Mat img = *(Mat*)userdata;
        cout << "BGR color code at ["<<x<<","<<y<<"] is:"<<img.at<Vec3b>(x,y)<<endl;

    }
    
}

int main(int argc, char** argv)
{
    Mat img = imread(argv[1]);

    namedWindow("MAIN", 1);
    imshow("MAIN", img);
    
    setMouseCallback("MAIN", callbackFunction, &img);

    

    waitKey(0);
	return 0;
}
