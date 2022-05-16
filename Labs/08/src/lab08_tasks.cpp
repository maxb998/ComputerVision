#include <opencv2/highgui.hpp>
#include <fstream>
#include <iostream>
#include <lab08_tasks.hpp>
#include <opencv2/calib3d.hpp>

using namespace cv;
using namespace std;

void customCalibrateCamera(string pathPattern)
{
    vector<Mat> chessBoards = loadImgs(pathPattern);
    int n = chessBoards.size();

    // inner corners = (12,8)
    vector<Mat> corners;
    vector<bool> patternFound;
    cout << "start computing corners" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "i = " << i << "  n = " << n;
        Mat imgCorners;
        patternFound.push_back(findChessboardCorners(chessBoards[i], Size(12,8), imgCorners));
        corners.push_back(imgCorners);
        cout << "     DONE" << endl;
    }
    drawCornersOnChess(chessBoards, corners, patternFound, Size(12,8));
}

vector<Mat> loadImgs(string pathAndPattern)
{
    vector<Mat> sourceImgs;
    vector<string> filenames;
    glob(pathAndPattern, filenames, true);

    // check if the path is correct
    if (filenames.size() < 1)
        throw invalid_argument("There are no images inside the specified directory with the specified pattern");
    
    // load images
    Mat img;
    for (int i = 0; i < filenames.size(); i++)
    {
        img = imread(filenames[i], IMREAD_GRAYSCALE);
        sourceImgs.push_back(img);
    }

    return sourceImgs;
}

void drawCornersOnChess(vector<Mat> originChess, vector<Mat> corners, vector<bool> pattFound, Size s)
{
    for (int i = 0; i < originChess.size(); i++)
    {
        //imshow("Original", originChess[i]);

        Mat imgCorner = originChess[i].clone();
        drawChessboardCorners(imgCorner, s, corners[i], pattFound[i]);

        namedWindow("Corners", WINDOW_NORMAL);
        imshow("Corners", imgCorner);
        resizeWindow("Corners", 1344,1008);
        char c = (char)waitKey(0);
        if (c == 'q')
            break;
    }
}