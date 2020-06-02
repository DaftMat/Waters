//
// Created by mathis on 18/05/2020.
//
#pragma once

#include "ShaderProgram.hpp"

class QuadShader : public ShaderProgram
{
  public:
    QuadShader( const char* vertexPath, const char* fragmentPath ) :
        ShaderProgram( vertexPath, fragmentPath ) {}

    void setTexture();
};
