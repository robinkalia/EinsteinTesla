// Robin Kalia
// robinkalia@berkeley.edu
// Project: EinsteinTesla -> Computer Vision Library


#include <stdio.h>
#include <iostream>
#include <stdint.h>

namespace einsteintesla {
	namespace vision {

		class Pixel
		{
		private:
			uint8_t r_, g_, b_;

		public:
			Pixel(const uint8_t& r0 = 0, const uint8_t& g0 = 0, const uint8_t& b0 = 0) : r_(r0), g_(g0), b_(b0) {
			}

			Pixel(const Pixel& pixel) : r_(pixel.r_), g_(pixel.g_), b_(pixel.b_) {
			}

			~Pixel() {
				this->r_ = this->g_ = this->b_ = 0;
			}

			Pixel operator= (const Pixel& p) {
				this->CopyFrom(p);
				return *this;
			}

			uint8_t GetGrayValue() const;
			uint8_t GetColorValue(const uint32_t& color_index) const;
			void GetAllColorValues(uint8_t& r_val, uint8_t& g_val, uint8_t& b_val) const;

			void SetColorValues(const uint8_t& r_set, const uint8_t& g_set, const uint8_t& b_set);
			void SetGrayValue(const uint8_t& gray_val);

			void CopyTo(Pixel& p) const;
			void CopyFrom(const Pixel& p);
		};

	}
}
