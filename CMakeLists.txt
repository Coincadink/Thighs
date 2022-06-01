cmake_minimum_required(VERSION 3.21)
project(Thighs VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 20)

set(glm_DIR "C:/Libraries/glm/cmake/glm")

find_package(Vulkan REQUIRED)
find_package(glm REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(dependencies/glfw)

add_executable(thighs src/main.cpp src/Vulkan_interface.cpp)
target_link_libraries(thighs Vulkan::Vulkan glm::glm glfw)

configure_file(shaders/comp.spv shaders/comp.spv COPYONLY)