#include <opencv2\opencv.hpp>
#include <opencvLibs.h>

#include <iostream>
using namespace std;

int main() {
	cv::Mat m_SrcImg = cv::imread("lena_256_pop5_rie.png");
	cv::namedWindow("Source Image");
	cv::imshow("Source Image", m_SrcImg);
	cv::waitKey(0);
	
	// Èæ¹é ½ºÄÉÄ¡
	cv::Mat m_DstImg;
	cv::Mat m_Gray;

	cv::cvtColor(m_SrcImg, m_Gray, CV_BGR2GRAY);
	const int MEDIAN_BLUR_FILTER_SIZE = 7;
	cv::medianBlur(m_Gray, m_Gray, MEDIAN_BLUR_FILTER_SIZE);
	cv::imshow("blur", m_Gray);
	cv::waitKey(0);
	cv::destroyWindow("blur");

	cv::Mat m_Edge;
	const int LAPLACIAN_FILTER_SIZE = 5;
	cv::Laplacian(m_Gray, m_Edge, CV_8U, LAPLACIAN_FILTER_SIZE);
	cv::imshow("edge", m_Edge);
	cv::waitKey(0);
	cv::destroyWindow("edge");

	cv::Mat m_Mask;
	const int EDGES_THRESHOLD = 80;
	cv::threshold(m_Edge, m_Mask, EDGES_THRESHOLD, 255, CV_THRESH_BINARY_INV);
	cv::imshow("threshold", m_Edge);
	cv::imshow("mask", m_Mask);
	cv::waitKey(0);
	cv::destroyWindow("threshold");
	cv::destroyWindow("mask");



	return 0;
}