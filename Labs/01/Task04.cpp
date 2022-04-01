#include <opencv2/highgui.hpp>

cv::Mat removeColor(cv::Mat source, int colorIndex)
{
    cv::Mat newImg = source.clone();

    for (int i = 0; i < newImg.rows; i++)
       for (int j = 0; j < newImg.cols; j++)
           newImg.at<cv::Vec3b>(i,j)(colorIndex) = 0;

    return newImg;
}

int main(int argc, char** argv)
{
	cv::Mat img = cv::imread(argv[1]);

    if (img.channels() == 3) 
    {
        cv::Mat rmBlue = removeColor(img, 0);
        cv::imshow("No Blue img", rmBlue);

        cv::Mat rmGreen = removeColor(img, 1);
        cv::imshow("No Green img", rmGreen);

        cv::Mat rmRed = removeColor(img, 2);
        cv::imshow("No Red img", rmRed);
    }

    //The color coding of OpenCv for a Vec3b is [Blue, Green, Red]

	char exitKey = cv::waitKey(0);
	printf("\n%c\n", exitKey);
	return 0;
}
