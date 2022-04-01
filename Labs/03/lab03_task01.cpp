#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    Mat img = cv::imread("robocup.jpg");

    imshow("Robocup", img);

    waitKey(0);
	return 0;
}