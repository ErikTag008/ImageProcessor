#include "ImageProcessor.h"
#include <opencv2/core/matx.hpp>
#include <opencv2/core/utility.hpp>

cv::Mat ImageProcessor::RemoveColorInImage(const cv::Mat& image, int colorIndex)
{
	if (colorIndex > 2) return image;
	cv::Mat processedImage = image.clone();
	ManipulateEachPixel(processedImage, [colorIndex](cv::Vec3b& pixel)
		{
			pixel[colorIndex] = 0;
		});

	return processedImage;
}


template<typename Action>
void ImageProcessor::ManipulateEachPixel(cv::Mat& image, Action action)
{
	image.forEach<cv::Vec3b>([action](cv::Vec3b& pixel, const int*) 
		{
			action(pixel);
		});
}

cv::Mat ImageProcessor::GrayscaleImage(const cv::Mat& image)
{
	cv::Mat processedImage = image.clone();
	ManipulateEachPixel(processedImage, [](cv::Vec3b& pixel)
		{
			double grey = pixel[0] * 0.114 + pixel[1] * 0.587 + pixel[2] * 0.299;
			unsigned char intensity = static_cast<unsigned char>(grey);
			pixel[0] = intensity;
			pixel[1] = intensity;
			pixel[2] = intensity;
		});
	return processedImage;
}
cv::Mat ImageProcessor::BlurImage(const cv::Mat& image, double strength)
{
	cv::Mat processedImage = image.clone();
	return processedImage;
}
cv::Mat ImageProcessor::RemoveBlueInImage(const cv::Mat& image)
{
	return RemoveColorInImage(image, 0);
}

cv::Mat ImageProcessor::RemoveGreenInImage(const cv::Mat& image)
{
	return RemoveColorInImage(image, 1);
}

cv::Mat ImageProcessor::RemoveRedInImage(const cv::Mat& image)
{
	return RemoveColorInImage(image, 2);
}