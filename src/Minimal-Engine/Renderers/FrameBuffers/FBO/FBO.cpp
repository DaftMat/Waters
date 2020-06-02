//
// Created by mathis on 18/05/2020.
//

#include "FBO.hpp"

void FBO::initialize(FBO::Attachments attach ) {
    for ( int i = 0; i < attach.numColor; ++i )
    {
        if ( attach.color == Attachments::TEXTURE ) { addColorTexture(); }
        else if ( attach.color == Attachments::BUFFER )
        { addColorBuffer(); }
    }
    if ( attach.depth == Attachments::TEXTURE ) { addDepthTexture(); }
    else if ( attach.depth == Attachments::BUFFER )
    { addDepthBuffer(); }
    if ( attach.stencil == Attachments::TEXTURE ) { addStencilTexture(); }
    else if ( attach.stencil == Attachments::BUFFER )
    { addStencilBuffer(); }
    if ( attach.stencil_depth == Attachments::TEXTURE ) { addDepthStencilTexture(); }
    else if ( attach.stencil_depth == Attachments::BUFFER )
    { addDepthStencilBuffer(); }
    drawBuffers();
}
