cmake_minimum_required(VERSION 3.21)
project(VulkanMandelbrot)

set(CMAKE_CXX_STANDARD 20)

find_package(Vulkan REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(dependencies/glfw)

add_subdirectory(dependencies/glm)

add_executable(mandelbrot src/mandelbrot.cpp src/lodepng.cpp src/Vulkan_mandelbrot_generator.cpp)
target_link_libraries(mandelbrot Vulkan::Vulkan glfw glm::glm)

configure_file(shaders/comp.spv shaders/comp.spv COPYONLY) 