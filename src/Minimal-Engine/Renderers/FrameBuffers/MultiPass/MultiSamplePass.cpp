//
// Created by mathis on 03/06/2020.
//
#include "MultiSamplePass.hpp"

MultiSamplePass::MultiSamplePass( int width, int height, int numSample ) {
    m_msFBO = std::make_unique<FBO>(
        width,
        height,
        numSample,
        FBO::Attachments{ FBO::Attachments::BUFFER, 1, FBO::Attachments::BUFFER } );
    m_txFBO = std::make_unique<FBO>(
        width,
        height,
        1,
        FBO::Attachments{ FBO::Attachments::TEXTURE, 1, FBO::Attachments::TEXTURE } );
}

MultiSamplePass::~MultiSamplePass() {
    m_msFBO.reset();
    m_txFBO.reset();
}

void MultiSamplePass::prepare() const {
    m_msFBO->prepare();
}

void MultiSamplePass::unbind( int width, int height ) const {
    m_msFBO->unbind( width, height );
    m_msFBO->resolve( *m_txFBO );
}
