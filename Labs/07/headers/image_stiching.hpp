#ifndef IMAGE_STICHING_H
#define IMAGE_STICHING_H

#include <opencv2/core.hpp>

class StichImages
{
private:
    std::vector<cv::Mat> sourceImgs;
    std::vector<cv::Mat> cylindricalImgs;
    std::vector<cv::KeyPoint> detectKeypoints(cv::Mat img);
    void matchKeypoints(std::vector<cv::KeyPoint> keypoints);

public:
    StichImages(std::string pathAndPattern);
    ~StichImages();
    void cylindricalConversion(double FOV);
    cv::Mat generateLandscape();
};

#endif