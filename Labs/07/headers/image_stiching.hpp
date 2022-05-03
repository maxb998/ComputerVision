#ifndef IMAGE_STICHING_H
#define IMAGE_STICHING_H

#include <opencv2/core.hpp>

class StichImages
{
private:
    std::vector<cv::Mat> sourceImgs;

public:
    StichImages(std::string pathAndPattern);
    ~StichImages();
};

#endif