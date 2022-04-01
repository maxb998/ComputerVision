#include <opencv2/highgui.hpp>

cv::Mat justColor(cv::Mat source, int colorIndex)
{
    cv::Mat newImg = source.clone();

    for (int i = 0; i < newImg.rows; i++)
       for (int j = 0; j < newImg.cols; j++)
           for (size_t t = 0; t < 3; t++)
                if(t != colorIndex)
                    newImg.at<cv::Vec3b>(i,j)(t) = 0;
           

    return newImg;
}

int main(int argc, char** argv)
{
	cv::Mat img = cv::imread(argv[1]);

    if (img.channels() == 3) 
    {
        cv::Mat onlyBlue = justColor(img, 0);
        cv::imshow("Only Blue", onlyBlue);

        cv::Mat onlyGreen = justColor(img, 1);
        cv::imshow("Only Green", onlyGreen);

        cv::Mat onlyRed = justColor(img, 2);
        cv::imshow("Only Red", onlyRed);
    }

	char exitKey = cv::waitKey(0);
	printf("\n%c\n", exitKey);
	return 0;
}
