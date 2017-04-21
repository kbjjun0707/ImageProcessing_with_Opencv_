/*
	����ȭ, ������׷� ���, ������׷� ��Ȱȭ ���� ����
*/
#include <opencv2\opencv.hpp>
#include <opencvLibs.h>			// ���� ����

#include <iostream>

int main() {
	cv::Mat m_Img = cv::imread("humming_bird.jpg", cv::IMREAD_GRAYSCALE);
	cv::namedWindow("org");
	cv::moveWindow("org", 10, 10);
	cv::imshow("org", m_Img);

	// ���� ����ȭ
	// �⺻ 8U�� ������ ����ִ� �̹����� ��谪(m_ThresholdVal)�� ������ �ִ밪 �ƴϸ� 0
	cv::Mat m_BinaryImg;
	double m_ThresholdVal = 110.0, m_MaxVal = 255.0;
	cv::threshold(m_Img, m_BinaryImg, m_ThresholdVal, m_MaxVal, cv::THRESH_BINARY);
	cv::namedWindow("Binary");
	cv::moveWindow("Binary", 10 + m_Img.cols, 10);
	cv::imshow("Binary", m_BinaryImg);

	cv::Mat m_Hist;		// ���� ���� ��Ƶ� ��
	// BGR BGR �ΰ��� �̹����� �ִ� ġ��, ù��° �̹����� B �ι�° �̹����� G�� ����ϰ�ʹٸ�,
	// 012 345 �ε����̱� ������ {0, 4}�� �ִ´�.
	const int channel_numbers[] = { 0 };	// ȸ���̹����� �ϳ��� ä���̱⶧���� 
	float channel_range[] = { 0.0 , 255.0 };	// 
	const float *channel_rnages[] = { channel_range };
	int number_bins = 255;
	cv::calcHist(&m_Img, 1, channel_numbers, cv::Mat(), m_Hist, 1, &number_bins, channel_rnages);

	// �����͸� �׷����� ������ ��� Mat�� �����(����� �̹���)
	cv::Mat m_HistGraphImg(255, m_Hist.rows, CV_32FC1, cv::Scalar(255));
	double min, max;
	cv::minMaxLoc(m_Hist, &min, &max);	// m_Hist���� �ִ밪�� �ּҰ��� ã�´�.
	for (int i = 0; i < m_HistGraphImg.rows; i++) {
		// ������ �������� 0,0�� ���̰� �׸� �׷����� �� ���� 0�� ���� �׷����̴�.
		// ��� Mat�� ũ��� 255x255�̱� ������ ���� �󵵼��� 0~255�� �ȿ� ���� ���̴�. ���⼱ �ִ� �ִ밡 240���� �׸� ���̴�.
		cv::line(m_HistGraphImg, cv::Point(i, 255), cv::Point(i, 255 - (m_Hist.at<float>(i, 0) / max)*240), cv::Scalar(0));
	}
	cv::namedWindow("Histogram");
	cv::moveWindow("Histogram", 10, 10 + m_Img.rows);
	cv::imshow("Histogram", m_HistGraphImg);

	// ������׷� ��Ȱȭ
	cv::Mat m_EqualizeHistImg;
	cv::equalizeHist(m_Img, m_EqualizeHistImg);
	cv::namedWindow("Equalized");
	cv::moveWindow("Equalized", 10 + m_HistGraphImg.cols, 10 + m_Img.rows);
	cv::imshow("Equalized", m_EqualizeHistImg);

	// ��Ȱȭ�� �̹��� ����.
	cv::imwrite("save.png", m_EqualizeHistImg);
	
	cv::waitKey();

	return 0;
}