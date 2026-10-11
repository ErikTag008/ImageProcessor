#include "ImageProcessor.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>
#include <string>
#include <opencv2/core/utils/logger.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

unsigned char GetManipulationInput()
{
	std::cout << "Input what manipulation should be done." << std::endl;
	unsigned char manipulationInput{ };
	std::string admissableChars = "xyzgb";
	do
	{
		std::cout << "X - remove blue; Y - remove green; Z - remove red; G - grayscale; B - blur" << std::endl;
		if (!(std::cin >> manipulationInput))
		{
			std::cerr << "Failed to read the manipulation choice" << std::endl;
			return '\0';
		}
		manipulationInput = static_cast<unsigned char>(std::tolower((manipulationInput)));
	} while (std::find(admissableChars.begin(), admissableChars.end(), manipulationInput) == admissableChars.end());

	return manipulationInput;
}

void SaveImage(const cv::Mat& image, const std::string& path)
{
	try
	{
		if (!cv::imwrite(path, image))
		{
			std::cerr << "Failed to save the processed image" << std::endl;
		}
	}
	catch (const cv::Exception& error)
	{
		std::cerr << "Failed to save the processed image: " << error.what() << std::endl;
	}
}

int main()
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_WARNING);
	std::string path{};
	std::cout << "Please Input the Image Path: ";
	if (!std::getline(std::cin, path))
	{
		std::cerr << "Failed to read the image path" << std::endl;
		return 1;
	}

	cv::Mat image = cv::imread(path);
	if (image.empty())
	{
		std::cerr << "Failed to load the image" << std::endl;
		return 1;
	}
	

	

	auto manipulationInput = GetManipulationInput();
	if (!std::cin) return 1;
	ImageProcessor processor;
	cv::Mat processedImage{ };

	unsigned radius{};
	switch (manipulationInput)
	{
	case 'x':
		processedImage = processor.RemoveBlueInImage(image);
		break;
	case 'y':
		processedImage = processor.RemoveGreenInImage(image);
		break;
	case 'z':
		processedImage = processor.RemoveRedInImage(image);
		break;
	case 'g':
		processedImage = processor.GrayscaleImage(image);
		break;
	case 'b':
		std::cout << "Please Input the Radius of the Blur(recommended 1 - 20): ";
		if (!(std::cin >> radius))
		{
			std::cerr << "Failed to read the blur radius" << std::endl;
			return 1;
		}
		processedImage = processor.BlurImage(image, radius);
		break;
	default:
		std::cerr<<"Processor was unable to find the correct manipulation!";
		break;
	}

	if (processedImage.empty())
	{
		std::cerr << "Failed to show the processed image" << std::endl;
		return 1;
	}

	std::string windowName = "Processed Image";
	
	cv::namedWindow(windowName, cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO);
	cv::resizeWindow(windowName, 1280, 720);
	cv::imshow(windowName, processedImage);
	
	cv::waitKey(0);
	cv::destroyAllWindows();
	std::cout << "Do you want to save the processed Image?" << std::endl;
	std::cout << "Y/N: ";
	unsigned char allowSave{};
	if (!(std::cin >> allowSave))
	{
		std::cerr << "Failed to read the save choice" << std::endl;
		return 1;
	}
	if (std::tolower(allowSave) == 'y')
	{
		std::cout << "\nPlease input the path with the name to save to: ";
		std::string path;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (!std::getline(std::cin, path))
		{
			std::cerr << "Failed to read the output path" << std::endl;
			return 1;
		}
		std::cout << "Saving to: [" << path << "]\n";
		SaveImage(processedImage, path);
	}
	return 0;
}
