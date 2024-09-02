#pragma once

/*
 * Handles the window creation, update, resize, etc and also has some
 * getter functions for window
*/

#include <glad/glad.h>
#include "../utils/defaults.h"
#include <GLFW/glfw3.h>

namespace Physx2D {

class PHYSX2D_API Window {
public:
  GLFWwindow *m_window;
  static WindowProps properties;
  uint32_t VERSION_MAJOR, VERSION_MINOR;

  Window(WindowProps props = WindowProps(), uint32_t gl_version_major = 4,
         uint32_t gl_version_minor = 6);
  ~Window();
  void OnInit();

  inline void SetVsync(bool value) { glfwSwapInterval(value); }

  inline bool ShouldClose() { return glfwWindowShouldClose(m_window); }

  inline void SetClose(bool value) {
    glfwSetWindowShouldClose(m_window, value);
  }

  inline ivec2 GetResolution() const {
    return ivec2(properties.WIDTH, properties.HEIGHT);
  }

  inline int GetWidth() const { return properties.WIDTH; }

  inline int GetHeight() const { return properties.HEIGHT; }

  inline void FillScreen(Color color = Color(0.0f, 0.0f, 0.0f, 1.0f)) {
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT);
  }

  inline void SetTitle(const char *title) {
    glfwSetWindowTitle(m_window, properties.TITLE = title);
  }

  inline void OnUpdate() {
    glfwPollEvents();
    glfwSwapBuffers(m_window);
  }
};
} // namespace Physx2D
