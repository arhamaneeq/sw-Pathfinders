#include "../include/types.hpp"
#include "../include/renderer.hpp"
#include "../include/gameboard.hpp"
#include "../include/utils.hpp"
#include "../include/errors.hpp"

int main() {
    Utils::enableAnsiSupport();

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Renderer renderer(
        Utils::getTerminalSize(),
        Utils::getColourSupport(),
        Utils::getAnsiSupport()
    );

    Grid grid(Utils::getTerminalSize());

    /* --- PHASE 1: Loading Fakery --- */
    for (int frame = 0; frame < 100; frame++) {
        renderer.clear();
        renderer.appendEmpty();
        renderer.appendTextCenter("Pathfinders", {Ansi::Bold});
        renderer.appendTextCenter("A Demonstration by Arham Aneeq");
        renderer.appendEmpty();
        renderer.appendTextCenter("github.com/arhamaneeq", {Ansi::Cyan});
        renderer.appendLine();
        renderer.appendProgressBar(frame / 100.0f);
        renderer.appendLine();

        if (frame >= 25) {
            renderer.appendTextCenter("Instructions can be found at");
            renderer.appendTextCenter("readme.md", {Ansi::Yellow});
            renderer.appendEmpty();
            renderer.appendText("Press ", {}, false);
            renderer.appendText("ctrl + C ", {Ansi::Red}, false);
            renderer.appendText("to force stop if loop is stuck.");
        }

        if (frame >= 50) {
            renderer.appendText("renderer::getColourSupport(): ", {}, false);
            [&](bool v){renderer.appendText(v ? "True" : "False", {v ? Ansi::Green : Ansi::Red});}(renderer.getColourSupport());
        }
        if (frame >= 55) {
            renderer.appendText("renderer::getAnsiSupport():   ", {}, false);
            [&](bool v){renderer.appendText(v ? "True" : "False", {v ? Ansi::Green : Ansi::Red});}(renderer.getAnsiSupport());
        }

        renderer.render();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    while (true) {
        /* --- PHASE 2: Input Section --- */
        while (true) {
            renderer.clear();
            renderer.appendGrid(grid);
            renderer.appendInput(" >>>", {Ansi::Yellow});
            renderer.render();
    
            std::string input, cmd;
            std::getline(std::cin, input);
            std::istringstream iss(input);

            iss >> cmd;
            if (cmd == "PWA") {
                int x, y;
                if (iss >> x >> y) {
                    grid.config.createWallAt(Coord{x, y});
                }
            } else if (cmd == "END") {
                return 0;
            } else if (cmd == "PHL") {
                int x, y, L;
                if (iss >> x >> y >> L) {
                    grid.config.createWallHorizontal(Coord{x, y}, L);
                }
            } else if (cmd == "PVL") {
                int x, y, L;
                if (iss >> x >> y >> L) {
                    grid.config.createWallVertical(Coord{x, y}, L);
                }
            } else if (cmd == "PSA") {
                int x, y;
                if (iss >> x >> y) {
                    grid.config.createTypeAt(Coord{x, y}, cellType::Start);
                }
            } else if (cmd == "PEA") {
                int x, y;
                if (iss >> x >> y) {
                    grid.config.createTypeAt(Coord{x, y}, cellType::Goal);
                }
            } else if (cmd == "RUN") {
                break;
            }

        }
    
        /* --- PHASE 3: Pathfinding --- */
        while (true) {
            renderer.clear();
            renderer.appendGrid(grid);
            renderer.render();
        }
    }
}