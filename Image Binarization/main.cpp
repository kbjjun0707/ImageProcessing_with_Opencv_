/*
	이진화, 히스토그램 출력, 히스토그램 평활화 영상 저장
*/
#include <opencv2\opencv.hpp>
#include <opencvLibs.h>			// 개인 설정

#include <iostream>

int main() {
	cv::Mat m_Img = cv::imread("humming_bird.jpg", cv::IMREAD_GRAYSCALE);
	cv::namedWindow("org");
	cv::moveWindow("org", 10, 10);
	cv::imshow("org", m_Img);

	// 영상 이진화
	// 기본 8U의 정보를 담고있는 이미지를 경계값(m_ThresholdVal)을 넘으면 최대값 아니면 0
	cv::Mat m_BinaryImg;
	double m_ThresholdVal = 110.0, m_MaxVal = 255.0;
	cv::threshold(m_Img, m_BinaryImg, m_ThresholdVal, m_MaxVal, cv::THRESH_BINARY);
	cv::namedWindow("Binary");
	cv::moveWindow("Binary", 10 + m_Img.cols, 10);
	cv::imshow("Binary", m_BinaryImg);

	cv::Mat m_Hist;		// 값을 구해 담아둘 곳
	// BGR BGR 두개의 이미지가 있다 치고, 첫번째 이미지의 B 두번째 이미지의 G를 계산하고싶다면,
	// 012 345 인덱싱이기 때문에 {0, 4}를 넣는다.
	const int channel_numbers[] = { 0 };	// 회색이미지의 하나의 채널이기때문에 
	float channel_range[] = { 0.0 , 255.0 };	// 
	const float *channel_rnages[] = { channel_range };
	int number_bins = 255;
	cv::calcHist(&m_Img, 1, channel_numbers, cv::Mat(), m_Hist, 1, &number_bins, channel_rnages);

	// 데이터를 그래프로 보여줄 결과 Mat를 만든다(흰색의 이미지)
	cv::Mat m_HistGraphImg(255, m_Hist.rows, CV_32FC1, cv::Scalar(255));
	double min, max;
	cv::minMaxLoc(m_Hist, &min, &max);	// m_Hist에서 최대값고 최소값을 찾는다.
	for (int i = 0; i < m_HistGraphImg.rows; i++) {
		// 영상은 왼쪽위가 0,0인 곳이고 그릴 그래프는 맨 밑이 0인 막대 그래프이다.
		// 결과 Mat의 크기는 255x255이기 떄문에 색의 빈도수를 0~255의 안에 넣을 것이다. 여기선 최대 최대가 240으로 그릴 것이다.
		cv::line(m_HistGraphImg, cv::Point(i, 255), cv::Point(i, 255 - (m_Hist.at<float>(i, 0) / max)*240), cv::Scalar(0));
	}
	cv::namedWindow("Histogram");
	cv::moveWindow("Histogram", 10, 10 + m_Img.rows);
	cv::imshow("Histogram", m_HistGraphImg);

	// 히스토그램 평활화
	cv::Mat m_EqualizeHistImg;
	cv::equalizeHist(m_Img, m_EqualizeHistImg);
	cv::namedWindow("Equalized");
	cv::moveWindow("Equalized", 10 + m_HistGraphImg.cols, 10 + m_Img.rows);
	cv::imshow("Equalized", m_EqualizeHistImg);

	// 평활화된 이미지 저장.
	cv::imwrite("save.png", m_EqualizeHistImg);
	
	cv::waitKey();

	return 0;
}