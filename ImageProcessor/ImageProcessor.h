#pragma once
#include <opencv2/core/mat.hpp>

class ImageProcessor
{
private:
	cv::Mat RemoveColorInImage(const cv::Mat& image, int colorIndex);


	template<typename Action>
	void ManipulateEachPixel(cv::Mat& image, Action action);
public:
	cv::Mat GrayscaleImage(const cv::Mat&  image);
	cv::Mat BlurImage(const cv::Mat& image, unsigned radius = 1);
	cv::Mat RemoveBlueInImage(const cv::Mat& image);
	cv::Mat RemoveGreenInImage(const cv::Mat& image);
	cv::Mat RemoveRedInImage(const cv::Mat& image);


};