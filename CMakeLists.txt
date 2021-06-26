# Basic setup
cmake_minimum_required(VERSION 3.10)

project(OpenGLSandbox VERSION 0.1)

# Global options
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_definitions(GL_SILENCE_DEPRECATION)

# Libraries setup
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_subdirectory(3ps/glfw)
include_directories(3ps/glfw/include)

# Main executable setup
add_executable(main
    main.cc
)

target_link_libraries(main
    glfw
    ${GLFW_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARIES}
)
