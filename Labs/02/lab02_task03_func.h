#ifndef lab02_task03_func

#define lab02_task03_func .h

    cv::Mat maxFilter(cv::Mat img, int kerWidth, int kerHeigth);
    cv::Mat maxFilter(cv::Mat img, int kerSize);

    cv::Mat minFilter(cv::Mat img, int kerWidth, int kerHeigth);
    cv::Mat minFilter(cv::Mat img, int kerSize);

    cv::Mat gaussianFilter(cv::Mat img, cv::Size kerSize, double stdDev);

    cv::Mat medianFilter(cv::Mat img, int kerSize);

#endif