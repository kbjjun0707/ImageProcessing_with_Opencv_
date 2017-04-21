/*
	Edge 검출, 비디오 재생, 비디오 저장.
*/
#include <opencv2\opencv.hpp>
#include <opencvLibs.h>			// 개인 설정

#include <iostream>


int main() {
	// 비디오를 열 객체 생성. 카메라도 열수 있다.
	cv::VideoCapture m_Video;
	if (!m_Video.open("Wildlife.wmv")) {
		std::cout << "동영상 없음" << std::endl;
		return -1;
	}

	// 비디오의 정보
	int m_Fourcc = m_Video.get(cv::CAP_PROP_FOURCC);
	char m_FourccChar[5] = { 0 };
	memcpy(m_FourccChar, &m_Fourcc, sizeof(char) * 4);
	int m_Fps = m_Video.get(cv::CAP_PROP_FPS);
	cv::Size m_FramSize;

	cv::Mat m_Frame, m_FrameEdge;
	cv::namedWindow("video");
	cv::moveWindow("video", 150, 100);
	// 영상에서 프레임 추출, 자동으로 다음으로 이동
	m_Video >> m_Frame;
	m_FramSize = m_Frame.size();

	// 비디오 정보 출력
	std::cout 
		<< "fourcc : " << m_FourccChar << std::endl
		<< "size : " << m_FramSize << std::endl
		<< "fps : " << m_Fps << std::endl;

	cv::VideoWriter m_VideoWriter(
		"Edge Detect.avi",		// 영상 이름
		0,						// 코덱 0은 무압축 코덱이 설치 되어있다면
								// 다른 코덱도 사용가능
		m_Fps,					// 영상의 fps
		m_FramSize,				// 영상크기
		true					// 저장영상이 컬리인가
	);
	// Edge 검출한 이미지는 흑백이라 false를 넣었는데 파일 저장 후 열어볼 때,
	// 에러가 있었다. gray->bgr로 변환 후 컬러로 저장하니까 해결되어 그렇게 함.
	// 코덱이 없어 무압축이라 용량이 엄청 커진다.

	while (!m_Frame.empty()) {
		// 그래이스캐일을 한 후 Canny Edge 검출
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