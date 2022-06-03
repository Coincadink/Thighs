#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class Application
{
public:
    void run()
    {
        initWindow();
        mainLoop();
        cleanup();
    }
private:
    void initWindow()
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    }

    void mainLoop()
    {
        while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();
		}

        drawFrame();
    }

    void drawFrame()
    {
        
    }
    
    void cleanup()
    {
        glfwDestroyWindow(window);
		glfwTerminate();
    }

    // Member Variables

    GLFWwindow* window;
};

int main()
{
    Application app;

    try
    {
        app.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}