/*
	영상에 문자를 넣어본다.
*/
#include <opencv2\opencv.hpp>
#include <opencvLibs.h>			// 개인 설정

#include <iostream>

int main() {
	cv::Mat m_Img = cv::imread("humming_bird.jpg");
	cv::namedWindow("origin");
	cv::moveWindow("origin", 10, 10);
	cv::imshow("origin", m_Img);

	cv::Mat m_ImgClone = m_Img.clone();
	// 문자를 입력할 이미지, 입력할 문자, 텍스트박스의 왼쪽 아래 점, 글꼴, 굵기, 문자의 색
	cv::putText(m_ImgClone, "Hello, bird!", cv::Point(55, 55), 
		cv::HersheyFonts::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(255, 255, 255));

	cv::namedWindow("Input Text Img");
	cv::moveWindow("Input Text Img", 10 + m_Img.cols, 10);
	cv::imshow("Input Text Img", m_ImgClone);

	cv::waitKey();

	return 0;
}