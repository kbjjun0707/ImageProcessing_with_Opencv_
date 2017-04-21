#include <opencv2\opencv.hpp>
#include <opencvLibs.h>

#include "opticalflow.h"

int main() {

	cv::Mat m_Img1, m_Img2;
	cv::Mat m_Gray1, m_Gray2;
	jun::Opt m_Optical;

	m_Img1 = cv::imread("stereo001L.jpg");
	m_Img2 = cv::imread("stereo001R.jpg");
	cv::resize(m_Img1, m_Img1, cv::Size(), 0.5, 0.5);
	cv::resize(m_Img2, m_Img2, cv::Size(), 0.5, 0.5);

	cv::namedWindow("img1");
	cv::moveWindow("img1", 10, 10);
	cv::namedWindow("img2");
	cv::moveWindow("img2", 10 + m_Img1.cols, 10);

	cv::imshow("img1", m_Img1);
	cv::imshow("img2", m_Img2);

	m_Optical.chkGray(m_Img1, m_Gray1);
	m_Optical.chkGray(m_Img2, m_Gray2);

	std::vector<cv::KeyPoint> m_Kpts1, m_Kpts2;
	std::vector<cv::Point2f> m_Pts1, m_Pts2;

	m_Optical.detectFeature(m_Gray1, m_Kpts1, m_Pts1);
	m_Optical.detectFeature(m_Gray2, m_Kpts2, m_Pts2);

	std::vector<cv::DMatch> m_Matches;
	// 1, 2번 이미지의 키 포인트들 pts1, pts2를 옵티컬 플로우로 매치시키고
	// 상태가 좋은 점들를 refinedPts1, refinedPts2에 담는다.
	// refinedPts들의 매치 정보를 반환.
	m_Optical.opticalMatch(m_Gray1, m_Gray2, m_Pts1, m_Pts2,
		m_Pts1, m_Pts2, m_Matches);

	// 옵티컬로 구한 양쪽의 점들을 매칭시켜 본다.
	cv::Mat m_MatchedImg;
	cv::KeyPoint::convert(m_Pts1, m_Kpts1);
	cv::KeyPoint::convert(m_Pts2, m_Kpts2);
	cv::drawMatches(m_Img1, m_Kpts1, m_Img2, m_Kpts2, m_Matches, m_MatchedImg);

	cv::namedWindow("match");
	cv::moveWindow("match", 10, 35 + m_Img1.rows);
	cv::imshow("match", m_MatchedImg);


	// 옵티컬로 구한 양쪽의 점들의 흐름을 선으로 그려 나타내본다.
	// (2번에서 1번으로의 점 이동)
	cv::Mat flow;
	m_Optical.calcFlow(m_Img1, flow, m_Pts1, m_Pts2);

	cv::Mat m_FlowImg = m_Img2.clone();
	for (int r = 0; r < m_FlowImg.rows; r++) {
		for (int c = 0; c < m_FlowImg.cols; c++) {
			cv::Point2f p0(c, r);
			cv::Point2f p1 = flow.at<cv::Point2f>(p0);
			if (p1 != cv::Point2f(0, 0))
				cv::arrowedLine(m_FlowImg, p0 + p1, p0, cv::Scalar(0, 200, 0));
		}
	}
	cv::namedWindow("flow");
	cv::moveWindow("flow", 10 + m_Img1.cols * 2, 10);
	cv::imshow("flow", m_FlowImg);


	// 점들의 흐름(변화량)으로 변환행렬을 구해 2번이미지를 와프 스켜본다.
	// 잘 구해졌다면 1번과 비슷한 이미지로 와프돼야 한다.
	cv::Mat m_WarpImg;
	cv::Mat m_RigidTransform = cv::estimateRigidTransform(m_Img2, m_Img1, true);
	cv::warpAffine(m_Img2, m_WarpImg, m_RigidTransform, cv::Size());
	cv::namedWindow("warp");
	cv::moveWindow("warp", 10 + m_Img1.cols * 2, 35 + m_FlowImg.rows);
	cv::imshow("warp", m_WarpImg);



	cv::waitKey();


	return 0;
}