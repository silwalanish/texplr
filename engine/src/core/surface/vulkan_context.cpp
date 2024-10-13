#include "texplr/core/surface/vulkan_context.h"

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
}

void VulkanContext::destroy()
{
}

const VulkanSpecification& VulkanContext::getSpecs() const
{
    return m_specs;
}

} // namespace texplr
