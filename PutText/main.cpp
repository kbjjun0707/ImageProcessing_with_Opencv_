/*
	���� ���ڸ� �־��.
*/
#include <opencv2\opencv.hpp>
#include <opencvLibs.h>			// ���� ����

#include <iostream>

int main() {
	cv::Mat m_Img = cv::imread("humming_bird.jpg");
	cv::namedWindow("origin");
	cv::moveWindow("origin", 10, 10);
	cv::imshow("origin", m_Img);

	cv::Mat m_ImgClone = m_Img.clone();
	// ���ڸ� �Է��� �̹���, �Է��� ����, �ؽ�Ʈ�ڽ��� ���� �Ʒ� ��, �۲�, ����, ������ ��
	cv::putText(m_ImgClone, "Hello, bird!", cv::Point(55, 55), 
		cv::HersheyFonts::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(255, 255, 255));

	cv::namedWindow("Input Text Img");
	cv::moveWindow("Input Text Img", 10 + m_Img.cols, 10);
	cv::imshow("Input Text Img", m_ImgClone);

	cv::waitKey();

	return 0;
}