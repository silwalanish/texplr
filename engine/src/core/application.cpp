#include <texplr/core/application.h>

#include <chrono>

namespace texplr {

Application::Application(const ApplicationSpecification& specs)
    : m_specs(specs)
    , m_state(ApplicationState::CREATED)
{
    m_glfwContext = std::make_unique<GLFWContext>(GLFWSpecification {});
    m_window = std::make_shared<GameWindow>(WindowSpecification { m_specs.width, m_specs.height, m_specs.name });
    m_vulkanContext = std::make_unique<VulkanContext>(VulkanSpecification {});
    m_windowEvents = eventpp::ScopedRemover<GameWindow>(*m_window.get());
}

Application::~Application()
{
    destroy();
}

void Application::init()
{
    m_state = ApplicationState::INITIALIZING;

    m_glfwContext->init();
    m_window->init();
    m_vulkanContext->init();

    m_windowEvents.appendListener(WindowEvents::WINDOW_CLOSE, std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

    m_state = ApplicationState::INITIALIZED;
}

void Application::run()
{
    m_state = ApplicationState::RUNNING;

    std::chrono::steady_clock::time_point startTime = std::chrono::high_resolution_clock::now();
    std::chrono::steady_clock::time_point currentTime;
    float deltaTime = 0.0f;

    while (m_state == ApplicationState::RUNNING) {
        m_glfwContext->pollEvents();

        currentTime = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
        startTime = currentTime;
    }

    m_state = ApplicationState::STOPPED;
}

void Application::stop()
{
    m_state = ApplicationState::STOPPING;
}

void Application::destroy()
{
    if (m_state != ApplicationState::DESTROYED) {
        m_windowEvents.reset();

        m_vulkanContext->destroy();
        m_window->destroy();
        m_glfwContext->destroy();

        m_state = ApplicationState::DESTROYED;
    }
}

std::shared_ptr<GameWindow> Application::getWindow() const
{
    return m_window;
}

const ApplicationState& Application::getState() const
{
    return m_state;
}

const ApplicationSpecification& Application::getSpecs() const
{
    return m_specs;
}

void Application::OnWindowClose(const GameWindow& window)
{
    if (&window == m_window.get()) {
        this->stop();
    }
}

} // namespace texplr
