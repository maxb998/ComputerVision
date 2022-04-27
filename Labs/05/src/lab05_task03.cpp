#include "lab05_tasks.hpp"

using namespace cv;
using namespace std;

void task03(string filename)
{
    Mat img = imread(filename);
    imshow("Original picture", img);

    Mat blurred;
    medianBlur(img, blurred, 7);
    Mat kmImg = t3_kmeansSegmentation(blurred, 8);
    imshow("Kmeans method result", kmImg);
    
    waitKey(0);
}

Mat t3_kmeansSegmentation(Mat img, const int k)
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

    // check what clusters represent the shirts
    int cluster1 = -1, cluster2 = -1;
    for (int i = 0; i < centers.size(); i++)
    {
        if ( ((centers[i](0) >= 10 && centers[i](0) <= 18) && (centers[i](1) >= 71 && centers[i](1) <= 79) && (centers[i](2) >= 117 && centers[i](2) <= 125)) || 
            ((centers[i](0) >=  35 && centers[i](0) <= 43) && (centers[i](1) >= 125 && centers[i](1) <= 133) && (centers[i](2) >= 204 && centers[i](2) <= 212)) )
        {
            if (cluster1 == -1)
                cluster1 = i;
            else if (cluster2 == -1)
                cluster2 = i;
        }
    }

    // show the result of clustering in a new picture using center of each cluster found by kmeans as colors
    Mat seg = Mat::zeros(img.size(), CV_8UC3);
    for (int row = 0; row < img.rows; row++)
    {
        for (int col = 0; col < img.cols; col++)
        {
            int kNum = labels.at<int>(img.cols * row + col,0);
            if ((kNum == cluster1) || (kNum == cluster2))
                seg.at<Vec3b>(row,col) = (Vec3b)centers[cluster1];
        }
    }

    // don't know if I need to release the memory zones that are no longer used
    kmeansMat.release();

    return seg;
}