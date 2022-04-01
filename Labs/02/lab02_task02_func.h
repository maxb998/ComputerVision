#ifndef lab02_task02_func

#define lab02_task02_func .h

    cv::Mat maxFilter(cv::Mat img, int kerWidth, int kerHeigth);
    cv::Mat maxFilter(cv::Mat img, int kerSize);

    cv::Mat minFilter(cv::Mat img, int kerWidth, int kerHeigth);
    cv::Mat minFilter(cv::Mat img, int kerSize);

#endif