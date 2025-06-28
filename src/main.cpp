#include "../include/types.hpp"
#include "../include/renderer.hpp"
#include "../include/gameboard.hpp"
#include "../include/utils.hpp"
#include "../include/errors.hpp"
#include "../include/solver.hpp"

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
    Solver solver(grid);
    UIState state = UIState::LOADING;

    const float LOADFRAME = 50;
    const int MSPERFRAME = 40; // 25 FPS


    /* --- PHASE 1: Loading Fakery --- */
    for (int frame = 0; frame < LOADFRAME; frame++) {
        renderer.clear();
        renderer.appendEmpty();
        renderer.appendTextCenter("Pathfinders", {Ansi::Bold});
        renderer.appendTextCenter("A Demonstration by Arham Aneeq");
        renderer.appendEmpty();
        renderer.appendTextCenter("github.com/arhamaneeq", {Ansi::Cyan});
        renderer.appendLine();
        renderer.appendProgressBar(frame / LOADFRAME);
        renderer.appendLine();

        if (frame >= 0.25 * LOADFRAME) {
            renderer.appendTextCenter("Instructions can be found at");
            renderer.appendTextCenter("readme.md", {Ansi::Yellow});
            renderer.appendEmpty();
            renderer.appendText("Press ", {}, false);
            renderer.appendText("ctrl + C ", {Ansi::Red}, false);
            renderer.appendText("to force stop if loop is stuck.");
        }

        if (frame >= 0.5 * LOADFRAME) {
            renderer.appendText("renderer::getColourSupport(): ", {}, false);
            [&](bool v){renderer.appendText(v ? "True" : "False", {v ? Ansi::Green : Ansi::Red});}(renderer.getColourSupport());
        }
        if (frame >= 0.55 * LOADFRAME) {
            renderer.appendText("renderer::getAnsiSupport():   ", {}, false);
            [&](bool v){renderer.appendText(v ? "True" : "False", {v ? Ansi::Green : Ansi::Red});}(renderer.getAnsiSupport());
        }

        renderer.render();

        Utils::wait(MSPERFRAME);
        state = UIState::SETUP;
    }

    while (state == UIState::SETUP) {
        /* --- PHASE 2: Input Section --- */
        while (state == UIState::SETUP) {
            renderer.clear();
            renderer.appendGrid(grid);
            renderer.appendInput(" >>> ", {Ansi::Yellow});
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
            } else if (cmd == "ALGO") {
                std::string alg;
                if (iss >> alg) {
                    if (alg == "BFS") {solver.setAlgo(Algorithm::BFS);}
                    else if (alg == "DFS") {solver.setAlgo(Algorithm::DFS);}
                    else if (alg == "Djikstra") {solver.setAlgo(Algorithm::Djikstra);}
                    else if (alg == "AStar") {solver.setAlgo(Algorithm::AStar);}
                    else {renderer.appendTooltip("Invalid Algo", "Enter a supported algorithm", {Ansi::Sunny});};
                }
            } else if (cmd == "RUN") {
                int SetupResult = solver.setup();
                if (SetupResult == 0) {
                    state = UIState::SOLVING;
                    renderer.appendTooltip("Starting", "Successfully running.", {Ansi::Green}, 10);
                    break;
                } else if (SetupResult == 1) {
                    renderer.appendTooltip("Key Points not Set", "Start or End point missing.", {Ansi::Red});
                } else if (SetupResult == 2) {
                    renderer.appendTooltip("Algo not Set", "Set a valid algorithm to RUN.", {Ansi::Red});
                }
            } else {
                renderer.appendTooltip("Invalid Command", "Enter a supported command.", {Ansi::Sunny});
            }
        }
    
        /* --- PHASE 3: Pathfinding --- */
        while (state == UIState::SOLVING) {
            renderer.clear();
            renderer.appendGrid(grid);
            renderer.render();

            solver.step();
            if (solver.isStopped()) {state = UIState::SOLVED;}
            Utils::wait(MSPERFRAME);
        }

        while (state == UIState::SOLVED) {
            renderer.clear();
            renderer.appendGrid(grid);
            renderer.appendInput(" >>> ", {Ansi::Yellow});
            renderer.render();

            std::string input, cmd;
            std::getline(std::cin, input);
            std::istringstream iss(input);

            iss >> cmd;

            if (cmd == "END") {return 0;}
            if (cmd == "RESET") {solver.reset(); state = UIState::SETUP;}  // TODO: define how reset works // FIXME:

            renderer.appendTooltip("Invalid Command", "Valid commands are END or RESET", {Ansi::Terracotta});
        }
    }

    if (state == UIState::END) {
        return 0;
    }
}