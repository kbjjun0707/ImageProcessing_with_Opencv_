/*
	�⺻���� �̹��� �ε�, ����� ȭ�� ���
*/
#include <opencv2\opencv.hpp>
#include <opencvLibs.h>			// ���� ����

#include <iostream>

int main() {
	cv::Mat m_Img = cv::imread("sample.png");	// �̹��� �ҷ�����
	// cv�� BGR�� �̹��� ä���� ���
	// �� ä���� ũ��� 8U(unsigned char)�̰� ���� �����ϴ�. (cv::Mat�� �Ӽ�)
	// origin�� �̸��� ���� ������ ����
	cv::namedWindow("origin");
	// origin�̶�� �����츦 x=10, y=10�� ��ġ�� �̵�
	cv::moveWindow("origin", 10, 10);
	// origin�̶�� �����쿡 m_Img�� ���
	cv::imshow("origin", m_Img);
	// imshow�� �ص� ����� �Ǳ� ��.

	// ȸ���̹����� �ҷ�����
	cv::Mat m_LoadGray = cv::imread("sample.png", cv::IMREAD_GRAYSCALE);
	cv::namedWindow("LoadGray");
	cv::moveWindow("LoadGray", 10 + 2*m_Img.cols, 10);
	cv::imshow("LoadGray", m_LoadGray);

	cv::Mat m_CvtGray;
	// �÷��� �θ� �̹������� ȸ���̹����� ����
	cv::cvtColor(m_Img, m_CvtGray, cv::COLOR_BGR2GRAY);
	cv::namedWindow("CvtGray");
	cv::moveWindow("CvtGray", 10 + m_Img.cols, 10);
	cv::imshow("CvtGray", m_CvtGray);

	// Ű���� �Է��� ��ٸ���. 
	// �Ķ���ͷ� ��ٸ� �ð��� �и��� ������ ������
	// 0�� ������ ��ٸ�
	cv::waitKey(0);

	return 0;
}