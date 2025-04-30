// Window.cpp
#include "Window.hpp"

#include <stdexcept>
#include <iostream>

Window::Window(unsigned int width, unsigned int height, const std::string& title) {
    this->width = width;
    this->height = height;
    this->title = title;
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::open() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    // Initializing OpenGL context version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback); // key pressing processing
    glfwSwapInterval(1); // vsync

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    std::cout << "OpenGL initialized: " << glGetString(GL_VERSION) << std::endl;
}

void Window::close() {
    glfwSetWindowShouldClose(window, true);
}

void Window::pollEvents() const {
    glfwPollEvents();
}

void Window::swapBuffers() const {
    glfwSwapBuffers(window);
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void Window::renderScene(SceneManager& scene) {
    try {
        open();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return;
    }

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        swapBuffers();
        pollEvents();
    }

    close();
}
