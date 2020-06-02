//
// Created by mathis on 24/05/2020.
//
#include <Core/Log.hpp>
#include "GLFWWindow.hpp"

GLFWWindow::GLFWWindow(int width, int height) {
    APP_INFO("Creating window...");
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width,height, "Engine Example Works !", nullptr, nullptr);
    if (m_window == nullptr) {
        APP_ERROR("Failed to create GLFW window.");
        glfwTerminate();
    }
    glfwMakeContextCurrent(m_window);

    glfwSetFramebufferSizeCallback( m_window, framebuffer_size_callback );
    glfwSetCursorPosCallback(m_window, cursor_position_callback);
    glfwSetMouseButtonCallback(m_window, mouse_button_callback);
    glfwSetScrollCallback(m_window, scroll_callback);
    APP_INFO("Window created.");
}

void GLFWWindow::finish() {
    glfwPollEvents();
    glfwSwapBuffers(m_window);
}


void GLFWWindow::terminate() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
    APP_INFO("Window closed. Leaving now.");
}

void GLFWWindow::mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if (button != GLFW_MOUSE_BUTTON_LEFT) return;
    switch(action) {
        case GLFW_PRESS:
            m_mousePressCallback(m_mouseX, m_mouseY);
            break;
        case GLFW_RELEASE:
            m_mouseReleaseCallback();
            break;
        default:break;
    }
}

std::function<void(int,int)> GLFWWindow::m_framebufferCallback {[](int,int){}};
std::function<void(float,float)> GLFWWindow::m_mouseMoveCallback {[](float,float){}};
std::function<void(float,float)> GLFWWindow::m_mousePressCallback {[](float,float){}};
std::function<void()> GLFWWindow::m_mouseReleaseCallback {[](){}};
std::function<void(float)> GLFWWindow::m_mouseScrollCallback {[](float){}};
float GLFWWindow::m_mouseX{0};
float GLFWWindow::m_mouseY{0};

