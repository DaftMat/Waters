//
// Created by mathis on 24/05/2020.
//
#pragma once


#include <GLFW/glfw3.h>
#include <functional>

class GLFWWindow {
public:
    GLFWWindow(int width, int height);
    ~GLFWWindow() { terminate(); }

    bool shouldClose() { return glfwWindowShouldClose(m_window); }

    bool isPressed(int key) { return glfwGetKey(m_window, key) == GLFW_PRESS; }

    void finish();

    static void setFramebufferCallback(std::function<void(int,int)> framebufferCallback)
    { m_framebufferCallback = std::move(framebufferCallback); }

    static void setMouseMoveCallback(std::function<void(float,float)> mouseMoveCallback)
    { m_mouseMoveCallback = std::move(mouseMoveCallback); }

    static void setMousePressCallback(std::function<void(float,float)> mousePressCallback)
    { m_mousePressCallback = std::move(mousePressCallback); }

    static void setMouseReleaseCallback(std::function<void()> mouseReleaseCallback)
    { m_mouseReleaseCallback = std::move(mouseReleaseCallback); }

    static void setMouseScrollCallback(std::function<void(float)> mouseScrollCallback)
    { m_mouseScrollCallback = std::move(mouseScrollCallback); }

private:
    void terminate();

    GLFWwindow *m_window;

    static float m_mouseX, m_mouseY;

    static std::function<void(int,int)> m_framebufferCallback;
    static std::function<void(float,float)> m_mouseMoveCallback;
    static std::function<void(float,float)> m_mousePressCallback;
    static std::function<void()> m_mouseReleaseCallback;
    static std::function<void(float)> m_mouseScrollCallback;

    static void framebuffer_size_callback(GLFWwindow *window, int pwidth, int pheight) { m_framebufferCallback(pwidth, pheight); }
    static void cursor_position_callback( GLFWwindow* window, double xpos, double ypos ) { m_mouseX = xpos; m_mouseY = ypos; m_mouseMoveCallback(xpos, ypos); }
    static void mouse_button_callback( GLFWwindow* window, int button, int action, int mods );
    static void scroll_callback( GLFWwindow* window, double xoffset, double yoffset ) { m_mouseScrollCallback(yoffset); }
};