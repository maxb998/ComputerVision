#include "lab05_tasks.hpp"

using namespace cv;
using namespace std;




void task01(string filename)
{
    Mat img = imread(filename);
    Mat flt = Mat::zeros(img.size(), img.type());

    GaussianBlur(img,flt,Size(9,9),2.0,0.0);
    //bilateralFilter(img,flt,5,4.0,1.0);

    imshow("ORIGINAL IMAGE", img);
    imshow("FILTERED IMAGE",flt);


    waitKey(0);
}