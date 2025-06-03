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

void Renderer::appendGrid(const Grid& grid) {
    for (int y = 0; y < vh; y++) {
        for (int x = 0; x < vw; x++) {
            switch (grid.getCell(Coord{x, y}).type) {
                case cellType::Empty:
                    outputBuffer << Ansi::Black;
                    break;
                case cellType::Wall:
                    outputBuffer << Ansi::White;
                    break;
                case cellType::Start:
                    outputBuffer << Ansi::Blue;
                    break;
                case cellType::Goal:
                    outputBuffer << Ansi::Magenta;
                    break;
                case cellType::Visited:
                    outputBuffer << Ansi::Yellow;
                    break;
            }

            outputBuffer << "#";
        }

        outputBuffer << "\n";
    }

    outputBuffer << Ansi::DefaultFG;
}