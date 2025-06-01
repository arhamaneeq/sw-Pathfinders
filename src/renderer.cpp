#include "../include/renderer.hpp"

Renderer::Renderer(std::pair<int, int> viewport, bool colourSupport, bool ansiSupport) : frame(0), vw(viewport.first), vh(viewport.second - 1), colourSupport(colourSupport), ansiSupport(ansiSupport), outputBuffer() {
    std::cout << "Renderer initialised with:";
    std::cout << "\n           vw: " << vw;
    std::cout << "\n           vh: " << vh;
    std::cout << "\n  AnsiCharset: " << ansiSupport;
    std::cout << "\n   AnsiColour: " << colourSupport;
}
Renderer::~Renderer() = default;


void Renderer::clear() {
    outputBuffer.str("");
    outputBuffer.clear();
    outputBuffer << Ansi::CursorHome;
}

void Renderer::render() {
    outputBuffer << Ansi::DefaultFG;
    std::cout << outputBuffer.str() << std::flush;
    frame++;

    outputBuffer.str("");
    outputBuffer.clear();
}

int Renderer::getWidth() {
    return vw;
}

int Renderer::getHeight() {
    return vh;
}

int Renderer::getAnsiSupport() {
    return ansiSupport;
}

int Renderer::getColourSupport() {
    return colourSupport;
}

void Renderer::testCheckerBoard() {
    for (int y = 0; y < vh; y++) {
        for (int x = 0; x < vw; x++) {
            outputBuffer << ((frame % 2 == 0) ? Ansi::Cyan : Ansi::Red);
            outputBuffer << (((x + y + frame) % 2 == 0) ? '#' : ' ');
        }

        outputBuffer << "\n";
    }
}