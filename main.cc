#include <stdio.h>

#include <exception>
#include <string>
#include <vector>

#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>

class State {
  private:
    unsigned int vbo;
    unsigned int abo;
    std::vector<float> aboData;

    unsigned int program;

  public:
    void setup() {
        /* Vertex buffer object */
        glGenVertexArrays(1, &vbo);
        glBindVertexArray(vbo);

        /* Array buffer setup */
        aboData.reserve(6);
        aboData.push_back(-0.5f);
        aboData.push_back(-0.5f);
        aboData.push_back(0.5f);
        aboData.push_back(-0.5f);
        aboData.push_back(0.0f);
        aboData.push_back(0.5f);

        glGenBuffers(1, &abo);
        glBindBuffer(GL_ARRAY_BUFFER, abo);
        glBufferData(GL_ARRAY_BUFFER, aboData.size() * sizeof(float),
                     aboData.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2,
                              reinterpret_cast<const void *>(0));

        /* Shader setup */
        unsigned int vertexShader = createShader(
            GL_VERTEX_SHADER, "#version 330 core\n"
                              "\n"
                              "layout(location = 0) in vec4 position;\n"
                              "\n"
                              "void main() {\n"
                              "    gl_Position = position;\n"
                              "}\n");
        unsigned int fragmentShader = createShader(
            GL_FRAGMENT_SHADER, "#version 330 core\n"
                                "\n"
                                "layout(location = 0) out vec4 color;\n"
                                "\n"
                                "void main() {\n"
                                "    color = vec4(0.0, 0.0, 1.0, 1.0);\n"
                                "}\n");
        program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);
        glValidateProgram(program);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glUseProgram(program);
    }

    void render() {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void cleanUp() { glDeleteProgram(program); }

  private:
    unsigned int createShader(unsigned int type, std::string code) {
        unsigned int id = glCreateShader(type);
        const char *src = code.c_str();
        glShaderSource(id, 1, &src, NULL);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char *message = (char *)alloca(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);
            glDeleteShader(id);
            throw std::runtime_error{"Failed to compile shader." +
                                     std::string{message}};
        }

        return id;
    }
};

int main(int argc, char *argv[]) {
    if (!glfwInit()) {
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window =
        glfwCreateWindow(1280, 720, "OpenGL Sandbox", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    State state;
    state.setup();

    while (!glfwWindowShouldClose(window)) {
        state.render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    state.cleanUp();
    glfwTerminate();

    return 0;
}
