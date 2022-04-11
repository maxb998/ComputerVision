#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <cmath>

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
    cv::Mat checkColorsAroundLine(cv::Mat img, cv::Mat lines, uchar color, int neighborhoodSize);
    void task02(std::string filename);

#endif

#ifndef lab04_task02_Slope
#define lab04_task02_Slope

    class Slope
    {
    private:
        cv::Point *first, *last;
        float val;
        bool XoverY;
    public:
        Slope(cv::Point firstPoint);
        void setLast(cv::Point lastPoint);
        float value();
        int getLastX();
        int getLastY();
        bool isXoverY();
    };

#endif