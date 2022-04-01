#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "lab02_task03_func.h"

int main(int argc, char** argv)
{
    cv::Mat grayscaleImg = cv::imread(argv[1], cv::IMREAD_GRAYSCALE );

    cv::imshow("PREFILTERED Image", grayscaleImg);

    cv::Mat gauss = gaussianFilter(grayscaleImg,cv::Size(9,9), 100.);
    cv::namedWindow("GAUSS FILTER");
    cv::imshow("GAUSS FILTER", gauss);


    cv::Mat median = medianFilter(grayscaleImg,9);
    cv::namedWindow("MEDIAN FILTER");
    cv::imshow("MEDIAN FILTER", median);

    cv::waitKey(0);
	return 0;
}