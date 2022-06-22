#ifndef TUNABLE_BILATERAL
#define TUNABLE_BILATERAL

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

struct tunableBilateral
{
    double sigmaColor, sigmaSpace;
    int n, intSC, intSP, kSize;
    cv::Mat original, filtered;
    const char *windowName = "Bilateral Tunable";
};

void viewDemoRoulette(std::string pattern);
tunableBilateral viewDemo(std::string filename);
void applyFilterOnSliders(int val, void *userdata);



#endif //TUNABLE_BILATERAL