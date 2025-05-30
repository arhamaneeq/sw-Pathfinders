#include "../include/renderer.hpp"

Renderer::Renderer(std::pair<int, int> viewport, bool colourSupport, bool ansiSupport) : frame(0), vw(viewport.first), vh(viewport.second), colourSupport(colourSupport), ansiSupport(ansiSupport), outputBuffer() {}
Renderer::~Renderer() = default;


void Renderer::clear() {
    outputBuffer.str("");
    outputBuffer.clear();
    outputBuffer << Ansi::ClearScreen << Ansi::CursorHome;

    // FIXME: screen is not cleared
}

void Renderer::render() {
    std::cout << outputBuffer.str() << std::flush;
    frame++;

    outputBuffer.str("");
    outputBuffer.clear();
}

void Renderer::testCheckerBoard() {
    for (int y = 0; y < vh; y++) {
        for (int x = 0; x < vw; x++) {
            outputBuffer << (((x + y + frame) % 2 == 0) ? '#' : ' ');
        }

        outputBuffer << "\n";
    }
}