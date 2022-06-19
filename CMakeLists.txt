cmake_minimum_required(VERSION 3.21)
project(VulkanMandelbrot)

set(CMAKE_CXX_STANDARD 20)

find_package(Vulkan REQUIRED)

add_subdirectory(dependencies/glm)

add_executable(mandelbrot src/mandelbrot.cpp src/lodepng.cpp src/Vulkan_mandelbrot_generator.cpp)
target_link_libraries(mandelbrot Vulkan::Vulkan glm::glm)

configure_file(shaders/comp.spv shaders/comp.spv COPYONLY)