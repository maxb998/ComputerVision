#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

#ifndef lab04_task01
#define lab04_task01

    struct cannyData;
    void applyCannyOnSliders(int val, void* userdata);
    void task01(std::string filename);

#endif

#ifndef lab04_task02
#define lab04_task02

    cv::Mat angleEdgeFlt(cv::Mat img);
    uchar followVerticalLine(cv::Mat &img, int row, int col, int iterNum, float slope, cv::Point first);
    void task02(std::string filename);

#endif