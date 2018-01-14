// Robin Kalia
// robinkalia@berkeley.edu
// Proj: EinsteinTesla

#include <iostream>

#include "Image.h" 

using namespace einsteintesla::vision;

enum RETURN_VALUES { ARGUMENT_ERROR = -1, SUCCESS = 0 };

int32_t main(int32_t argc, char *argv[]) {

	if (argc < 2)	{
		std::cout << "Einstein Tesla Computer Vision Library 1.0\n"
			<< "<Usage>: ET_ComputerVision.exe <Image File in bmp or png format>";

		return ARGUMENT_ERROR;
	}

	std::string img_file = std::string(argv[1]);

	// Load Image file into Image object
	Image img(img_file);

	// Perform Computer Vision Operations

	return SUCCESS;	
}