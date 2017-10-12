// Robin Kalia
// robinkalia@berkeley.edu
// Proj: EinsteinTesla

#include <stdio.h>
#include <iostream>

#include <Image.h>

using namespace einsteintesla::vision;

void Image::SetImageParams(const std::vector<Pixel>& buffer, const uint32_t& height, const uint32_t& width, const uint32_t& depth)
{
	int32_t image_dims = width * height;
	int32_t buffer_size = buffer.size();
	if ((image_dims != img_size) && ((depth == Image::GRAY_DEPTH) || (depth == Image::COLOR_DEPTH))) {
		std::string errMsg = "The input image's buffer size is not the same as the expected allocation based on its width, height and depth";
		throw InvalidImageException(errMsg);
	}
	this.buffer_ = buffer;
	this.width_ = width;
	this.height_ = height;
	this.depth_ = depth;
}


void Image::CopyTo(Image& img) {
	img.SetImageParams(this.buffer_, this.height_, this.width_, this.depth_);
}


void Image::CopyFrom(const Image& img) {
	this.SetImageParams(img.buffer_, img.height_, img.width_, img.depth_);
}