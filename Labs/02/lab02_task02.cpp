#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "lab02_task02_func.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
    // Check n° of args
    if ((argc != 3) && (argc != 4))
    { throw invalid_argument("Usage: <path>/lab02_task02 imageName.jpg <SquareKernelSize>\n Or: <path>/lab02_task02 imageName.jpg <KernelWidth> <KernelHeigth>"); }

    // Check if file exists
    FILE *file;
    string filename(argv[1]);
    if (!(file = fopen(argv[1], "r")))
    { throw invalid_argument(filename + " not found"); }
    fclose(file);
    
    // Check if last arguments are both integers
    int kerWidth = 1;
    if (isdigit(*argv[2]))
    { kerWidth = stoi(argv[2]); }
    else { throw invalid_argument("KernelWidth is not a number"); }
    int kerHeigth = -1;
    if (argc == 4)
    {
        if (isdigit(*argv[3]))
        { kerHeigth = stoi(argv[3]); }
        else { throw invalid_argument("KernelHeigth is not a number"); }
    }
    
    // Begin to process actual task
    cv::Mat grayscaleImg = cv::imread(argv[1], cv::IMREAD_GRAYSCALE );

    cv::imshow("PREFILTERED Image", grayscaleImg);

    cv::Mat maxFlt;
    if (kerHeigth > 0)
    { maxFlt = maxFilter(grayscaleImg,kerWidth,kerHeigth); } // Not square kernel
    else { maxFlt = maxFilter(grayscaleImg,kerWidth); } // Square kernel
    
    cv::imshow("MAX FILTER", maxFlt);

    cv::Mat minFlt;
    if (kerHeigth > 0)
    { minFlt = minFilter(grayscaleImg,kerWidth,kerHeigth); } // Not square kernel
    else { minFlt = minFilter(grayscaleImg,kerWidth); } // Square kernel

    cv::imshow("MIN FILTER", minFlt);
    
    cv::waitKey(0);
	return 0;
}