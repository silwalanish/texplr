#include <texplr/core/surface/game_window.h>

#include <GLFW/glfw3.h>
#include <stdexcept>

namespace texplr {

static void closeCallback(GLFWwindow* handle)
{
    GameWindow* window = static_cast<GameWindow*>(glfwGetWindowUserPointer(handle));
    window->dispatch(WindowEvents::WINDOW_CLOSE, *window);
}

GameWindow::GameWindow(const WindowSpecification& specs)
    : m_specs(specs)
{
}

GameWindow::~GameWindow()
{
}

void GameWindow::init()
{
    if (!m_specs.isResizable) {
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    }

    m_handle = glfwCreateWindow(static_cast<int>(m_specs.width), static_cast<int>(m_specs.height), m_specs.title.c_str(), nullptr, nullptr);

    if (!m_handle) {
        throw new std::runtime_error("Couldn't create a window!");
    }

    glfwSetWindowUserPointer((GLFWwindow*)m_handle, this);
    glfwSetWindowCloseCallback((GLFWwindow*)m_handle, &closeCallback);

    glfwSetCursorPos((GLFWwindow*)m_handle, 0, 0);
}

void GameWindow::destroy()
{
    if (m_handle) {
        glfwDestroyWindow((GLFWwindow*)m_handle);
        m_handle = nullptr;
    }
}

void* GameWindow::getNativeHandle() const
{
    return m_handle;
}

const WindowSpecification& GameWindow::getSpecs() const
{
    return m_specs;
}

} // namespace texplr
