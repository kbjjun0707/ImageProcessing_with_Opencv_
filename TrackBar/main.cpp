/*
	�����쿡 Ʈ���� �����
	����ȭ, ������ �ռ�
*/
#include <opencv2\opencv.hpp>
#include <opencvLibs.h>			// ���� ����

#include <iostream>


void binTracker(int val, void *data) {
	cv::Mat l_Img = *(cv::Mat *)data;
	cv::Mat l_Res;
	cv::threshold(l_Img, l_Res, val, 255, cv::THRESH_BINARY);
	cv::imshow("binary", l_Res);
}

// �� �̹����� ����ִ� ����ü
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
	// �� �̹����� ũ�Ⱑ ���ƾ��Ѵ�.
	// A�� B�� alpha : beta ��� ��� �ش�.
	cv::addWeighted(l_Data.A, alpha, l_Data.B, beta, 1.0, l_Res);
	cv::imshow("dissolve", l_Res);
}

int main() {
	cv::Mat m_Img = cv::imread("flower.jpg", cv::IMREAD_GRAYSCALE);
	cv::namedWindow("binary");
	cv::moveWindow("binary", 10, 10);

	int m_ThresholdVal = 128;
	// Ʈ������ �̸�, ��ġ�� �������� �̸�, Ʈ������ ��ġ�� ���� ����, �ִ밪,
	// �۵��� �� �Լ�, �Ѱ��� void * �� �־� Ʈ���ٸ� �����.
	cv::createTrackbar("�Ӱ谪", "binary", &m_ThresholdVal, 255, binTracker, &m_Img);
	// �ʱ� �����ϸ� Ʈ������ ����� ����Ǿ����� �ʾ� �۵��� �ѹ� �����ش�.
	binTracker(m_ThresholdVal, &m_Img);

	// Ʈ���� �Լ��� �����͸� �Ѱ��� �� (void *)�ϳ��� �� �̹����� �Ѱ��ֱ� ����
	// �ҷ��� �� �̹����� �ϳ��� ����ü�� ��´�.
	PairImg datas(cv::imread("bike.jpg"), cv::imread("holse.JPG"));
	cv::namedWindow("dissolve");
	cv::moveWindow("dissolve", 10 + m_Img.cols + 20, 10);

	int m_DissolveVal = 50;
	cv::createTrackbar("ȥ�հ��", "dissolve", &m_DissolveVal, 100, dissolveTracker, &datas);
	dissolveTracker(m_DissolveVal, &datas);

	cv::waitKey();

	return 0;
}