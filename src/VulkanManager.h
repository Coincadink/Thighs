#ifndef VULKANMANAGER_HPP
#define VULKANMANAGER_HPP

#define VULKAN_HPP_NO_CONSTRUCTORS
#include <vulkan/vulkan.hpp>

#include <vector>
#include <cstdint>

class VulkanManager 
{
public:
    VulkanManager(int width, int height, uint32_t workgroup_size);
    ~VulkanManager();

    void initVulkan();

private:
    struct Workgroup_size
    {
        std::uint32_t x;
        std::uint32_t y;
    };

    int width;
    int height;
    Workgroup_size workgroupSize;

    vk::Instance instance{};

    #ifndef NDEBUG
    vk::DebugUtilsMessengerEXT debugUtilsMessenger{};
    #endif

    vk::PhysicalDevice physicalDevice{};
    vk::Device device{};
    vk::Queue queue{};
    std::uint32_t queueFamilyIndex{};

    vk::Buffer storageBuffer{};
    vk::DeviceMemory storageBufferMemory{};
    vk::Buffer uniformBuffer{};
    vk::DeviceMemory uniformBufferMemory{};

    vk::DescriptorSetLayout descriptorSetLayout{};
    vk::DescriptorPool descriptorPool{};
    std::vector<vk::DescriptorSet> descriptorSets{};

    vk::PipelineLayout pipelineLayout{};
    vk::Pipeline pipeline{};

    vk::CommandPool commandPool{};
    vk::CommandBuffer commandBuffer{};

    void createInstance();
    
    #ifndef NDEBUG
    void setupDebugUtilsMessenger();
    #endif

    void findPhysicalDevice();

    void cleanup();

    static std::vector<const char*> getLayers();
    static std::vector<const char*> getExtensions();
};
#endif
