#include <opencv2/highgui.hpp>
#include <filesystem>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    //filesystem::path p = 
    Mat img = cv::imread("robocup.jpg");

    imshow("Robocup", img);

    waitKey(0);
	return 0;
}