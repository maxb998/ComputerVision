#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main(int argc, char** argv)
{
    cv::Mat colorImg = cv::imread(argv[1]);
    cv::imshow("Colored Image", colorImg);

    cv::Mat grayscaleImg;
    cv::cvtColor(colorImg, grayscaleImg, cv::COLOR_BGR2GRAY);

    cv:imshow("Grayscale Image", grayscaleImg);

    cv::imwrite("grayscale.jpg", grayscaleImg);
    cv::waitKey(0);

	return 0;
}