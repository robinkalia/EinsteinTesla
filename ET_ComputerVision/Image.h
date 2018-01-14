// Robin Kalia
// robinkalia@berkeley.edu
// Project: EinsteinTesla -> Computer Vision Library


#include <stdio.h>
#include <iostream>
#include <vector>

#include "Pixel.h"

namespace einsteintesla {
	namespace vision {

		class Image {
		private:
			std::vector<Pixel> buffer_;
			uint32_t width_;
			uint32_t height_;
			uint8_t depth_;

		public:

			static const uint8_t COLOR_DEPTH = 3;
			static const uint8_t GRAY_DEPTH = 1;

			Image(): width_(-1), height_(-1), depth_(-1) {
			}

			Image(uint32_t w, uint32_t h, uint8_t d) : width_(w), height_(h), depth_(d) {
			}

			Image(const Image& img) {
				this->SetImageParams(img.buffer_, img.height_, img.width_, img.depth_);
			}

			~Image() {
				this->buffer_.clear();
				this->width_ = this->height_ = this->depth_ = -1;
			}

			Image(const std::string& img_file, uint8_t depth = 0 /*Color Mode*/) {
				this->LoadImage(img_file, depth);
			}

			Image operator= (const Image& img) {
				this->CopyFrom(img);
				return *this;
			}

			void SetImageParams(const std::vector<Pixel>& buffer, uint32_t height, uint32_t width, uint8_t depth);

			Pixel GetPixel(int32_t row, int32_t col);

			void CopyTo(Image& img) const;
			void CopyFrom(const Image& p);

			// Input Operations
			void LoadImage(const std::string& img_file, int32_t depth = 0 /*Color Mode*/);
		
			// Basic Computer Vision Operations
			void Erode(const Image& kernel);
			void Dilate(const Image& kernel);


			void Filter(uint8_t filter_type, uint32_t filterSize);

			void GenerateColorHistogram(std::vector<std::vector<uint64_t>>& img_color_hist);
			void GenerateGrayHistogram(std::vector<uint64_t>& img_gray_hist);
		};
	}
}
