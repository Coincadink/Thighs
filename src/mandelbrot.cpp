#include "Vulkan_mandelbrot_generator.hpp"
#include <iostream>

int main() 
{
  int width = 6000;
  int height = 4000;

  auto raw_image = std::vector<unsigned char>{};
  raw_image = Vulkan_mandelbrot_generator{width, height}.generate();

  int pixelTest = -1;

  std::cout << "P3\n" << width << " " << height << "\n255\n";
  for (int i = 0; i < raw_image.size(); i++) 
  {
      int index = i % 3;
      if (index == 0) pixelTest ++;

      if (!(pixelTest % 4 == 0)) std::cout << static_cast<unsigned int>(raw_image[i]) << " ";
  }
}
