// Robin Kalia
// robinkalia@berkeley.edu
// Proj: EinsteinTesla


#include <stdio.h>
#include <iostream>

#include <Pixel.h>

namespace einsteintesla::vision {

class Image {
	private:
		std::vector<Pixel> buffer_;
		uint32_t width_;
		uint32_t height_;
		uint32_t depth_;

	public:

		static const int32_t COLOR_DEPTH = 3;
		static const int32_t GRAY_DEPTH = 1;

		Image(): width_(-1), height_(-1), depth_(-1) {
		}

		Image(const Image& img) {
			this.SetImageParams(img.buffer_, img.height_, img.width_, img.depth_);
		}

		~Image() {
			this.buffer_.clear();
			this.width_ = this.height_ = this.depth_ = -1;
		}

		Image(const std::string& img_file, const int32_t& depth = 0 /*Color Mode*/) {
			this.LoadImage(img_file, depth);
		}

		void operator= (const Image& img) {
			this.CopyFrom(img);
		}

		void SetImageParams(const std::vector<Pixel>& buffer, const uint32_t& height, const uint32_t& width, const uint32_t& depth);

		Pixel GetPixel(int32_t row, int32_t col);

		void CopyTo(Image& img);
		void CopyFrom(const Image& p);

		// Input Operations
		void LoadImage(const std::string& img_file, const int32_t& depth = 0 /*Color Mode*/);
		
		// Basic Computer Vision Operations
		void Erode(const Image& kernel);
		void Dilate(const Image& kernel);

		void Filter(const Image& filter);

		void GenerateColorHistogram(std::vector<std::vector<uint64_t>>& img_color_hist);
		void GenerateGrayHistogram(std::vector<uint64_t>& img_gray_hist);
};


}
