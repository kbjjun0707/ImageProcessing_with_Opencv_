/*
	기본적인 이미지 로드, 저장과 화면 출력
*/
#include <opencv2\opencv.hpp>
#include <opencvLibs.h>			// 개인 설정

#include <iostream>

int main() {
	cv::Mat m_Img = cv::imread("sample.png");	// 이미지 불러오기
	// cv는 BGR의 이미지 채널을 사용
	// 한 채널의 크기는 8U(unsigned char)이고 변형 가능하다. (cv::Mat의 속성)
	// origin의 이름을 가진 윈도우 만듦
	cv::namedWindow("origin");
	// origin이라는 윈도우를 x=10, y=10인 위치로 이동
	cv::moveWindow("origin", 10, 10);
	// origin이라는 윈도우에 m_Img를 출력
	cv::imshow("origin", m_Img);
	// imshow만 해도 출력이 되긴 됨.

	// 회색이미지로 불러오기
	cv::Mat m_LoadGray = cv::imread("sample.png", cv::IMREAD_GRAYSCALE);
	cv::namedWindow("LoadGray");
	cv::moveWindow("LoadGray", 10 + 2*m_Img.cols, 10);
	cv::imshow("LoadGray", m_LoadGray);

	cv::Mat m_CvtGray;
	// 컬러로 부른 이미지에서 회색이미지로 변형
	cv::cvtColor(m_Img, m_CvtGray, cv::COLOR_BGR2GRAY);
	cv::namedWindow("CvtGray");
	cv::moveWindow("CvtGray", 10 + m_Img.cols, 10);
	cv::imshow("CvtGray", m_CvtGray);

	// 키보드 입력을 기다린다. 
	// 파라미터로 기다릴 시간을 밀리초 단위를 넣으며
	// 0은 무한히 기다림
	cv::waitKey(0);

	return 0;
}