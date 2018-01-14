// Robin Kalia
// robinkalia@berkeley.edu
// Proj: EinsteinTesla

#include <stdio.h>
#include <iostream>
#include <exception>


#include "Image.h"

using namespace einsteintesla::vision;

void Image::SetImageParams(const std::vector<Pixel>& buffer, uint32_t height, const uint32_t width, uint8_t depth)
{
	int32_t image_dims = width * height * depth;
	int32_t buffer_size = buffer.size();
	if ((image_dims != buffer_size) || ((depth != Image::GRAY_DEPTH) && (depth != Image::COLOR_DEPTH))) {
		std::string errMsg = "The input image's buffer size is not the same as the expected allocation based on its width, height and depth";
		throw std::exception(errMsg.c_str());
	}

	this->buffer_ = buffer;
	this->width_ = width;
	this->height_ = height;
	this->depth_ = depth;
}


void Image::CopyTo(Image& img) const 
{
	img.SetImageParams(this->buffer_, this->height_, this->width_, this->depth_);
}


void Image::CopyFrom(const Image& img) 
{
	this->SetImageParams(img.buffer_, img.height_, img.width_, img.depth_);
}


void Image::Filter(const uint8_t filterType, const uint32_t filterSize)
{
	if (filterSize % 2 == 0) {
		std::cout << "Filter size should be an odd number as filters are odd in size";
		return;
	}
	
	uint32_t filterWidth = filterSize;
	uint32_t filterHeight = filterSize;
	uint64_t numPixelsFiltered = filterWidth * filterHeight;

	uint8_t filterDepth = Image::GRAY_DEPTH;

	Image filter(filterWidth, filterHeight, filterDepth);
	// Generate the contents of filter depending upon the filter type

	uint8_t imgDepth = (this->depth_ == Image::COLOR_DEPTH) ? 3 : 0;
	Image filteredImage(*this);

	
	for (int32_t h = 0; h < this->height_; ++h) {
		for (int32_t w = 0; w < this->width_; w++) {
			std::vector<int32_t> pixelValues;
			for (int32_t d = 0; d < imgDepth; ++d) {
				uint64_t filteredSum = 0;
				for (int32_t fh = -filterHeight/2; fh < filterHeight/2; ++fh) {
					for (int32_t fw = -filterWidth/2; fw < filterWidth/2; ++fw) {
						if ((h + fh >= 0) && (h + fh < this->height_) && (w + fw >= 0) && (w + fw < this->width_)) {
							filteredSum += this->buffer_[this->width_ * h + w].GetColorValue(d) * filter.buffer_[filterWidth*(fh + filterHeight/2) + fw + filterWidth/2].GetColorValue(0);
						}
					}
				}
				pixelValues.push_back(filteredSum / numPixelsFiltered);
			}
			if (imgDepth==0)
				filteredImage.buffer_[this->width_*h + w].SetColorValues(pixelValues[0], pixelValues[1], pixelValues[2]);
			else
				filteredImage.buffer_[this->width_*h + w].SetColorValues(pixelValues[0], pixelValues[0], pixelValues[0]);
		}
	}

	this->SetImageParams(filteredImage.buffer_, filteredImage.width_, filteredImage.height_, filteredImage.depth_);
}