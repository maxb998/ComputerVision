#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <iostream>
#include <image_stiching.hpp>

using namespace cv;
using namespace std;

class image_stiching
{
private:
    vector<Mat> sourceImg;
public:
    image_stiching(string pathAndPattern);
    ~image_stiching();
};

image_stiching::image_stiching(string pathAndPattern)
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
        sourceImg.push_back(img);
    }

    for (int i = 0; i < sourceImg.size(); i++)
    {
        imread
    }
    
    
}

image_stiching::~image_stiching()
{
}
