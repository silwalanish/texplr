#include "texplr/core/surface/vulkan_context.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

namespace texplr {

VulkanContext::VulkanContext(const VulkanSpecification& specs)
    : m_specs(specs)
{
}

VulkanContext::~VulkanContext()
{
}

void VulkanContext::init()
{
    VkApplicationInfo appInfo {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.apiVersion = VK_API_VERSION_1_2;
    appInfo.pApplicationName = m_specs.appName.c_str();
    appInfo.pEngineName = m_specs.engineName.c_str();

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> requiredExtensions;
    for (uint32_t i = 0; i < glfwExtensionCount; i++) {
        requiredExtensions.emplace_back(glfwExtensions[i]);
    }
    requiredExtensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

    std::vector<const char*> validationLayers;

    #ifndef NDEBUG
        validationLayers.emplace_back("VK_LAYER_KHRONOS_validation");
    #endif

    VkInstanceCreateInfo createInfo {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
    createInfo.ppEnabledExtensionNames = requiredExtensions.data();
    createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
    createInfo.ppEnabledLayerNames = validationLayers.data();
    createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

    VkResult result = vkCreateInstance(&createInfo, nullptr, (VkInstance*)&m_instance);

    if (result != VK_SUCCESS) {
        throw std::runtime_error("Failed to create vulkan instance!");
    }
}

void VulkanContext::destroy()
{
    vkDestroyInstance((VkInstance)m_instance, nullptr);
}

const VulkanSpecification& VulkanContext::getSpecs() const
{
    return m_specs;
}

} // namespace texplr
