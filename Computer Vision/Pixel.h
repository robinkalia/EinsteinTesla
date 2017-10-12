// Robin Kalia
// robinkalia@berkeley.edu
// Proj: EinsteinTesla


#include <stdio.h>
#include <iostream>

namespace einsteintesla::vision {

class Pixel 
{
	private:
		uint8_t r, g, b;

	public:
		Pixel(const uint8_t& r0 = 0, const uint8_t& g0 = 0, const uint8_t& b0 = 0) : r(r0), g(g0), b(b0) {
		}

		Pixel(const Pixel& pixel): r_(pixel.r), g_(pixel.g), b_(pixel.b) {
		}

		~Pixel() {
		}

		void operator= (const Pixel& p) {
			this.CopyFrom(p);
		}

		uint8_t GetGrayValue();
		uint8_t GetColorValue(const uint32_t& color_index);
		void GetAllColorValues(uint8_t& r_val, uint8_t& g_val, uint8_t& b_val);

		void SetColorValues(const uint8_t& r_set, const uint8_t& g_set, const uint8_t& b_set);
		void SetGrayValue(const uint8_t& gray_val);

		void CopyTo(Pixel& p);
		void CopyFrom(const Pixel& p);
};

}
