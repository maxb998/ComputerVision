#include <opencv2/highgui.hpp>

int main(int argc, char** argv)
{
    cv::Mat img = cv::imread("robocup.jpg");

    cv::imshow("Robocup", img);

    cv::waitKey(0);
	return 0;
}