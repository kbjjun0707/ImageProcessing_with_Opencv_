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
	// 1, 2�� �̹����� Ű ����Ʈ�� pts1, pts2�� ��Ƽ�� �÷ο�� ��ġ��Ű��
	// ���°� ���� ���鸦 refinedPts1, refinedPts2�� ��´�.
	// refinedPts���� ��ġ ������ ��ȯ.
	m_Optical.opticalMatch(m_Gray1, m_Gray2, m_Pts1, m_Pts2,
		m_Pts1, m_Pts2, m_Matches);

	// ��Ƽ�÷� ���� ������ ������ ��Ī���� ����.
	cv::Mat m_MatchedImg;
	cv::KeyPoint::convert(m_Pts1, m_Kpts1);
	cv::KeyPoint::convert(m_Pts2, m_Kpts2);
	cv::drawMatches(m_Img1, m_Kpts1, m_Img2, m_Kpts2, m_Matches, m_MatchedImg);

	cv::namedWindow("match");
	cv::moveWindow("match", 10, 35 + m_Img1.rows);
	cv::imshow("match", m_MatchedImg);


	// ��Ƽ�÷� ���� ������ ������ �帧�� ������ �׷� ��Ÿ������.
	// (2������ 1�������� �� �̵�)
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


	// ������ �帧(��ȭ��)���� ��ȯ����� ���� 2���̹����� ���� ���Ѻ���.
	// �� �������ٸ� 1���� ����� �̹����� �����ž� �Ѵ�.
	cv::Mat m_WarpImg;
	cv::Mat m_RigidTransform = cv::estimateRigidTransform(m_Img2, m_Img1, true);
	cv::warpAffine(m_Img2, m_WarpImg, m_RigidTransform, cv::Size());
	cv::namedWindow("warp");
	cv::moveWindow("warp", 10 + m_Img1.cols * 2, 35 + m_FlowImg.rows);
	cv::imshow("warp", m_WarpImg);



	cv::waitKey();


	return 0;
}