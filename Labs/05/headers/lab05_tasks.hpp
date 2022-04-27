#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <cmath>

#ifndef lab05_task01
#define lab05_task01

    void task01(std::string filename);
    cv::Mat t1_kmeansSegmentCrack(cv::Mat img, const int k, const int medianKSize);
    cv::Mat t1_staticThresholdRegionGrowing(cv::Mat img, const uchar seedThreshold, const uchar growthThreshold, const int medianKSize);
    cv::Mat t1_dynamicThresholdRegionGrowing(cv::Mat img, const uchar seedThreshold, const uchar growthThreshold, const uchar distanceAttenuator, const int medianKSize);
    std::vector<cv::Point> t1_correctNeighbor (int row, int col, int matRows, int matCols);    // returns valid neighborhood of a point(without out of bounds points wrt. the matrix)

#endif

#ifndef lab05_task02
#define lab05_task02

    void task02(std::string filename);
    cv::Mat t2_kmeansSegmentation(cv::Mat img, const int k);
    cv::Mat t2_watershedTechnique(cv::Mat img);

#endif

#ifndef lab05_task03
#define lab05_task03

    void task03(std::string filename);
    cv::Mat t3_kmeansSegmentation(cv::Mat img, const int k);
    //cv::Mat t3_watershedTechnique(cv::Mat img);

#endif