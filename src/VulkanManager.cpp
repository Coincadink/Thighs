#include "VulkanManager.h"
#include <iostream>
#include <fstream>

// DEBUG MESSENGER

#ifndef NDEBUG
VKAPI_ATTR VkResult VKAPI_CALL vkCreateDebugUtilsMessengerEXT
(
    VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugUtilsMessengerEXT* pMessenger
)
{
    auto func = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));
    if (func)
    {
        return func(instance, pCreateInfo, pAllocator, pMessenger);
    }
    else { return VK_ERROR_EXTENSION_NOT_PRESENT; }
}

VKAPI_ATTR void VKAPI_CALL vkDestroyDebugUtilsMessengerEXT
(
    VkInstance instance,
    VkDebugUtilsMessengerEXT messenger,
    const VkAllocationCallbacks* pAllocator
)
{
    auto func = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"));
    if (func)
    {
        return func(instance, messenger, pAllocator);
    }
    // No need to error handle, if the extension is missing it will have errored out on creation.
}

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback
(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData
)
{
    std::cerr << pCallbackData -> pMessage << "\n";
    return VK_FALSE;
}
#endif

// UTILITY FUNCTIONS

/**
 * @brief Used to read data from a given file.
 * 
 * This function works by searching for the filename given to it, opening that file
 * from the back, and using that cursor location at the back to determine file size.
 * From this file size it creates an appropriately sized buffer and returns to the
 * start of the file from which it then streams the file data into that sized buffer
 * and returns it to the caller.
 * 
 * @param filename 
 * @return std::vector<char> 
 */
std::vector<char> readFile(const std::string& filename) 
{
    auto file = std::ifstream(filename, std::ios::ate | std::ios::binary);
    if (!file.is_open()) 
    {
        throw std::runtime_error("Failed to open the given file.");
    }

    auto fileSize = file.tellg();
    auto buffer = std::vector<char>(static_cast<std::size_t>(fileSize));

    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();

    return buffer;
}

VulkanManager::VulkanManager(int _width, int _height, uint32_t _workgroupSize) :
    width{_width}, 
    height{_height}, 
    workgroupSize{_workgroupSize, _workgroupSize}
{}

VulkanManager::~VulkanManager()
{
    cleanup();
}

void VulkanManager::initVulkan()
{
    createInstance();
    
    #ifndef NDEBUG
    setupDebugUtilsMessenger();
    #endif

    findPhysicalDevice();
}

void VulkanManager::createInstance()
{
    auto applicationInfo = vk::ApplicationInfo
    {
        .pApplicationName = "Thighs",
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName = "No Engine",
        .engineVersion = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion = VK_API_VERSION_1_0
    };

    #ifndef NDEBUG
    auto layerProperties = vk::enumerateInstanceLayerProperties();
    auto foundValidationLayer = std::ranges::any_of
    (
        layerProperties, 
        [](const auto& property)
        {
            return std::strcmp("VK_LAYER_KHRONOS_validation", property.layerName) == 0;
        }
    );
    if (!foundValidationLayer) 
    { 
        throw std::runtime_error("Validation layer requested but not available."); 
    }
    #endif

    auto layers = getLayers();
    auto extensions = getExtensions();
    auto instanceCreateInfo = vk::InstanceCreateInfo
    {
        .pApplicationInfo = &applicationInfo,
        .enabledLayerCount = static_cast<uint32_t>(layers.size()),
        .ppEnabledLayerNames = layers.data(),
        .enabledExtensionCount = static_cast<uint32_t>(extensions.size()),
        .ppEnabledExtensionNames = extensions.data()
    };

    instance = vk::createInstance(instanceCreateInfo);
}

void VulkanManager::setupDebugUtilsMessenger()
{
    auto severityFlags = vk::DebugUtilsMessageSeverityFlagsEXT
    {
        // vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
        vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo |
        vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
        vk::DebugUtilsMessageSeverityFlagBitsEXT::eError
    };
    auto messageTypeFlags = vk::DebugUtilsMessageTypeFlagsEXT
    {
        vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
        vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance |
        vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation
    };

    auto createInfo = vk::DebugUtilsMessengerCreateInfoEXT
    {
        .messageSeverity = severityFlags,
        .messageType = messageTypeFlags,
        .pfnUserCallback = debugCallback
    };

    debugUtilsMessenger = instance.createDebugUtilsMessengerEXT(createInfo);
}

void VulkanManager::findPhysicalDevice()
{
    auto physicalDevices = instance.enumeratePhysicalDevices();
    if (physicalDevices.empty())
    {
        throw std::runtime_error("Cannot find any physical devices.");
    }

    auto physicalDevice = pickPhysicalDevice(physicalDevices);
}

VkPhysicalDevice VulkanManager::pickPhysicalDevice(std::vector<vk::PhysicalDevice, std::allocator<vk::PhysicalDevice>> physicalDevices)
{
    for (auto physicalDevice : physicalDevices)
    {
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);
        VkPhysicalDeviceMemoryProperties memoryProperties;
        vkGetPhysicalDeviceMemoryProperties (physicalDevice, &memoryProperties);

        std::cout << "\n" <<  deviceProperties.deviceName << "\n";
        std::cout << deviceProperties.deviceType << "\n";
        std::cout << memoryProperties.memoryHeapCount << "\n";
        std::cout << memoryProperties.memoryHeaps << "\n";
        std::cout << memoryProperties.memoryTypeCount << "\n";
        std::cout << memoryProperties.memoryTypes << "\n";
    }

    return physicalDevices[0];
}

void VulkanManager::cleanup()
{
    #ifndef NDEBUG
    instance.destroyDebugUtilsMessengerEXT(debugUtilsMessenger);
    #endif
    instance.destroy();
}

std::vector<const char*> VulkanManager::getLayers()
{
    std::vector<const char*> layers;

    #ifndef NDEBUG
    layers.push_back("VK_LAYER_KHRONOS_validation");
    #endif

    return layers;
}

std::vector<const char*> VulkanManager::getExtensions()
{
    std::vector<const char*> extensions;

    #ifndef NDEBUG
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    #endif

    return extensions;
}
