#include <tunableBilateral.hpp>

using namespace std;
using namespace cv;

tunableBilateral viewDemo(std::string filename)
{
    tunableBilateral s;
    s.n = 5;
    s.kSize = 3;
    s.sigmaColor = 1.;
    s.sigmaSpace = 1.;
    s.original = imread(filename);
    s.filtered = Mat::zeros(s.original.size(), s.original.type());

    imshow("Original Image", s.original);

    namedWindow(s.windowName);
    createTrackbar("n", s.windowName, &s.n, 10, applyFilterOnSliders, &s);
    createTrackbar("Kernel Size", s.windowName, &s.kSize, 20, applyFilterOnSliders, &s);
    createTrackbar("Sigma Color * 10", s.windowName, &s.intSC, 300, applyFilterOnSliders, &s);
    createTrackbar("Sigma Space * 10", s.windowName, &s.intSP, 300, applyFilterOnSliders, &s);

    applyFilterOnSliders(0, &s);

    return s;
}


void applyFilterOnSliders(int val, void *userdata)
{
    tunableBilateral s = *(tunableBilateral*)userdata;

    if (s.kSize % 2 == 0)
        s.kSize += 1;

    s.sigmaColor = ((double)s.intSC);
    s.sigmaSpace = ((double)s.intSP);

    Mat temp = s.original.clone();

    for (int i = 0; i < s.n; i++)
    {
        bilateralFilter(temp, s.filtered, s.kSize, s.sigmaColor, s.sigmaSpace);
        temp.release();
        temp = s.filtered.clone();
    }

    imshow(s.windowName, s.filtered);
}

void viewDemoRoulette(std::string pattern)
{
    vector<string> filenames;
    glob(pattern, filenames, true);

    // check if the path is correct
    if (filenames.size() < 1)
        throw invalid_argument("There are no images inside the specified directory with the specified pattern");   

    tunableBilateral s = viewDemo(filenames[0]);

    char nxt;
    for (int i = 0; i < filenames.size(); i++)
    {
        s.original = imread(filenames[i]);
        imshow("Original Image", s.original);
        applyFilterOnSliders(0, &s);

        while (true)
        {
            nxt = (char)waitKey(0);
            if (nxt == 'n')
                break;
            if (nxt == 'q')
                exit(EXIT_SUCCESS);
        }
    }
}