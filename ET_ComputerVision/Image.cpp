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


void Image::Filter(uint8_t filterType, uint32_t filterSize)
{
	if (filterSize % 2 == 0 || filterSize <= 0) {
		std::cout << "Filter size should be a positive odd number as filters are odd in size" << std::endl;
		return;
	}
	
	uint32_t filterWidth = filterSize;
	uint32_t filterHeight = filterSize;
	uint64_t numPixelsFiltered = filterWidth * filterHeight;

	uint8_t filterDepth = Image::GRAY_DEPTH;

	Image filter(filterWidth, filterHeight, filterDepth);
	// Generate the contents of filter depending upon the filter type

	Image filteredImage(filterWidth, filterHeight, Image::COLOR_DEPTH);
	
	for (int32_t h = 0; h < this->height_; ++h) {
		for (int32_t w = 0; w < this->width_; w++) {
			std::vector<uint8_t> pixelValues;
			for (int32_t d = 0; d < this->depth_; ++d) {
				uint64_t filteredSum = 0;
				for (int32_t fh = -1 * filterHeight/2; fh < filterHeight/2; ++fh) {
					for (int32_t fw = -1 * filterWidth/2; fw < filterWidth/2; ++fw) {
						if ((h + fh >= 0) && (h + fh < this->height_) && (w + fw >= 0) && (w + fw < this->width_)) {
							filteredSum += this->buffer_[this->width_ * (h + fh) + w + fw].GetColorValue(d) * filter.buffer_[filterWidth*(fh + filterHeight/2) + fw + filterWidth/2].GetColorValue(0);
						}
					}
				}
				pixelValues.push_back(uint8_t(filteredSum / numPixelsFiltered));
			}

			if (this->depth_ == Image::COLOR_DEPTH) {
				filteredImage.buffer_[this->width_*h + w].SetColorValues(pixelValues[0], pixelValues[1], pixelValues[2]);
			} else {
				filteredImage.buffer_[this->width_*h + w].SetColorValues(pixelValues[0], pixelValues[0], pixelValues[0]);
			}
		}
	}

	this->SetImageParams(filteredImage.buffer_, filteredImage.width_, filteredImage.height_, filteredImage.depth_);
}


void Image::Erode(const Image& kernel) {
	this->ApplyMorphologicalFilter(kernel);
}

void Image::Dilate(const Image& kernel) {
	this->ApplyMorphologicalFilter(kernel, false);
}

void Image::ApplyMorphologicalFilter(const Image& kernel, bool erodeCond) 
{
	if ((kernel.width_ <= 0) || (kernel.height_ <= 0) || (kernel.width_ % 2 == 1) || (kernel.height_%2 == 1)) {
		std::cout << "Kernel dimensions should be positive odd numbers as kernels have odd dimensions";
		return;
	}

	int32_t kernelWidth = kernel.width_;
	int32_t kernelHeight = kernel.height_;

	Image filteredImage(this->width_, this->height_, Image::GRAY_DEPTH);
	
	uint64_t numKernelColoredPixels = 0;
	if (erodeCond) {
		for (int32_t kh = 0; kh < kernelHeight; kh++)
			for (int32_t kw = 0; kw < kernelWidth; kw++) {
				Pixel kernelPixel = kernel.buffer_[kernelWidth * kh + kw];
				numKernelColoredPixels += ((kernelPixel.GetColorValue(0) > 0) || (kernelPixel.GetColorValue(1) > 0) ||											 (kernelPixel.GetColorValue(2) > 0)) ? 1 : 0;
			}
	}

	for (int32_t h = 0; h < this->height_; h++) {
		for (int32_t w = 0; w < this->width_; ++w) {
			uint64_t numMatchingPixels = 0;
			for (int32_t kh = -1 * kernelHeight / 2; kh < kernelHeight / 2; ++kh) {
				for (int32_t kw = -1 * kernelWidth / 2; kw < kernelWidth / 2; ++kw) {
					if ((h + kh >= 0) || (h + kh < this->height_) || (w + kw >= 0) || (w + kw < this->width_)) {
						Pixel kernelPixel = kernel.buffer_[kernelWidth * (kh + kernelHeight / 2) + kw + kernelWidth / 2];
						bool validKernelPixel = ((kernelPixel.GetColorValue(0) > 0) || (kernelPixel.GetColorValue(1)) || (kernelPixel.GetColorValue(2) > 0));
						Pixel corrImgPixel = this->buffer_[this->width_*(h + kh) + w + kw];
						bool validCorrImgPixel = ((corrImgPixel.GetColorValue(0) > 0) || (corrImgPixel.GetColorValue(1) > 0) || (corrImgPixel.GetColorValue(2) > 0));
						numMatchingPixels += (validKernelPixel && validCorrImgPixel) ? 1 : 0;
					}
				}
			}

			bool matchCond = (erodeCond) ? (numMatchingPixels == numKernelColoredPixels) : (numMatchingPixels > 0);
			if (matchCond) {
				Pixel imgPixel = this->buffer_[this->width_*h + w];
				filteredImage.buffer_[this->width_*h + w].SetColorValues(imgPixel.GetColorValue(0), imgPixel.GetColorValue(1), imgPixel.GetColorValue(2));
			}
		}
	}

	this->SetImageParams(filteredImage.buffer_, filteredImage.width_, filteredImage.height_, filteredImage.depth_);
}