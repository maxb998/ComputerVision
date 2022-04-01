#include </usr/local/include/opencv4/opencv2/highgui.hpp>

cv::Mat rotateImg(cv::Mat img, float theta)
{
    cv::Mat rotImg(img.size(), img.type());

    float rotMat[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            rotMat[i][j] = 0;
    
    rotMat[0][0] = cosf(theta);
    rotMat[1][1] = rotMat[0][0];
    rotMat[0][1] = sinf(theta);
    rotMat[1][0] = -rotMat[0][1];
    rotMat[2][2] = 1;

    int count = 0;
    for (int y = 0; y < img.rows; y++)
    {
        for (int x = 0; x < img.cols; x++)
        {
            int xp = (int) (rotMat[0][0]*(float)x + rotMat[0][1]*(float)y + rotMat[0][2]);
            int yp = (int) (rotMat[1][0]*(float)x + rotMat[1][1]*(float)y + rotMat[1][2]);
            if ((xp < img.rows) && (yp < img.cols) && (xp >= 0) && (yp >= 0))
            {
                rotImg.at<cv::Vec3b>(xp,yp) = img.at<cv::Vec3b>(x,y);
                count++;
            }
        }
        
    }
    


    return rotImg;
}

int main(int argc, char** argv)
{
	cv::Mat img = cv::imread(argv[1]);
	
    if (img.channels() == 3)
    {
        cv::Mat rotatedImg = rotateImg(img, 3.14/4);
        cv::imshow("RotatedIMG", rotatedImg);
    }

	cv::waitKey(0);
	return 0;
}
