#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>
int main()
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_WARNING);
	std::string path{};
	std::cout << "Please Input the Image Path: ";
	std::getline(std::cin, path);
	cv::Mat image = cv::imread(path);
	if (image.empty())
	{
		std::cerr << "Failed to load the image" << std::endl;
		return 1;
	}

	cv::imshow("Image Show", image);
	cv::waitKey(0);
	cv::destroyAllWindows();
	return 0;
}
