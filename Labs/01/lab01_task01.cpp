#include </usr/local/include/opencv4/opencv2/highgui.hpp>

int main(int argc, char** argv)
{
	cv::Mat img = cv::imread(argv[1]);
	cv::namedWindow("CARROT");
	cv::imshow("THE IMAGE", img);
	//printf("\n%d\n", img.type());
	cv::waitKey(0);
	
	return 0;
}
