#include "pch.h"
#include "window.h"

namespace Physx2D {
    WindowProps Window::properties = WindowProps();

    Window::Window(WindowProps props, uint32_t version_major, uint32_t version_minor) {
        properties = props;
        VERSION_MAJOR = version_major;
        VERSION_MINOR = version_minor;

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, VERSION_MAJOR);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, VERSION_MINOR);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

        #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif

        glfwWindowHint(GLFW_RESIZABLE, true);

        m_window = glfwCreateWindow(properties.WIDTH, properties.HEIGHT, properties.TITLE, NULL, NULL);
        glfwMakeContextCurrent(m_window);
        
        PHSX2D_HARD_ASSERT( gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize glad%s", "\n");

        glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
                glfwSetWindowSize(window, width, height);
                glViewport(0, 0, width, height);
                properties.WIDTH = width;
                properties.HEIGHT = height;
            }
        );

        glfwSwapInterval(0);        
    }

    void Window::OnInit() {
        glfwGetWindowSize(m_window, &properties.WIDTH, &properties.HEIGHT);
        glViewport(0, 0, properties.WIDTH, properties.HEIGHT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        SetVsync(true);
    }

    Window::~Window() {
        glfwDestroyWindow(m_window);
    }
}
