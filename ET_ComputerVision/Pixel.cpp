// Robin Kalia
// robinkalia@berkeley.edu
// Proj: EinsteinTesla


#include <stdio.h>
#include <iostream>
#include <string>

#include "Pixel.h"

using namespace einsteintesla::vision;

uint8_t Pixel::GetGrayValue() const
{
	return (this->r_ + this->g_ + this->b_)/3;
}


uint8_t Pixel::GetColorValue(const uint32_t& color_index) const
{
	switch(color_index) {
		case 0:
			return this->r_;
		case 1:
			return this->g_;
		case 2:
			return this->b_;
		default:
			std::string errMsg = std::to_string(color_index) + " is not a valid color pixel index. Valid values::=> 0 (red), 1(green), 2(blue).";
			return -1;
	}
}


void Pixel::GetAllColorValues(uint8_t& r_val, uint8_t& g_val, uint8_t& b_val) const
{
	r_val = this->r_;
	g_val = this->g_;
	b_val = this->b_;
}


void Pixel::SetColorValues(const uint8_t& r_set, const uint8_t& g_set, const uint8_t& b_set)
{
	this->r_ = r_set;
	this->g_ = g_set;
	this->b_ = b_set;
}


void Pixel::SetGrayValue(const uint8_t& gray_val)
{
	this->r_ = this->b_ = this->g_ = gray_val;
}


void Pixel::CopyTo(Pixel& pixel) const
{
	pixel.SetColorValues(this->r_, this->g_, this->b_);
}


void Pixel::CopyFrom(const Pixel& pixel)
{
	this->SetColorValues(pixel.GetColorValue(0), pixel.GetColorValue(1), pixel.GetColorValue(2));
}
