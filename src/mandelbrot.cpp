#include "Vulkan_mandelbrot_generator.hpp"
#include "lodepng.h"
#include <iostream>

void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height) {
  //Encode the image
  unsigned error = lodepng::encode(filename, image, width, height);

  //if there's an error, display it
  if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

int main() 
{
  const char* filename = "mandelbrot.png";

  int width = 1200;
  int height = 1200;
  // Max size for intel integrated 520 is 32.
  uint32_t workgroup_size = 32;

  auto raw_image = std::vector<unsigned char>{};
  raw_image = Vulkan_mandelbrot_generator{width, height, workgroup_size}.generate();

//   std::cout << "P3\n" << width << " " << height << "\n255\n";
//   for (int i = 0; i < raw_image.size(); i++) 
//   {
//       std::cout << static_cast<unsigned int>(raw_image[i]);
//   }

  encodeOneStep(filename, raw_image, width, height);
}
