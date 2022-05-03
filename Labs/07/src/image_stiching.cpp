#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <iostream>
#include <image_stiching.hpp>

using namespace cv;
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

    namedWindow("IMAGE_TEST");

    for (int i = 0; i < sourceImgs.size(); i++)
    {
        imshow("IMAGE_TEST", sourceImgs[i]);
        waitKey(0);
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
