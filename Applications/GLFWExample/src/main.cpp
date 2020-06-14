
#include <Core/Log.hpp>
#include "GLFWExample.hpp"

int main() {
    wtr::Core::Log::init();

    GLFWExample app;
    app.run();
    return 0;
}