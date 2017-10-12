// Robin Kalia
// robinkalia@berkeley.edu
// Proj: EinsteinTesla


#include <stdio.h>
#include <iostream>

#include <Pixel.h>

using namespace einsteintesla::vision;

uint8_t Pixel::GetGrayValue() 
{
	return (this.r_ + this.g_ + this.b_)/3;
}


uint8_t Pixel::GetColorValue(const uint32_t& color_index) 
{
	switch(color_index) {
		case 0:
			return this.r_;
		case 1:
			return this.g_;
		case 2:
			return this.b_;
		default:
			std::string errMsg = std::string(color_index) + " is not a valid color pixel index. Valid values::=> 0 (red), 1(green), 2(blue)." 		
			throw InvalidPixelException(errMsg)
	}

	return 0;
}


void Pixel::GetAllColorValues(uint8_t& r_val, uint8_t& g_val, uint8_t& b_val)
{
	r_val = this.r_;
	g_val = this.g_;
	b_val = this.b_;
}


void Pixel::SetColorValues(const uint8_t& r_set, const uint8_t& g_set, const uint8_t& b_set)
{
	this.r_ = r_set;
	this.g_ = g_set;
	this.b_ = b_set;
}


void Pixel::SetGrayValue(const uint8_t& gray_val)
{
	this.r_ = this.b_ = this.g_ = gray_val;
}


void Pixel::CopyTo(Pixel& pixel)
{
	pixel.SetColorValues(this.r_, this.g_, this.b_);
}


void Pixel::copyFrom(const Pixel& pixel)
{
	this.SetColorValues(pixel.r_, pixel.g_, pixel.b_);
}
