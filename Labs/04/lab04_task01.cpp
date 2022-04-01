#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int t1slider=100, t2slider=100;
Mat img, imgEdges;

static void applyCanny() 
{
    Canny(img, imgEdges, (double)t1slider, (double)t2slider);

    imshow("Canny edges", imgEdges);
}

static void threshold1(int val, void* userdata) 
{
    applyCanny();
}
static void threshold2(int val, void* userdata) 
{
    applyCanny();
}


int main(int argc, char** argv)
{
    img = imread("street_scene.png");

    namedWindow("Street scene");
    imshow("Street scene", img);

    namedWindow("Canny edges");
    createTrackbar("Threshold1","Canny edges",&t1slider,750,threshold1);
    createTrackbar("Threshold2","Canny edges",&t2slider,750,threshold2);


    imgEdges = Mat::zeros(img.size(),CV_8U);
    
    
    applyCanny();

    waitKey(0);
	return 0;
}