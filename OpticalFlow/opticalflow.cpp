#include "opticalflow.h"


jun::Opt::Opt() {
	m_Ffd = cv::FastFeatureDetector::create();
}

jun::Opt::~Opt() {
	m_Ffd.release();
}

void jun::Opt::detectFeature(const cv::Mat & grayimg,
	std::vector<cv::KeyPoint>& kpts,
	std::vector<cv::Point2f>& pts) {

	kpts.clear();
	pts.clear();
	m_Ffd->detect(grayimg, kpts);
	cv::KeyPoint::convert(kpts, pts);
}

bool jun::Opt::chkGray(const cv::Mat &src, cv::Mat &dst) {
	if (src.channels() == 1) {
		dst = src.clone();
		return true;
	} else {
		cv::cvtColor(src, dst, cv::COLOR_BGR2GRAY);
		return false;
	}
}

void jun::Opt::opticalMatch(cv::Mat &preGray, cv::Mat &posGray,
	std::vector<cv::Point2f> &ptsL, std::vector<cv::Point2f> &ptsR,
	std::vector<cv::Point2f> &refinedptsL, std::vector<cv::Point2f> &refinedptsR,
	std::vector<cv::DMatch> &matches) {

	std::vector<uchar> status;
	std::vector<float> errors;

	std::vector<cv::Point2f> ptsL_ = ptsL, ptsR_ = ptsR;
	cv::calcOpticalFlowPyrLK(preGray, posGray, ptsL_, ptsR_, status, errors);

	refinedptsL.clear();
	refinedptsR.clear();
	for (unsigned int i = 0; i < status.size(); i++) {
		if (status[i] && (errors[i] < 6.0)) {
			refinedptsL.push_back(ptsL_[i]);
			refinedptsR.push_back(ptsR_[i]);
		} else {
			status[i] = 0;
		}
	}

	cv::Mat refineL_flat = cv::Mat(refinedptsL).
		reshape(1, refinedptsL.size());

	cv::Mat refineR_flat = cv::Mat(refinedptsR).
		reshape(1, refinedptsR.size());

	cv::BFMatcher matcher(CV_L2);
	std::vector<std::vector<cv::DMatch>> nearest_neighbors;
	matches.clear();

	matcher.radiusMatch(
		refineL_flat,
		refineR_flat,
		nearest_neighbors,
		2.0f
	);

	std::set<int> found_in_right_points;
	for (int i = 0; i < nearest_neighbors.size(); i++) {
		cv::DMatch _m;
		if (nearest_neighbors[i].size() == 1) {
			_m = nearest_neighbors[i][0];
		} else if (nearest_neighbors[i].size() >1) {
			double ratio = nearest_neighbors[i][0].distance /
				nearest_neighbors[i][1].distance;
			if (ratio < 0.7) {
				_m = nearest_neighbors[i][0];
			} else {
				continue;
			}
		} else {
			continue;
		}
		matches.push_back(_m);
	}
}

void jun::Opt::calcFlow(const cv::Mat & src, cv::Mat &flow,
	std::vector<cv::Point2f> &ptsL, std::vector<cv::Point2f> &ptsR,
	const std::vector<cv::DMatch> &matches) {

	flow = cv::Mat(src.size(), CV_32FC2, cv::Scalar(0));

	if (matches.size() > 0) {
		for (cv::DMatch it : matches) {
			cv::Point2f pl = ptsL[it.queryIdx];
			cv::Point2f pr = ptsR[it.trainIdx];
			flow.at<cv::Point2f>(pl) = pr - pl;
		}
	} else {
		for (int i = 0; i < ptsL.size(); i++) {
			cv::Point2f pl = ptsL[i];
			cv::Point2f pr = ptsR[i];
			flow.at<cv::Point2f>(pl) = pr - pl;
		}
	}
}
