#pragma once

#include <cstdint>
#include <eventpp/utilities/scopedremover.h>
#include <memory>
#include <string>

#include "surface/game_window.h"
#include "surface/glfw_context.h"
#include "surface/vulkan_context.h"

namespace texplr {

enum ApplicationState {
    CREATED,
    INITIALIZING,
    INITIALIZED,
    RUNNING,
    STOPPING,
    STOPPED,
    DESTROYED
};

struct ApplicationSpecification {
    std::string name;
    std::string appVersion;
    std::string engineVersion;

    uint16_t width;
    uint16_t height;
    bool isResizable;
};

class Application {
public:
    Application(const ApplicationSpecification& specs);
    ~Application();

    void init();
    void run();
    void stop();
    void destroy();

    std::shared_ptr<GameWindow> getWindow() const;

    const ApplicationState& getState() const;
    const ApplicationSpecification& getSpecs() const;

private:
    ApplicationState m_state;
    ApplicationSpecification m_specs;

    std::unique_ptr<VulkanContext> m_vulkanContext;
    std::unique_ptr<GLFWContext> m_glfwContext;
    std::shared_ptr<GameWindow> m_window;

    void OnWindowClose(const GameWindow& window);
    void OnWindowResize(const GameWindow& window);

    eventpp::ScopedRemover<GameWindow> m_windowEvents;
};

} // namespace texplr
