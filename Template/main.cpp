#include <opencv2\opencv.hpp>
#include <opencvLibs.h>

int main() {
	cv::Mat m_ImgAlpha	= cv::imread("alphabet.bmp");
	cv::Mat m_ImgA		= cv::imread("A.bmp");
	cv::Mat m_ImgB		= cv::imread("b.bmp");
	cv::Mat m_ImgM		= cv::imread("m.bmp");
	cv::Mat m_ImgS		= cv::imread("s.bmp");

	cv::Mat res, tmp;
	res = m_ImgAlpha.clone();

	cv::Point leftTopA, leftTopB, leftTopM, leftTopS;

	cv::matchTemplate(m_ImgAlpha, m_ImgA, tmp, cv::TM_CCOEFF_NORMED);
	cv::minMaxLoc(tmp, 0, 0, 0, &leftTopA);

	cv::matchTemplate(m_ImgAlpha, m_ImgB, tmp, cv::TM_CCOEFF_NORMED);
	cv::minMaxLoc(tmp, 0, 0, 0, &leftTopB);

	cv::matchTemplate(m_ImgAlpha, m_ImgM, tmp, cv::TM_CCOEFF_NORMED);
	cv::minMaxLoc(tmp, 0, 0, 0, &leftTopM);

	cv::matchTemplate(m_ImgAlpha, m_ImgS, tmp, cv::TM_CCOEFF_NORMED);
	cv::minMaxLoc(tmp, 0, 0, 0, &leftTopS);

	cv::rectangle(res, 
		leftTopA, cv::Point(leftTopA.x + m_ImgA.cols, leftTopA.y + m_ImgA.rows), 
		cv::Scalar(255, 0, 0));
	cv::rectangle(res,
		leftTopB, cv::Point(leftTopB.x + m_ImgB.cols, leftTopB.y + m_ImgB.rows),
		cv::Scalar(0, 255, 0));

	cv::rectangle(res,
		leftTopM, cv::Point(leftTopM.x + m_ImgM.cols, leftTopM.y + m_ImgM.rows),
		cv::Scalar(0, 0, 255));

	cv::rectangle(res,
		leftTopS, cv::Point(leftTopS.x + m_ImgS.cols, leftTopS.y + m_ImgS.rows),
		cv::Scalar(200, 0, 200));

	cv::namedWindow("alphabet");
	cv::moveWindow("alphabet", 10, 10);
	cv::imshow("alphabet", res);

	cv::waitKey(0);

	return 0;
}