/*
	윈도우에 트랙바 만들기
	이진화, 디졸브 합성
*/
#include <opencv2\opencv.hpp>
#include <opencvLibs.h>			// 개인 설정

#include <iostream>


void binTracker(int val, void *data) {
	cv::Mat l_Img = *(cv::Mat *)data;
	cv::Mat l_Res;
	cv::threshold(l_Img, l_Res, val, 255, cv::THRESH_BINARY);
	cv::imshow("binary", l_Res);
}

// 두 이미지를 담고있는 구조체
class PairImg {
public:
	cv::Mat A, B;
	PairImg(const cv::Mat &a, const cv::Mat &b) {
		A = a.clone();
		B = b.clone();
	}
};

void dissolveTracker(int val, void *data) {
	PairImg l_Data = *(PairImg *)data;
	double alpha = (double)val / 100;
	double beta = (1.0 - alpha);

	if (l_Data.A.size() != l_Data.B.size()) {
		cv::resize(l_Data.B, l_Data.B, l_Data.A.size());
	}

	cv::Mat l_Res;
	// 두 이미지의 크기가 같아야한다.
	// A와 B를 alpha : beta 비로 섞어서 준다.
	cv::addWeighted(l_Data.A, alpha, l_Data.B, beta, 1.0, l_Res);
	cv::imshow("dissolve", l_Res);
}

int main() {
	cv::Mat m_Img = cv::imread("flower.jpg", cv::IMREAD_GRAYSCALE);
	cv::namedWindow("binary");
	cv::moveWindow("binary", 10, 10);

	int m_ThresholdVal = 128;
	// 트랙바의 이름, 위치할 윈도우의 이름, 트랙바의 위치를 담을 변수, 최대값,
	// 작동을 할 함수, 넘겨줄 void * 를 넣어 트랙바를 만든다.
	cv::createTrackbar("임계값", "binary", &m_ThresholdVal, 255, binTracker, &m_Img);
	// 초기 생성하면 트랙바의 기능이 적용되어있지 않아 작동을 한번 시켜준다.
	binTracker(m_ThresholdVal, &m_Img);

	// 트랙바 함수에 데이터를 넘겨줄 때 (void *)하나라 두 이미지를 넘겨주기 위해
	// 불러온 두 이미지를 하나의 구조체에 담는다.
	PairImg datas(cv::imread("bike.jpg"), cv::imread("holse.JPG"));
	cv::namedWindow("dissolve");
	cv::moveWindow("dissolve", 10 + m_Img.cols + 20, 10);

	int m_DissolveVal = 50;
	cv::createTrackbar("혼합계수", "dissolve", &m_DissolveVal, 100, dissolveTracker, &datas);
	dissolveTracker(m_DissolveVal, &datas);

	cv::waitKey();

	return 0;
}