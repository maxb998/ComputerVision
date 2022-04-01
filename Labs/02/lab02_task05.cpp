#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void plotHistogram2D(Mat histogramData, int height, int widthRatio, string name)
{
    //create empty image to contain the actual plot
    Mat graph = Mat::zeros(height,histogramData.rows*widthRatio,CV_8U);

    //find maximum value in order to scale the height of the histogram bars accordingly
    float max = histogramData.at<float>(0,0);
    for (int i = 1; i < histogramData.rows; i++)
    {
        if (max < histogramData.at<float>(i,0))
        {
            max = histogramData.at<float>(i,0);
        }
    }
    
    
    //generate image to show the histogram bry drawing rectangles on a matrix of zeroes
    for (int i = 0; i < histogramData.rows; i++)
    {
        rectangle(graph, 
            Point(i*widthRatio, 0), 
            Point((i+1)*widthRatio-1, height-(int)(histogramData.at<float>(i,0)*height/max)),
            Scalar(255),FILLED);
    }

    imshow(name, graph);
}

int main(int argc, char** argv)
{
    Mat img = imread(argv[1], IMREAD_GRAYSCALE);

    Mat eqImg = Mat::zeros(img.rows, img.cols,img.type());

    equalizeHist(img, eqImg);   //Equalize image

    int nbins = 256; //n° of columns composing the histogram
    //Histogram Calculation
    Mat originHist, eqHist;
    int c[] = {0}, size[] = {nbins};
    float range[] = {0,256};
    const float* ranges[] = {range};
    calcHist(&img, 1, c, Mat(), originHist, 1, size, ranges);
    calcHist(&eqImg, 1, c, Mat(), eqHist, 1, size, ranges);

    //print results
    plotHistogram2D(originHist, 500, 1000/nbins, "Pre-equalization Histogram");
    plotHistogram2D(eqHist, 500, 1000/nbins, "Equalized Histogram");

    imshow("Original image", img);
    imshow("Equalized image", eqImg);

    waitKey(0);
	return 0;
}