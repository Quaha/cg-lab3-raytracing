#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "SceneManager.hpp"

class Window {
private:
    unsigned int width, height;
    std::string title;

    GLFWwindow* window = nullptr;

    void open();
    void close();

    void pollEvents() const;
    void swapBuffers() const;

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

public:

    Window(unsigned int width, unsigned int height, const std::string& title);
    ~Window();

    void renderScene(SceneManager& scene);
};
