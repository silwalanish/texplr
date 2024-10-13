#pragma once

namespace texplr {

struct VulkanSpecification {
};

class VulkanContext {
public:
    VulkanContext(const VulkanSpecification& specs);
    ~VulkanContext();

    void init();
    void destroy();

    const VulkanSpecification& getSpecs() const;

private:
    VulkanSpecification m_specs;
};

} // namespace texplr
