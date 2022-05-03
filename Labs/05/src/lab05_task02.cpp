#include "lab05_tasks.hpp"

using namespace cv;
using namespace std;

void task02(string filename)
{
    Mat img = imread(filename);
    imshow("Original picture", img);

    Mat blurred;
    medianBlur(img, blurred, 7);
    Mat kmImg = t2_kmeansSegmentation(blurred, 10);
    imshow("Kmeans method result", kmImg);
    
    Mat watershRegions = t2_watershedTechnique(img);
    imshow("Watershed technique result", watershRegions);
    
    waitKey(0);
}

Mat t2_kmeansSegmentation(Mat img, const int k)
{
    // convert to proper settings for kmeans function
    Mat kmeansMat = img.clone();
    kmeansMat.convertTo(kmeansMat, CV_32F);
    kmeansMat = kmeansMat.reshape(1,kmeansMat.cols*kmeansMat.rows);

    // declare values returned by kmeans
    Mat labels = Mat::ones(kmeansMat.size(), CV_32S);
    vector<Vec3b> centers;

    // kmeans
    kmeans(kmeansMat, k, labels, TermCriteria( TermCriteria::EPS+TermCriteria::MAX_ITER, 10, 1.0), 1, KMEANS_PP_CENTERS, centers);

    // show the result of clustering in a new picture using center of each cluster found by kmeans as colors
    Mat seg = Mat::zeros(img.size(), CV_8UC3);
    for (int row = 0; row < img.rows; row++)
    {
        for (int col = 0; col < img.cols; col++)
        {
            int lblIndex = img.cols * row + col;
            seg.at<Vec3b>(row,col) = (Vec3b)centers[labels.at<int>(lblIndex,0)];  
        }
    }

    // don't know if I need to release the memory zones that are no longer used
    kmeansMat.release();

    return seg;
}

#define SKY_POINTS { Point(589,67) }
#define ROAD_POINTS { Point(578,292), Point(1025,362) }
#define OTHER_POINTS { Point(150,299), Point(349,159), Point(606,159), Point(848,207), Point(1067,295) }

#define SKY_COLOR Vec3b(247, 204, 136)
#define ROAD_COLOR Vec3b(117,117,112)
#define OTHER_COLOR Vec3b(34, 51, 43)

Mat t2_watershedTechnique(Mat img)
{
    // declare objects needed to use the watershed method
    vector<vector<Point>> features = { SKY_POINTS, ROAD_POINTS, OTHER_POINTS };
    Mat markers = Mat::zeros(img.size(), CV_32S);

    // draw points of different color on a kind of mask(the color represent the region number so points with the same color, but different than zero will be in the same region)
    // the more points are manually picked and drawn the higher will be the precision of the segmentation, but the overfit will also increase(this method is basically pure overfit compared to the kmeans)
    for (int i = 0; i < features.size(); i++)
        for (int j = 0; j < features[i].size(); j++)
            markers.at<int>(features[i][j]) = i + 1;
    
    // apply the opencv method
    watershed(img, markers);

    // declare objects needed to draw the final image
    Mat regions = Mat::zeros(img.size(), img.type());
    vector<Vec3b> colors = { SKY_COLOR, ROAD_COLOR, OTHER_COLOR };

    // draw each color in its corresponding region
    for (int row = 0; row < img.rows; row++)
    {
        for (int col = 0; col < img.cols; col++)
        {
            int colorId = markers.at<int>(row,col) - 1;
            regions.at<Vec3b>(row,col) = colors[colorId];
        }
    }
    
    return regions;
}