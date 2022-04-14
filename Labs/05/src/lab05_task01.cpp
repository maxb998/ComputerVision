#include "lab05_tasks.hpp"

using namespace cv;
using namespace std;

void task01(string filename)
{
    const int medianKSize = 7;

    Mat img = imread(filename);
    imshow("Original Picture", img);

    Mat grayImg = Mat::zeros(img.size(), CV_8UC1);
    cvtColor(img, grayImg, COLOR_BGR2GRAY);
    imshow("Grayscale Picture", grayImg);

    Mat med = Mat::zeros(grayImg.size(), grayImg.type());
    medianBlur(grayImg, med, medianKSize);
    imshow("Median Filtered Picture", med);
    


    waitKey(0);
}

Mat thresholding(Mat img) // region growing
{
    equalizeHist(img, img);
    for (int row = 0; row < img.rows; row++)
    {
        for (int col = 0; col < img.cols; col++)
        {
            if (img.at<uchar>(row,col) <= (uchar)0)
                img.at<uchar>(row,col) = 255;
            else
                img.at<uchar>(row,col) = 0;
        }
    }
    imshow("THRESHOLDING", img);

    waitKey(0);
}

void task01_Kmeans(Mat img)     // BROKEN IMG SIZES
{
    const int k = 2;

    img.convertTo(img, CV_32F);
    img = img.reshape(1,img.cols*img.rows);


    Mat labels = Mat::ones(img.size(), CV_32S);

    double minVal, maxVal;
    Point minPt, maxPt;
    minMaxLoc(img, &minVal, &maxVal, &minPt, &maxPt);

    float threshVal = (float)(minVal);

    for (int i = 0; i < labels.rows; i++)
    {
        if (img.at<float>(i,0) <= threshVal)
            labels.at<int>(i,0) = 0;
        else
            labels.at<int>(i,0) = 1;   
    }
    
    kmeans(img, k, labels, TermCriteria( TermCriteria::EPS+TermCriteria::MAX_ITER, 10, 1.0), 1, KMEANS_USE_INITIAL_LABELS);

    Mat seg = Mat::zeros(img.size(), CV_8UC1);

    for (int row = 0; row < img.rows; row++)
    {
        for (int col = 0; col < img.cols; col++)
        {
            int lblIndex = img.cols * row + col;
            seg.at<uchar>(row,col) = (uchar)(255 * labels.at<int>(lblIndex,0) / k);            
        }
        
    }
    
    imshow("KMEANS", seg);

    waitKey(0);
}

void experiments(string filename)
{
    const int medianKSize = 7, k = 2;

    Mat img = imread(filename);
    imshow("Original Picture", img);

    Mat grayImg = Mat::zeros(img.size(), CV_8UC1);
    cvtColor(img, grayImg, COLOR_BGR2GRAY);
    imshow("Grayscale Picture", grayImg);

    Mat med = Mat::zeros(grayImg.size(), grayImg.type());
    medianBlur(grayImg, med, medianKSize);
    imshow("Median Filtered Picture", med);
    equalizeHist(med,med);


    double minVal, maxVal;
    Point minPt, maxPt;
    minMaxLoc(med, &minVal, &maxVal, &minPt, &maxPt);

    cout << "Max = " << maxVal << "       Min = " << minVal << endl;

    Scalar myMean, stdDev;
    meanStdDev(med, myMean, stdDev);

    cout << "mean = " << myMean(0) << endl;
    cout << "std dev = " << stdDev(0) << endl;

    double thresholdValue = round(myMean(0) - stdDev(0));
    cout << "threshold = " << thresholdValue << endl;
    
}