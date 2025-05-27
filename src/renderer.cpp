#include "../include/renderer.hpp"
Renderer::Renderer(dims viewport, bool colourSupport, bool ansiSupport) : frame(0), viewport(viewport), colourSupport(colourSupport), ansiSupport(ansiSupport), outputBuffer() {}
Renderer::~Renderer() = default;


void Renderer::clear() {
    outputBuffer << Ansi::CursorHome << Ansi::ClearScreen;
}

void Renderer::render() {
    std::cout << outputBuffer.str();
    std::cout << std::flush;
    frame++;
}