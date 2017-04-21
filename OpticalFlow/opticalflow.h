#pragma once

#include <opencv2\opencv.hpp>
#include <vector>

namespace jun {

	class Opt {

		cv::Ptr<cv::FastFeatureDetector> m_Ffd;

	public:

		Opt();
		~Opt();

		void detectFeature(const cv::Mat &grayimg,
			std::vector<cv::KeyPoint> &kpts,
			std::vector<cv::Point2f> &pts);

		bool chkGray(const cv::Mat &src, cv::Mat &dst = cv::Mat());

		void opticalMatch(cv::Mat &preGray, cv::Mat &posGray,
			std::vector<cv::Point2f> &ptsL, std::vector<cv::Point2f> &ptsR,
			std::vector<cv::Point2f> &refinedptsL, std::vector<cv::Point2f> &refinedptsR,
			std::vector<cv::DMatch> &matches);

		void calcFlow(const cv::Mat &src, cv::Mat &flow,
			std::vector<cv::Point2f> &ptsL, std::vector<cv::Point2f> &ptsR,
			const std::vector<cv::DMatch> &matches = std::vector<cv::DMatch>());



	};

}