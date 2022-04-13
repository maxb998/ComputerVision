#include "lab04_tasks.hpp"

#define MIN_LINE_LENGTH 20      // beware that a too high value influences negatively performance of flollowVerticalLine2
#define TRUE_LINE_COLOR (uchar)240
#define SHORT_LINE_COLOR (uchar)50
#define VISITED_PIXEL_COLOR (uchar)15
#define TOLERANCE_VALUE 1.0F

#define PT0 Point(col-1,row)
#define PT1 Point(col-1,row+1)
#define PT2 Point(col  ,row+1)
#define PT3 Point(col+1,row+1)
#define PT4 Point(col+1,row)

using namespace cv;
using namespace std;


uchar followVerticalLine2(Mat &img, Slope s, float iter)
{
    int row = s.getLastY(), col = s.getLastX();
    img.at<uchar>(row,col) = VISITED_PIXEL_COLOR;   // avoids traps

    Point pts[] = {PT0,PT1,PT2,PT3,PT4};
    
    uchar finalColor = SHORT_LINE_COLOR;
    float currentSlope = s.value();
    bool iterated = false;

    for (int i = 0; i < (sizeof(pts)/sizeof(pts[0])); i++)
    {
        if ((pts[i].x > -1) && (pts[i].x < img.cols) && (pts[i].y < img.rows))  // check bounds
        {
            if ((img.at<uchar>(pts[i]) > VISITED_PIXEL_COLOR) && (img.at<uchar>(pts[i]) != TRUE_LINE_COLOR))
            {
                s.setLast(pts[i]);  // move to next point

                if ((iter != 0) && (abs(s.value()-currentSlope) > TOLERANCE_VALUE/iter))    // checks if adding the point will distort the line too much
                    continue;

                uchar color = followVerticalLine2(img,s,iter+1); // recursion tells if current point is source of a line
                iterated = true;

                if (color == TRUE_LINE_COLOR)
                {
                    img.at<uchar>(row,col) = color;
                    finalColor = color; // needs to be part of just one line to get the color
                }
            }
        }
    }
    
    if (!iterated)
    {
        if (iter > MIN_LINE_LENGTH)
            finalColor = TRUE_LINE_COLOR;
        else
            finalColor = SHORT_LINE_COLOR;
    }
    img.at<uchar>(row,col) = finalColor;

    return finalColor;
}

uchar followVerticalLine(Mat &img, int row, int col, int iterNum, float slope, Point first)
{
    int nextRow = row + 1;  // move to row below

    if (nextRow < img.rows) // check if nextRow is still in the image
    {
        int colPriorityOrder[3] = {-1, -1, -1}; // -1 means that one checked it won't even consider the column

        if (slope > 0.5)        // between 22.5° and 45° angle line
        {
            colPriorityOrder[0] = col+1;
            colPriorityOrder[1] = col;
        }
        else if (slope < -0.5)   // between -45° and -22.5° angle line
        {
            colPriorityOrder[0] = col-1;
            colPriorityOrder[1] = col;
        }
        else                    // between -22.5° and 22.5° angle line
        {
            colPriorityOrder[0] = col;
            colPriorityOrder[1] = col-1;
            colPriorityOrder[2] = col+1;
        }

        for (int i = 0; i < 3; i++)
        {
            if ((colPriorityOrder[i] > -1) && (colPriorityOrder[i] < img.cols))
            {
                if (img.at<uchar>(nextRow, colPriorityOrder[i]) == 255) // check if the selected pixel is part of an edge
                {
                    float newSlope = (float)(colPriorityOrder[i]-first.x)/(float)(nextRow-first.y); // slope calculation

                    if (abs(newSlope-slope) < 1./(float)iterNum)
                    {
                        uchar newColor = followVerticalLine(img, nextRow, colPriorityOrder[i], iterNum+1, newSlope, first); // recursive call

                        img.at<uchar>(nextRow, colPriorityOrder[i]) = newColor; // color set

                        return newColor;
                    }
                }
            }
        }
    }

    if (iterNum > MIN_LINE_LENGTH)
        return TRUE_LINE_COLOR;  // the line is valid
    else
        return SHORT_LINE_COLOR;   // line to short
}

