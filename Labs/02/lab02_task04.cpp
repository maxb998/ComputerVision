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

//check wether the histograms are identical (used for debug purposes)
bool checkCorrectness(Mat hist1, Mat hist2)
{
    bool check = true;
    for (int i = 0; i < hist1.rows; i++)
    {
        if (hist1.at<float>(i,0) != hist2.at<float>(i,0))
        {
            check = false;
            cout << i << "     " << hist1.at<float>(i,0) << "     " << hist2.at<float>(i,0) << endl;
            //prints all points that are different between the 2 histograms
        }
    }   
    return check;
}

int main(int argc, char** argv)
{
    Mat img = imread(argv[1], IMREAD_GRAYSCALE);
    imshow("image", img);

    int nbins = 60; //n° of columns composing the histogram

    //Histogram Calculation by OpenCV function
    Mat autoHist;
    int c[] = {0}, size[] = {nbins};
    float range[] = {0,255};
    const float* ranges[] = {range};
    calcHist(&img, 1, c, Mat(), autoHist, 1, size, ranges);

    plotHistogram2D(autoHist, 500, 1000/nbins, "Automatic Histogram");

    //Manual calculation of the histogram
    Mat manualHist = Mat::zeros(nbins,1,CV_32FC1);
    for (int row = 0; row < img.rows; row++)
    {
        for (int col = 0; col < img.cols; col++)
        {
            manualHist.at<float>(((int)img.at<uchar>(row,col)*nbins/255),0)++;
        }
    }    

    plotHistogram2D(manualHist, 500, 1000/nbins, "Manual Histgram");

    if (checkCorrectness(manualHist,autoHist))
    {
        cout << "The two histograms are exactly the same" << endl;
    }
    else
    {
        cout << "The two histograms are different" << endl;
    }


    waitKey(0);
	return 0;
}