//
// Created by mathis on 24/05/2020.
//
#include "GLFWExample.hpp"

#include <Core/Log.hpp>
#include <Core/Random.hpp>
#include <Minimal-Engine/Geometry/Primitives.hpp>
#include <Minimal-Engine/Material/PerlinNoise/Noise.hpp>

#include "GLFWWindow.hpp"

GLFWExample::GLFWExample() {
    init(1600, 900);

    auto& renderer = *m_renderer;
    GLFWWindow::setFramebufferCallback([&renderer](int width, int height) { renderer.resize(width, height); });
    auto& camera = m_camera;
    GLFWWindow::setMouseMoveCallback([&camera](float xpos, float ypos) {
        camera.processMouseMove(glm::vec2{xpos, ypos});
    });
    GLFWWindow::setMousePressCallback([&camera](float xpos, float ypos) {
        camera.processMousePress(glm::vec2{xpos, ypos});
    });
    GLFWWindow::setMouseReleaseCallback([&camera]() { camera.processMouseRelease(); });
    GLFWWindow::setMouseScrollCallback([&camera](float offset) { camera.processMouseScroll(offset); });

    loadExampleScene();
    APP_INFO("Application created.");
}

void GLFWExample::movePlayer(float dt) {
    if (m_window->isPressed(GLFW_KEY_W)) {
        m_renderer->player().processMovement(Player::Movement::FRONT, dt);
        m_camera.updateYaw(dt);
    }
    if (m_window->isPressed(GLFW_KEY_S)) m_renderer->player().processMovement(Player::Movement::BACK, dt);
    if (m_window->isPressed(GLFW_KEY_A)) m_renderer->player().processMovement(Player::Movement::LEFT, dt);
    if (m_window->isPressed(GLFW_KEY_D)) m_renderer->player().processMovement(Player::Movement::RIGHT, dt);
    if (m_window->isPressed(GLFW_KEY_SPACE)) m_renderer->player().jump();
    glm::vec2 pos{m_renderer->player().getPosition().x, m_renderer->player().getPosition().z};
    float h = m_renderer->terrains().getHeight(pos.x, pos.y);
    m_renderer->player().update(dt, h);
    m_camera.update(m_renderer->player().getPosition() + glm::vec3{0.f, 2.5f, 0.f},
                    m_renderer->player().getRotation().y);
}

void GLFWExample::loadExampleScene() {
    APP_INFO("Loading example scene...");
    m_renderer->initPlayer(Player(Mesh("resources/objects/person.obj")));
    m_renderer->player().addAlbedoTexture("resources/textures/playerTexture.png");
    m_renderer->player().setScale(glm::vec3{0.2f});

    m_renderer->terrains().fun() = [](float h) { return (5.f * ((h - 0.5f) * 2.f)); };

    float size = 20.f;
    int dim = 7;
    int indexTree = 0;
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            glm::ivec2 gridPos{i - int(glm::floor(float(dim) / 2.f)), j - int(glm::floor(float(dim) / 2.f))};
            m_renderer->addTerrain(gridPos.x, gridPos.y);
            glm::vec2 pos{gridPos.x * 2.f * size, gridPos.y * 2.f * size};
            int index = i * dim + j;
            m_renderer->addWater(Water(0.03f, 4, size));
            m_renderer->water(index).position() = glm::vec3{pos.x, 0.f, pos.y};

            for (int k = 0; k < wtr::Core::Random::get(0, 10); ++k) {
                glm::vec2 coords = {wtr::Core::Random::get(pos.x - size, pos.x + size),
                                    wtr::Core::Random::get(pos.y - size, pos.y + size)};
                auto h = m_renderer->terrains().getHeight(coords.x, coords.y);
                if (h > 0.f) {
                    m_renderer->addObject(Object(Mesh("resources/objects/tree.obj")));
                    m_renderer->object(indexTree).setPosition(glm::vec3{coords.x, h - 0.25f, coords.y});
                    m_renderer->object(indexTree).setScale(glm::vec3{wtr::Core::Random::get(1.5f, 2.f)});
                    m_renderer->object(indexTree).addAlbedoTexture("resources/textures/tree.png");
                    indexTree++;
                }
            }
        }
    }

    m_quadRenderer->addQuad(Quad(-1.f, 1.f, 2.f, 2.f));  // screen

    m_quadRenderer->quad(0).setTexture(m_renderer->screenFBO().textures()[0]);
    APP_INFO("Example scene loaded");
}

void GLFWExample::draw(double deltatime) {
    m_renderer->update(float(deltatime));
    m_renderer->prepare();
    m_renderer->render(m_lights, m_camera, deltatime);

    m_quadRenderer->prepare();
    m_quadRenderer->render();
}

void GLFWExample::run() {
    APP_INFO("launching application...");
    m_lastTime = glfwGetTime();
    while (!m_window->shouldClose()) {
        auto currenttime = float(glfwGetTime());
        auto deltaTime = currenttime - m_lastTime;
        m_lastTime = currenttime;
        movePlayer(deltaTime);
        draw(deltaTime);
        m_window->finish();
    }
    APP_INFO("application got out of main loop");
}