#ifndef HAND_SEGMENTATION_SUPPORT
#define HAND_SEGMENTATION_SUPPORT

#include <opencv2/core.hpp>

class handSegmentationSupport
{
private:
    bool imgsLoaded, handBoxesLoaded, trueMasksLoaded;
    std::vector<cv::Mat> imgs, trueMasks;
    std::vector<std::vector<cv::Rect2i>> handBoxes;
public:
    handSegmentationSupport();
    ~handSegmentationSupport();

    int loadImgsWithGlob(char *pattern);
    int loadHandBoxesCoordsWithGlob(char *pattern);
    int loadTrueSegmentationMask(char *pattern);

    void showImgsWithLocalizedHands();
    void showImgsWithTrueMasksSeg();
    cv::Mat segmentImgWithTrueMask(int imgID);

    void showImgsWithSpecifiedMasks(std::vector<cv::Mat> masks);
    cv::Mat segmentImgWithSpecifiedMask(int imgID, cv::Mat mask);
};




#endif // HAND_SEGMENTATION_SUPPORT