Mat myFindStraightlines2(Mat img)
{
    Mat enhancedImg = img.clone();
    
    for (int row = 0; row < img.rows; row++)
    {
        for (int col = 0; col < img.cols; col++)
        {
            if (enhancedImg.at<uchar>(row,col) == 255)
            {
                Slope s(Point(col,row));
                followVerticalLine2(enhancedImg,s,0.0F);
            }
        }
    }


    return enhancedImg;
}

Mat myFindStraightlines(Mat img) // had to specify it was mine because there is one with the same name in openCV Mat
{
    Mat enhancedImg = img.clone();
    
    for (int row = 0; row < img.rows; row++)
    {
        for (int col = 0; col < img.cols; col++)
        {
            if (enhancedImg.at<uchar>(row,col) == 255)
            {
                enhancedImg.at<uchar>(row,col) = followVerticalLine(enhancedImg, row, col, 0, 0., Point(col,row));
            }
        }
    }


    return enhancedImg;
}

Mat checkColorsAroundLine(Mat img, Mat lines, uchar colorThreshold, int neighborhoodSize)   // returns black image with the only white pixels being the ones that are near a line and the color is "greater" than the threshold
{
    Mat coloredLines = Mat::zeros(img.size(),CV_8UC1);

    for (int row = 0; row < img.rows; row++)
    {
        for (int col = 0; col < img.cols; col++)
        {
            // for each pixel that belongs into a line(defined by non black pixels in Mat lines) check neighborhood
            if ((lines.at<uchar>(row,col) < TRUE_LINE_COLOR))
                continue;
            for (int i = row-neighborhoodSize; i < row+neighborhoodSize+1; i++)
            {
                for (int j = col-neighborhoodSize; j < col+neighborhoodSize+1; j++)
                {
                    if ((i > -1) && (i < img.rows) && (j > -1) && (j < img.cols))
                    {
                        if ((img.at<Vec3b>(i,j)[0] >= colorThreshold) && (img.at<Vec3b>(i,j)[1] >= colorThreshold) && (img.at<Vec3b>(i,j)[2] >= colorThreshold))
                        {
                            // set the color of the current pixel and the neighbor one to white
                            coloredLines.at<uchar>(row,col) = (uchar)255;
                            coloredLines.at<uchar>(i,j) = (uchar)255;
                        }
                    }
                }
            }
        }
    }
    return coloredLines;
}

void task02(string filename)
{
    // Load img and apply canny
    Mat img = imread(filename), cannyImg = Mat::zeros(img.size(), CV_8UC1);
    Canny(img, cannyImg, 540, 410);

    Mat lineFlt1 = myFindStraightlines(cannyImg);

    // must check command line in order to see if the method has returned something
    cout << "START METHOD 2 TO FIND STRAIGHT LINES, WHICH PROBABLY HAS EXPONENTIAL TIME COMPLEXITY(OR EVEN WORSE), PLEASE SET \"MIN_LINE_LENGTH\" TO A LOWER VALUE" << endl;
    Mat lineFlt2 = myFindStraightlines2(cannyImg);
    cout << "Not trapped inside myFindStraightlines2 recursion" << endl;
    
    imshow("Canny ONLY", cannyImg);
    imshow("Canny + Line filtering method 1", lineFlt1);
    imshow("Canny + Line filtering method 2", lineFlt2);

    Mat colorFlt0 = checkColorsAroundLine(img,cannyImg,(char)250,3);
    Mat colorFlt1 = checkColorsAroundLine(img,lineFlt1,(char)250,3);
    Mat colorFlt2 = checkColorsAroundLine(img,lineFlt2,(char)250,3);


    imshow("Canny + Color filtering", colorFlt0);
    imshow("Canny + Line filtering method 1 + Color filtering", colorFlt1);
    imshow("Canny + Line filtering method 2 + Color filtering", colorFlt2);
    
    waitKey(0);
}