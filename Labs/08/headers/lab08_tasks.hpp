#ifndef LAB08_TASKS_H
#define LAB08_TASKS_H

#include <opencv2/core.hpp>

void customCalibrateCamera(std::string pathPattern);
std::vector<cv::Mat> loadImgs(std::string pathAndPattern);
void drawCornersOnChess(std::vector<cv::Mat> originChess, std::vector<cv::Mat> corners, std::vector<bool> pattFound, cv::Size s);

#endif