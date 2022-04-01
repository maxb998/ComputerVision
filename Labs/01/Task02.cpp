#include <opencv2/highgui.hpp>

int main(int argc, char** argv)
{
	cv::Mat img = cv::imread(argv[1]);
	printf("\n%d", img.channels());
	cv::namedWindow("CARROT");
	cv::imshow("THE IMAGE", img);
	char exitKey = cv::waitKey(0);
	printf("\n%c\n", exitKey);
	
	return 0;
}
