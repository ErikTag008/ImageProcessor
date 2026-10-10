#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>
#include "ImageProcessor.h"
#include <algorithm>
#include <cctype>
#include <string>
#include <opencv2/core/mat.hpp>
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
		std::cin >> manipulationInput;
		manipulationInput = static_cast<unsigned char>(std::tolower((manipulationInput)));
	} while (std::find(admissableChars.begin(), admissableChars.end(), manipulationInput) == admissableChars.end());

	return manipulationInput;
}

void SaveImage(cv::Mat image, std::string path)
{
	if (!cv::imwrite(path, image))
	{
		std::cerr << "Failed to Save the Processed Image" << std::endl;
	}
}

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
	

	

	auto manipulationInput = GetManipulationInput();

	ImageProcessor processor;
	cv::Mat processedImage{ };

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
		processedImage = processor.BlurImage(image, 5);
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
	std::cin >> allowSave;
	if (std::tolower(allowSave) != 'n')
	{
		std::cout << "\nPlease input the path with the name to save to: ";
		std::string path;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, path);
		std::cout << "Saving to: [" << path << "]\n";
		SaveImage(processedImage, path);
	}
	return 0;
}
