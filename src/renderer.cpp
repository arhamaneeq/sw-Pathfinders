#include "../include/renderer.hpp"

Renderer::Renderer(std::pair<int, int> viewport, bool colourSupport, bool ansiSupport) : frame(0), vw(viewport.first), vh(viewport.second), colourSupport(colourSupport), ansiSupport(ansiSupport), outputBuffer() {}
Renderer::~Renderer() = default;


void Renderer::clear() {
    outputBuffer << Ansi::CursorHome << Ansi::ClearScreen;
}

void Renderer::render() {
    std::cout << outputBuffer.str();
    std::cout << std::flush;
    frame++;
}