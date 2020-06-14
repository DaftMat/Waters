//
// Created by mathis on 03/06/2020.
//
#pragma once

#include <Minimal-Engine/Renderers/FrameBuffers/FBO/FBO.hpp>
#include <memory>

class MultiSamplePass {
   public:
    MultiSamplePass(int width, int height, int numSample);
    ~MultiSamplePass();

    void prepare() const;

    void unbind(int width, int height) const;

    [[nodiscard]] FBO &resultFBO() { return *m_txFBO; }

   private:
    std::unique_ptr<FBO> m_msFBO{nullptr}, m_txFBO{nullptr};
};
