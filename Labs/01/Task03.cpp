#include <opencv2/highgui.hpp>

cv::Mat chessBoard(int boardSize, int squareSize, cv::Vec3b color1, cv::Vec3b color2)
	{
	cv::Mat chess(boardSize,boardSize,CV_8UC3);

	bool rowSquare = true, colSquare = true;
	u_int8_t rowCounter = 0;
	u_int8_t colCounter = 0;

	for(int i = 0; i < boardSize; i++){

		if (rowCounter >= squareSize) { rowSquare = !rowSquare; rowCounter = 0; }

		colSquare = true; colCounter = 0; // for some reason colCounter set itself to the value of 20 on the frist iteration, I don't know why so I reset it here
		for(int j = 0; j < boardSize; j++){

			if (colCounter >= squareSize) { colSquare = !colSquare; colCounter = 0; }

			if(rowSquare != colSquare)
				chess.at<cv::Vec3b>(i,j) = color1;
			else
				chess.at<cv::Vec3b>(i,j) = color2;
			colCounter++;
		}
		rowCounter++;
	}
	return chess;
}

int main(int argc, char** argv)
{
	cv::Mat gradHoriz;
	cv::Mat gradVert;
	gradHoriz.create(256,256,CV_8U);
	gradVert.create(256,256,CV_8U);
	
	u_int8_t t = 0;
	for(int i = 0; i < 256; i++) {
		for(int j = 0; j < 256; j++){
			gradHoriz.at<uchar>(i,j) = t;
			gradVert.at<uchar>(j,i) = t;
		}	
		t++;
	}

	cv::imshow("Horizontal Gradient", gradHoriz);
	cv::imshow("Vertical Gradient", gradVert);

	cv::Mat chess20 = chessBoard(300, 20, cv::Vec3b(255,120,30), cv::Vec3b(0,250,150));
	cv::Mat chess50 = chessBoard(300, 50, cv::Vec3b(20,120,255), cv::Vec3b(200,70,100));
	
	cv::imshow("chessboard 20", chess20);
	cv::imshow("chessboard 50", chess50);

	cv::waitKey(0);
	return 0;
}