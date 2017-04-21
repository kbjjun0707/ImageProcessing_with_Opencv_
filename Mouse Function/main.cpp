/*
	마우스 함수, ROI(Region Of Interest, 관심영역) 지정
*/
#include <opencv2\opencv.hpp>
#include <opencvLibs.h>

#include <iostream>

class Datas {
public:
	cv::Mat m_Img, m_Roi;
	int		pressX, pressY;
	bool	isPress, isROI;
	Datas(const cv::Mat &img = cv::Mat()) {
		this->m_Img = img.clone();
		pressX = 0; pressY = 0;
		isPress = false; isROI = false;
	}
};

void onMouse(int evt, int x, int y, int flags, void *data) {
	Datas &l_datas = *(Datas *)data;
	cv::Mat l_Img = l_datas.m_Img.clone();
	int sx, sy, width = 0, heigh = 0;
	
	switch (evt) {
	case CV_EVENT_LBUTTONDOWN:
		l_datas.isROI = false;
		l_datas.isPress = true;

		l_datas.pressX = x;
		l_datas.pressY = y;
		break;

	case CV_EVENT_MOUSEMOVE:
		if (!l_datas.isPress) return;

		// x, y 를 이미지 안의 좌표로 맞춤.
		if (x > l_Img.cols) x = l_Img.cols;
		else if (x < 0) x = 0;
		if (y > l_Img.rows) y = l_Img.rows;
		else if (y < 0) y = 0;

		// sx, sy는 사각형 시작 점, cv::Rect는 폭이 양수인거만 됨
		sx = (l_datas.pressX < x) ? l_datas.pressX : x;
		sy = (l_datas.pressY < y) ? l_datas.pressY : y;
		width = abs(x - l_datas.pressX); heigh = abs(y - l_datas.pressY);

		l_datas.m_Roi = l_Img(cv::Rect(sx, sy, width, heigh));
		l_datas.m_Roi = ~l_datas.m_Roi;
		break;

	case CV_EVENT_LBUTTONUP:
		l_datas.isROI = true;
		l_datas.isPress = false;
		break;

	default:
		break;
	}

	cv::imshow("org", l_Img);
	if (l_datas.isROI) {
		cv::imshow("ROI", ~l_datas.m_Roi);
	} else {
		cv::destroyWindow("ROI");
	}
}

int main() {
	cv::Mat m_Img = cv::imread("flower.jpg");
	cv::Mat m_Roi;

	Datas m_Datas(m_Img);

	cv::namedWindow("org");
	cv::moveWindow("org", 10, 10);
	cv::imshow("org", m_Img);
	cv::setMouseCallback("org", onMouse, &m_Datas);

	cv::namedWindow("ROI");
	cv::moveWindow("ROI", 10 + m_Img.cols + 15, 10);
	cv::destroyWindow("ROI");

	cv::waitKey();

	return 0;
}