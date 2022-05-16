#include <opencv2/highgui.hpp>
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include <iostream>
#include <image_stiching.hpp>
#include <panoramic_utils.hpp>

using namespace cv;
using namespace cv::xfeatures2d;
using namespace std;

StichImages::StichImages(string pathAndPattern)
{
    vector<string> filenames;
    glob(pathAndPattern, filenames, true);

    // check if the path is correct
    if (filenames.size() < 1)
        throw invalid_argument("There are no images inside the specified directory with the specified pattern");
    
    Mat img;
    for (int i = 0; i < filenames.size(); i++)
    {
        img = imread(filenames[i]);
        sourceImgs.push_back(img);
    }
}

StichImages::~StichImages()
{
    // release memory of sourceImgs vector
    for (int i = 0; i < sourceImgs.size(); i++)
        sourceImgs[i].release();
    sourceImgs.clear();
    sourceImgs.shrink_to_fit();
}

void StichImages::cylindricalConversion(double FOV)
{
    for (int i = 0; i < sourceImgs.size(); i++)
    {
        //imshow("origin", sourceImgs[i]);
        Mat img = cylindricalProj(sourceImgs[i], FOV/2.);
        cylindricalImgs.push_back(img);
        /*imshow("cil", img);
        char c = (char)waitKey();
        if (c == 'q')
            break;*/
        detectKeypoints(img);
    }
}

Mat StichImages::generateLandscape()
{

}

vector<KeyPoint> StichImages::detectKeypoints(Mat img)
{
    Ptr<SIFT> detector = SIFT::create();
    vector<KeyPoint> keypoints;
    detector->detect(img, keypoints);
    
    /*// draw and show
    Mat nImg;
    drawKeypoints(img, keyPoints, nImg);
    imshow("SIFT KEYPOINTS", nImg);
    waitKey(0);*/

    return keypoints;
}

void StichImages::matchKeypoints(vector<KeyPoint> keypoints)
{
    for (int i = 0; i < cylindricalImgs.size()-1; i++)
    {
        BFMatcher bfMatch = BFMatcher();
        matcher -> BFMatcher(); 
    }
    
}