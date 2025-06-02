#include "../include/renderer.hpp"

Renderer::Renderer(std::pair<int, int> viewport, bool colourSupport, bool ansiSupport) : frame(0), vw(viewport.first), vh(viewport.second - 1), colourSupport(colourSupport), ansiSupport(ansiSupport), outputBuffer() {clearScreen();}
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

void Renderer::clearScreen() {
    clear();
    for (int i = 0; i < vw * vh; i++) {
        outputBuffer << " ";
    }
    render();
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