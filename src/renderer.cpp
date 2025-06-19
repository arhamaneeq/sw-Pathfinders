#include "../include/renderer.hpp"

Renderer::Renderer(std::pair<int, int> viewport, bool colourSupport, bool ansiSupport) : frame(0), vw(viewport.first), vh(viewport.second - 1), colourSupport(colourSupport), ansiSupport(ansiSupport), outputBuffer() {clearScreen();}
Renderer::~Renderer() = default;


void Renderer::clear() {
    outputBuffer.str("");
    outputBuffer.clear();
    outputBuffer << Ansi::CursorHome;
}

void Renderer::render() {
    if (frame >= tooltip.startingFrame && frame < tooltip.startingFrame + tooltip.duration) {renderTooltip();};

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
                    outputBuffer << Ansi::Yellow;
                    break;
                case cellType::Goal:
                    outputBuffer << Ansi::Red;
                    break;
                case cellType::Visited:
                    outputBuffer << Ansi::Blue;
                    break;
                case cellType::Frontier:
                    outputBuffer << Ansi::Cyan;
                    break;
                case cellType::Path:
                    outputBuffer << Ansi::Green;
                    break;
            }

            outputBuffer << "#";
        }

        outputBuffer << "\n";
    }

    outputBuffer << Ansi::DefaultFG;
}

void Renderer::appendLine() {
    for (int x = 0; x < vw; x++) {
        outputBuffer << "-";
    }

    outputBuffer << "\n";
}

void Renderer::appendEmpty() {
    outputBuffer << "\n";
}

void Renderer::appendText(String txt, Styles styles, bool newLine) {
    for (auto style : styles) {outputBuffer << String(style);}
    outputBuffer << txt << Ansi::Reset <<  ((newLine) ? "\n" : "");
}

void Renderer::appendTextCenter(String txt, Styles styles) {
    for (int i = 0; i < 0.5*(vw - txt.length()); i++) {outputBuffer << " ";}
    for (auto style : styles) {outputBuffer << String(style);}
    outputBuffer << txt << Ansi::Reset << "\n";
}

void Renderer::appendProgressBar(float percentProgress) {
    for (int i = 0; i < vw*percentProgress; i++) {
        outputBuffer << "#";
    }
    outputBuffer << "\n";
}

void Renderer::appendInput(String txt, Styles styles) {
    for (auto style : styles) {outputBuffer << String(style);}
    outputBuffer << txt << Ansi::Reset << Ansi::CursorSave;
    for (int i = 0; i < vw - txt.length(); i++) {outputBuffer << " ";}
    outputBuffer << Ansi::CursorRestore;
}

void Renderer::appendTooltip(String title, String text, Styles styles, int duration) {
    tooltip.startingFrame = frame;
    tooltip.duration = duration;
    tooltip.title = title;
    tooltip.text = text;
    tooltip.width = 30;
    tooltip.styles = styles;
}

void Renderer::renderTooltip() {
    int titleLen = tooltip.title.length();
    int textLen = tooltip.text.length();

    outputBuffer << Ansi::CursorSave << Ansi::CursorHome;
    outputBuffer << Ansi::CursorDown(2);
    outputBuffer << Ansi::CursorRight(2);

    for (int i = 0; i < tooltip.width; i++) {outputBuffer << "-";}
    outputBuffer << Ansi::CursorLeft(tooltip.width) << Ansi::CursorDown();
    outputBuffer << "| ";
    for (auto style : tooltip.styles) {outputBuffer << String(style);}
    outputBuffer << tooltip.title << Ansi::Reset;
    for (int i = 0; i < tooltip.width - 4 - titleLen; i++) {outputBuffer << " ";}
    outputBuffer << " |";
    outputBuffer << Ansi::CursorLeft(tooltip.width) << Ansi::CursorDown();
    outputBuffer << "| " << tooltip.text;
    for (int i = 0; i < tooltip.width - 4 - textLen; i++) {outputBuffer << " ";}
    outputBuffer << " |";
    outputBuffer << Ansi::CursorLeft(tooltip.width) << Ansi::CursorDown();
    for (int i = 0; i < tooltip.width; i++) {outputBuffer << "-";}
    outputBuffer << Ansi::CursorRestore;
}