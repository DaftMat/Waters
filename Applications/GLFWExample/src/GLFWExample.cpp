//
// Created by mathis on 24/05/2020.
//
#include <Core/Log.hpp>
#include <Minimal-Engine/Geometry/Primitives.hpp>
#include <Minimal-Engine/Material/PerlinNoise/Noise.hpp>
#include "GLFWExample.hpp"
#include "GLFWWindow.hpp"

GLFWExample::GLFWExample() {
    init(1600, 900);

    auto &renderer = *m_renderer;
    GLFWWindow::setFramebufferCallback([&renderer](int width, int height){ renderer.resize(width, height); });
    auto &camera = m_camera;
    GLFWWindow::setMouseMoveCallback([&camera](float xpos, float ypos){ camera.processMouseMove(glm::vec2{xpos, ypos});});
    GLFWWindow::setMousePressCallback([&camera](float xpos, float ypos){camera.processMousePress(glm::vec2{xpos, ypos});});
    GLFWWindow::setMouseReleaseCallback([&camera](){camera.processMouseRelease();});
    GLFWWindow::setMouseScrollCallback([&camera](float offset){camera.processMouseScroll(offset);});

    loadExampleScene();
    APP_INFO("Application created.");
}

void GLFWExample::moveCamera(float dt) {
    if (m_window->isPressed(GLFW_KEY_W))
        m_camera.processMovement(Camera::Movement::FRONT, dt);
    if (m_window->isPressed(GLFW_KEY_S))
        m_camera.processMovement(Camera::Movement::BACK, dt);
    if (m_window->isPressed(GLFW_KEY_A))
        m_camera.processMovement(Camera::Movement::LEFT, dt);
    if (m_window->isPressed(GLFW_KEY_D))
        m_camera.processMovement(Camera::Movement::RIGHT, dt);
    if (m_window->isPressed(GLFW_KEY_SPACE))
        m_camera.processMovement(Camera::Movement::UP, dt);
    if (m_window->isPressed(GLFW_KEY_X))
        m_camera.processMovement(Camera::Movement::DOWN, dt);
}

void GLFWExample::loadExampleScene() {
    APP_INFO("Loading example scene...");
    //std::vector<Mesh::Vertex> vertices;
    //std::vector<GLuint> indices{ 0, 2, 3, 0, 1, 2 };
    //Mesh::Vertex vertex{};
    //vertex.texCoords = { 0.f, 0.f };
    //vertex.normal    = { 1.f, 1.f, 1.f };
    //vertex.position  = { -0.5f, -0.5f, 0.5f };
    //vertices.push_back( vertex );
    //vertex.texCoords = { 1.f, 0.f };
    //vertex.normal    = { 1.f, 0.f, 0.f };
    //vertex.position  = { 0.5f, -0.5f, 0.f };
    //vertices.push_back( vertex );
    //vertex.texCoords = { 1.f, 1.f };
    //vertex.normal    = { 0.f, 1.f, 0.f };
    //vertex.position  = { 0.5f, 0.5f, 0.f };
    //vertices.push_back( vertex );
    //vertex.texCoords = { 0.f, 1.f };
    //vertex.normal    = { 0.f, 0.f, 1.f };
    //vertex.position  = { -0.5f, 0.5f, 0.f };
    //vertices.push_back( vertex );
    m_renderer->addTerrain(Terrain(HeightMap(Noise::generate(128, 12, 0.5f, 2.f, 0.f, Perlin(512)), [](float h){
        return (h - 0.5f) * 2.f;
    })));
    m_lights.addLight(DirectLight({-0.1f, -1.f, 0.f}));
    //m_renderer->addMesh(vertices, indices);
    APP_INFO("Example scene loaded");
}

void GLFWExample::draw(double deltatime) {
    m_renderer->prepare();
    m_renderer->render(m_lights, m_camera);
}

void GLFWExample::run() {
    APP_INFO("launching application...");
    m_lastTime = glfwGetTime();
    while (!m_window->shouldClose()) {
        auto currenttime = float(glfwGetTime());
        auto deltaTime = currenttime - m_lastTime;
        m_lastTime = currenttime;
        moveCamera(0.016);
        draw(deltaTime);
        m_window->finish();
    }
    APP_INFO("application got out of main loop");
}
