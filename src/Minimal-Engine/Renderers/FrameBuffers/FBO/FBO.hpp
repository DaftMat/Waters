//
// Created by mathis on 18/05/2020.
//
#pragma once

#include <Minimal-Engine/Renderers/FrameBuffers/FrameBuffer.hpp>

class FBO : public FrameBuffer
{
  public:
    struct Attachments {
        enum Type {
            TEXTURE,
            BUFFER,
            NONE ///< if no buffer of that attachment wanted
        };

        explicit Attachments( Type pcolor         = TEXTURE,
                     int num_color       = 1,
                     Type pdepth         = BUFFER,
                     Type pstencil       = NONE,
                     Type pstencil_depth = NONE ) :
            color{ pcolor },
            numColor{ num_color },
            depth{ pdepth },
            stencil{ pstencil },
            stencil_depth{ pstencil_depth } {}

        Type color;
        int numColor;
        Type depth;
        Type stencil;
        Type stencil_depth;
    };

    FBO(int width, int height, int numSamples, Attachments attach ) :
        FrameBuffer( width, height, numSamples ) {
        initialize( attach );
    }

  protected:
    void initialize( Attachments attach );
};
