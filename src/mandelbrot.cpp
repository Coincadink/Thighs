#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "Vulkan_mandelbrot_generator.hpp"
#include "lodepng.h"
#include <iostream>

int main() 
{
	const char* filename = "mandelbrot.png";

	int width = 1200;
	int height = 800;
	uint32_t workgroup_size = 32;

	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	GLFWwindow* window = glfwCreateWindow(width, height, "Vulkan", nullptr, nullptr);

	Vulkan_mandelbrot_generator generator = Vulkan_mandelbrot_generator{width, height, workgroup_size};
	VkInstance instance = generator.generate();

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		// drawFrame();
	}
}
