#include "ImageProcessor.h"
#include <cstdint>
#include <iostream>
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
cv::Mat ImageProcessor::BlurImage(const cv::Mat& image, const unsigned radius)
{
	
	if (radius < 1) return image.clone();
	cv::Mat processedImage(image.size(), image.type());
	std::cout << "Please Wait While Blur is getting Applied..." << std::endl;
	const std::int64_t neighborhoodRadius = radius;
	auto maxBoxSize = neighborhoodRadius * 2 + 1;
	if (maxBoxSize > image.cols || maxBoxSize > image.rows)
	{
		std::cout << "Selected Radius is Too big. This might take a while..." << std::endl;
	}
	processedImage.forEach<cv::Vec3b>(
		[&image, neighborhoodRadius](cv::Vec3b& outputPixel, const int* position)
		{
			int row = position[0];
			int col = position[1];
			int firstRow = static_cast<int>(MAX(row - neighborhoodRadius, 0));
			int firstCol = static_cast<int>(MAX(col - neighborhoodRadius, 0));
			int lastRow = static_cast<int>(MIN(row + neighborhoodRadius, image.rows - 1));
			int lastCol = static_cast<int>(MIN(col + neighborhoodRadius, image.cols - 1));

			cv::Vec3i sum{ 0,0,0 };
			unsigned count = 0;
			for (int neighborRow = firstRow; neighborRow <= lastRow; neighborRow++)
			{
				for (int neighborCol = firstCol; neighborCol <= lastCol; neighborCol++)
				{
					const auto& currentPixel = image.at<cv::Vec3b>(neighborRow, neighborCol);
					sum[0] += currentPixel[0];
					sum[1] += currentPixel[1];
					sum[2] += currentPixel[2];
					++count;
				}
			}
			outputPixel[0] = sum[0] / count;
			outputPixel[1] = sum[1] / count;
			outputPixel[2] = sum[2] / count;
		}
	);
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

