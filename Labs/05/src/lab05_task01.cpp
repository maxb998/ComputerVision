#include "lab05_tasks.hpp"

#define PT0 Point(col - 1, row - 1)
#define PT1 Point(col    , row - 1)
#define PT2 Point(col + 1, row - 1)
#define PT3 Point(col - 1, row    )
#define PT4 Point(col    , row    )
#define PT5 Point(col + 1, row    )
#define PT6 Point(col - 1, row + 1)
#define PT7 Point(col    , row + 1)
#define PT8 Point(col + 1, row + 1)

using namespace cv;
using namespace std;

void task01(string filename)
{
    const int medianKSize = 7, kmeansK = 10;
    const uchar regGrowSeedThreshold = (uchar)0, regGrowGrowthThreshold = (uchar)60, dynRegGrowthThreshDivivend = (uchar) 5;

    Mat img = imread(filename);
    imshow("Original picture", img);

    cout << "\nPress any key to continue.\nCurrent: kmeans method" << endl;
    Mat km = t1_kmeansSegmentCrack(img, kmeansK, medianKSize);
    imshow("Segmented crack using Kmeans", km);
    waitKey(0);
    destroyWindow("Segmented crack using Kmeans");

    cout << "\nPress any key to continue.\nCurrent: simple region growing" << endl;
    Mat staticReg = t1_staticThresholdRegionGrowing(img, regGrowSeedThreshold, regGrowGrowthThreshold, medianKSize);
    imshow("Segmented crack using static threshold region growing", staticReg);
    waitKey(0);
    destroyWindow("Segmented crack using static threshold region growing");

    // this last one method seems to work the best... more or less
    cout << "\nPress any key to continue.\nCurrent: less-simple region growing" << endl;
    Mat dynamicReg = t1_dynamicThresholdRegionGrowing(img, regGrowSeedThreshold, regGrowGrowthThreshold, dynRegGrowthThreshDivivend, medianKSize);
    imshow("Segmented crack using DYNAMIC threshold region growing", dynamicReg);
    waitKey(0);
    destroyWindow("Segmented crack using DYNAMIC threshold region growing");
    
    waitKey(0);
}

Mat t1_kmeansSegmentCrack(Mat img, const int k, const int medianKSize)
{
    // convert image to grayscale and equalize
    Mat grayEqualizedImg = Mat::zeros(img.size(), CV_8UC1);
    cvtColor(img, grayEqualizedImg, COLOR_BGR2GRAY);
    equalizeHist(grayEqualizedImg, grayEqualizedImg);

    // filter and convert to proper settings for kmeans function
    Mat kmeansMat = Mat::zeros(grayEqualizedImg.size(), grayEqualizedImg.type());
    medianBlur(grayEqualizedImg, kmeansMat, medianKSize);
    kmeansMat.convertTo(kmeansMat, CV_32F);
    kmeansMat = kmeansMat.reshape(1,kmeansMat.cols*kmeansMat.rows);

    // init values returned by kmeans
    Mat labels = Mat::ones(kmeansMat.size(), CV_32S);
    vector<float> centers;

    // kmeans
    kmeans(kmeansMat, k, labels, TermCriteria( TermCriteria::EPS+TermCriteria::MAX_ITER, 10, 1.0), 2, KMEANS_PP_CENTERS, centers);

    // find label of center with minimum value
    int minClusterId = 0;
    for (int i = 1; i < k; i++)
        if (centers[i] < centers[minClusterId])
            minClusterId = i;

    // show the crack region in white
    Mat seg = Mat::zeros(img.size(), CV_8UC1);
    for (int row = 0; row < img.rows; row++)
    {
        for (int col = 0; col < img.cols; col++)
        {
            int lblIndex = img.cols * row + col;
            if (labels.at<int>(lblIndex,0) == minClusterId)
                seg.at<uchar>(row,col) = (uchar)255;
        }
    }

    return seg;
}

Mat t1_staticThresholdRegionGrowing(Mat img, const uchar seedThreshold, const uchar growthThreshold, const int medianKSize)
{
    // converto to grayscale
    Mat gray = Mat::zeros(img.size(), CV_8UC1);
    cvtColor(img, gray, COLOR_BGR2GRAY);

    // apply filter to try to remove tarmac little stones and details, which can be treated as salt & pepper noise
    medianBlur(gray,gray,medianKSize);

    // equalize image to get darkest points to become of value 0
    Mat equalized = Mat::zeros(img.size(), img.type());
    equalizeHist(gray, equalized);
    Mat seeds = equalized.clone();

    // highlight all points with value 0, which are the darkest ones, which, in correct light exposition, are effectively the cracks(or new tarmac)
    for (int row = 0; row < seeds.rows; row++)
    {
        for (int col = 0; col < seeds.cols; col++)
        {
            if (equalized.at<uchar>(row,col) <= seedThreshold)
                seeds.at<uchar>(row,col) = (uchar)254;     // 254 so 255 can be setted at the end other useless loops
            else
                seeds.at<uchar>(row,col) = (uchar)0;
        }
    }
    //imshow("THRESHOLD SET OF POINTS", seeds);     // DEBUG

    // "grow" previously highlighted region with a static threshold technique
    Mat crackRegion = seeds.clone();
    uchar T = growthThreshold, regionVal = seedThreshold;
    bool changed = true;

    while (changed)
    {
        changed = false;
        for (int row = 0; row < crackRegion.rows; row++)
        {
            for (int col = 0; col < crackRegion.cols; col++)
            {
                if (crackRegion.at<uchar>(row, col) == (uchar)254) // check 8-connected
                {
                    vector<Point> pts = t1_correctNeighbor(row, col, crackRegion.rows, crackRegion.cols);

                    for (unsigned long i = 0; i < pts.size(); i++)
                    {
                        if ((crackRegion.at<uchar>(pts[i]) != (uchar)255) && (equalized.at<uchar>(pts[i]) - regionVal < T))
                        {
                            crackRegion.at<uchar>(pts[i]) = (uchar)254;
                        }
                    }
                    crackRegion.at<uchar>(row, col) = (uchar)255;
                    changed = true;
                }
            }
        }
    }
    
    return crackRegion;
}

