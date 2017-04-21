/*
	Edge ����, ���� ���, ���� ����.
*/
#include <opencv2\opencv.hpp>
#include <opencvLibs.h>			// ���� ����

#include <iostream>


int main() {
	// ������ �� ��ü ����. ī�޶� ���� �ִ�.
	cv::VideoCapture m_Video;
	if (!m_Video.open("Wildlife.wmv")) {
		std::cout << "������ ����" << std::endl;
		return -1;
	}

	// ������ ����
	int m_Fourcc = m_Video.get(cv::CAP_PROP_FOURCC);
	char m_FourccChar[5] = { 0 };
	memcpy(m_FourccChar, &m_Fourcc, sizeof(char) * 4);
	int m_Fps = m_Video.get(cv::CAP_PROP_FPS);
	cv::Size m_FramSize;

	cv::Mat m_Frame, m_FrameEdge;
	cv::namedWindow("video");
	cv::moveWindow("video", 150, 100);
	// ���󿡼� ������ ����, �ڵ����� �������� �̵�
	m_Video >> m_Frame;
	m_FramSize = m_Frame.size();

	// ���� ���� ���
	std::cout 
		<< "fourcc : " << m_FourccChar << std::endl
		<< "size : " << m_FramSize << std::endl
		<< "fps : " << m_Fps << std::endl;

	cv::VideoWriter m_VideoWriter(
		"Edge Detect.avi",		// ���� �̸�
		0,						// �ڵ� 0�� ������ �ڵ��� ��ġ �Ǿ��ִٸ�
								// �ٸ� �ڵ��� ��밡��
		m_Fps,					// ������ fps
		m_FramSize,				// ����ũ��
		true					// ���念���� �ø��ΰ�
	);
	// Edge ������ �̹����� ����̶� false�� �־��µ� ���� ���� �� ��� ��,
	// ������ �־���. gray->bgr�� ��ȯ �� �÷��� �����ϴϱ� �ذ�Ǿ� �׷��� ��.
	// �ڵ��� ���� �������̶� �뷮�� ��û Ŀ����.

	while (!m_Frame.empty()) {
		// �׷��̽�ĳ���� �� �� Canny Edge ����
		cv::cvtColor(m_Frame, m_FrameEdge, cv::COLOR_BGR2GRAY);
		cv::Canny(m_FrameEdge, m_FrameEdge, 30, 100);
		
		cv::cvtColor(m_FrameEdge, m_FrameEdge, cv::COLOR_GRAY2BGR);
		m_VideoWriter << m_FrameEdge;
		cv::imshow("video", m_FrameEdge);
		if (cv::waitKey(1000 / m_Fps) == 27) break;
		m_Video >> m_Frame;
	}

	m_Video.release();
	m_VideoWriter.release();

	return 0;
}