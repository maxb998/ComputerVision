#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <cmath>

#ifndef lab05_task01
#define lab05_task01

    void task01(std::string filename);
    cv::Mat kmeansSegmentation(cv::Mat img, const int k, const int medianKSize);
    cv::Mat kmeansSegmentCrack(cv::Mat img, const int k, const int medianKSize);
    cv::Mat staticThresholdRegionGrowing(cv::Mat img, const uchar seedThreshold, const uchar growthThreshold, const int medianKSize);
    cv::Mat dynamicThresholdRegionGrowing(cv::Mat img, const uchar seedThreshold, const uchar growthThreshold, const uchar distanceAttenuator, const int medianKSize);
    std::vector<cv::Point> correctNeighbor (int row, int col, int matRows, int matCols);    // returns valid neighborhood of a point(without out of bounds points wrt. the matrix)

#endif