Mat t1_dynamicThresholdRegionGrowing(Mat img, const uchar seedThreshold, const uchar growthThreshold, const uchar distanceAttenuator, const int medianKSize)
{
    // converto to grayscale
    Mat gray = Mat::zeros(img.size(), CV_8UC1);
    cvtColor(img, gray, COLOR_BGR2GRAY);

    // apply filter to try to remove tarmac little stones and details, which can be treated as salt & pepper noise
    medianBlur(gray,gray,medianKSize);

    // equalize image to get darkest points to become of value 0
    Mat equalized = Mat::zeros(img.size(), img.type());
    equalizeHist(gray, equalized);
    Mat seeds = equalized.clone();

    // highlight all points with value 0, which are the darkest ones, which, in correct light exposition, are effectively the cracks(or new tarmac)
    for (int row = 0; row < seeds.rows; row++)
    {
        for (int col = 0; col < seeds.cols; col++)
        {
            if (equalized.at<uchar>(row,col) <= seedThreshold)
                seeds.at<uchar>(row,col) = (uchar)254;
            else
                seeds.at<uchar>(row,col) = (uchar)0;
        }
    }
    //imshow("THRESHOLD SET OF POINTS", seeds);     // DEBUG

    // color of white the region containing the crack
    Mat crackRegion = seeds.clone();
    Mat supportMat = Mat::zeros(crackRegion.size(), CV_8UC1);   // used to keep the number of iterations of "distance" from the seeds
    uchar regionVal = seedThreshold;
    int T = (int)growthThreshold;
    bool changed = true;
    int iterNum = 1;

    while (changed)
    {
        changed = false;
        for (int row = 0; row < crackRegion.rows; row++)
        {
            for (int col = 0; col < crackRegion.cols; col++)
            {
                if (crackRegion.at<uchar>(row, col) == (uchar)254) // check 8-connected
                {
                    vector<Point> pts = t1_correctNeighbor(row, col, crackRegion.rows, crackRegion.cols);

                    for (unsigned long i = 0; i < pts.size(); i++)
                    {
                        if ((crackRegion.at<uchar>(pts[i]) != (uchar)255) && ((int)equalized.at<uchar>(pts[i]) - regionVal + (int)supportMat.at<uchar>(row,col)/distanceAttenuator < T))
                        {
                            crackRegion.at<uchar>(pts[i]) = (uchar)254;
                            supportMat.at<uchar>(pts[i]) = supportMat.at<uchar>(row,col) + (uchar)1;
                        }
                    }
                    crackRegion.at<uchar>(row, col) = (uchar)255;
                    changed = true;
                }
            }
        }
        iterNum++;
    }
    
    return crackRegion;
}

vector<Point> t1_correctNeighbor (int row, int col, int matRows, int matCols)
{
    vector<Point> pts = {PT0, PT1, PT2, PT3, PT5, PT6, PT7, PT8};
    if (row == 0)                       // first row check
    {
        pts.clear();
        pts.shrink_to_fit();
        if (col == 0)                   // first pixel check
            vector<Point> pts = {PT5, PT7, PT8};
        else if (col == matCols - 1)    // last row first pixel check
            vector<Point> pts = {PT3, PT6, PT7};
        else                            // any other first row pixel check
            vector<Point> pts = {PT3, PT5, PT6, PT7, PT8};
    }
    else if (row == matRows - 1)        // last row check
    {
        pts.clear();
        pts.shrink_to_fit();
        if (col == 0)                   // last row first pixel check
            vector<Point> pts = {PT1, PT2, PT5};
        else if (col == matCols - 1)    // last pixel check
            vector<Point> pts = {PT0, PT1, PT3};
        else                            // any other last row pixel check
            vector<Point> pts = {PT3, PT5, PT6, PT7, PT8};
    }
    else if (col == 0)                  // any first column pixel check(other than first and last row)
    {
        pts.clear();
        pts.shrink_to_fit();
        vector<Point> pts = {PT1, PT2, PT5, PT7, PT8};
    }
    else if (col == matCols -1)         // any last column pixel check(other than first and last row)
    {
        pts.clear();
        pts.shrink_to_fit();
        vector<Point> pts = {PT0, PT1, PT3, PT6, PT7};
    }

    return pts;
}