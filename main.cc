#include <stdio.h>

#include <GLFW/glfw3.h>
#include <OpenGL/gl.h>

int main(int argc, char *argv[]) {
  if (!glfwInit()) {
    return 1;
  }

  GLFWwindow *window =
      glfwCreateWindow(1280, 720, "OpenGL Sandbox", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return 1;
  }

  glfwMakeContextCurrent(window);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
