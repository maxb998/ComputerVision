#include "lab04_tasks.hpp"

using namespace cv;
using namespace std;

void drawLinesOnMat(Mat &img, vector<Vec3f> lines, Vec3b color, int nLines, int lineLength)
{
    for( size_t i = 0; (i < lines.size()) && (i < nLines); i++ )
    {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;

        pt1.x = cvRound(x0 + lineLength*(-b)/2);
        pt1.y = cvRound(y0 + lineLength*(a)/2);
        pt2.x = cvRound(x0 - lineLength*(-b)/2);
        pt2.y = cvRound(y0 - lineLength*(a)/2);

        line( img, pt1, pt2, Scalar(color), 3);
    }
}

void task03(string filename)
{
    Mat img = imread(filename);
    vector<Vec3f> lines;

    Mat adaptedImg = Mat::zeros(img.size(), CV_8UC1);

    Canny(img, adaptedImg, 540.0, 410.0);

    HoughLines(adaptedImg,lines,1,CV_PI/180, 220);

    drawLinesOnMat(img, lines, Vec3b(0,0,255), 2, 3000);

    imshow("Hough lines", img);
    
    waitKey(0);
}