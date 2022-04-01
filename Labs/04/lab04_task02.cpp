#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


Mat angleEdgeFlt(Mat img)
{
    Mat enhancedImg = img.clone();

    for (int row = 1; row < img.rows-1; row++)
    {
        for (int col = 1; col < img.cols-1; col++)
        {
            bool notdeg135 = ((img.at<uchar>(row,col)==0) || ((img.at<uchar>(row-1,col-1)==0) || ((img.at<uchar>(row+1,col+1)==0))));
            bool notdeg45 = ((img.at<uchar>(row,col)==0) || ((img.at<uchar>(row-1,col)==0) || ((img.at<uchar>(row+1,col)==0))));
            bool notdeg90 = ((img.at<uchar>(row,col)==0) || ((img.at<uchar>(row-1,col+1)==0) || ((img.at<uchar>(row+1,col-1)==0))));
            if (notdeg135 || notdeg45 || notdeg90)
            {
                enhancedImg.at<uchar>(row,col) == 0;
                cout << "ENTERED ONCE" << endl;
            }
        }
    }
    return enhancedImg;
}


int main(int argc, char** argv)
{
    Mat img = imread("street_scene.png");

    namedWindow("Street scene");
    imshow("Street scene", img);


    Mat imgEdges = Mat::zeros(img.size(),CV_8U);
    Canny(img, imgEdges,573.,278.);
    namedWindow("Canny edges");
    imshow("Canny edges", imgEdges);
    
    Mat edgeAngleFltImg = angleEdgeFlt(imgEdges);
    namedWindow("Angle filtered edges");
    imshow("Angle filtered edges", edgeAngleFltImg);

    waitKey(0);
	return 0;
}