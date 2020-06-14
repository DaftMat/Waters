//
// Created by mathis on 17/05/2020.
//
#pragma once

#include <Core/OpenGL.hpp>
#include <vector>

class FrameBuffer {
   public:
    FrameBuffer(int width, int height, int numSamples);
    ~FrameBuffer();

    void prepare() const;

    /** Unbind the framebuffer object and reset to the screen's fbo.
     *
     * @param width - screen width.
     * @param height - screen height.
     */
    void unbind(int width, int height) const;

    [[nodiscard]] const std::vector<GLuint> &textures() const { return m_textures; }

    [[nodiscard]] const std::vector<GLuint> &buffers() const { return m_buffers; }

    /** Resolves one fbo's color buffer to the screen's fbo.
     *
     * @param width - screen width.
     * @param height - screen height.
     * @param index - index of the color buffer to resolve.
     */
    void resolve(int width, int height, int index = 0) const;

    /** Resolves one fbo's color buffer to another fbo.
     *
     * @param frameBuffer - other fbo.
     * @param index - index of the color buffer to resolve.
     */
    void resolve(FrameBuffer &frameBuffer, int index = 0) const;

   protected:
    void addColorBuffer();
    void addDepthBuffer();
    void addStencilBuffer();
    void addDepthStencilBuffer();
    void addColorTexture();
    void addDepthTexture();
    void addStencilTexture();
    void addDepthStencilTexture();

    void drawBuffers();

   private:
    int m_width, m_height;
    GLuint m_fbo;
    std::vector<GLuint> m_textures;
    std::vector<GLuint> m_buffers;

    int m_numSamples;

    bool m_stencil{false}, m_depth{false}, m_stencil_depth{false};
    int m_num_color{0};
};
