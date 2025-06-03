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

    grid.setCellType(Coord{4, 5}, cellType::Goal);
    grid.setCellType(Coord{5, 5}, cellType::Path);
    grid.setCellType(Coord{5, 6}, cellType::Start);
    grid.setCellType(Coord{6, 5}, cellType::Wall);
    grid.setCellType(Coord{7, 7}, cellType::Visited);

    // while (true) {
    //     renderer.clear();

    //     std::cout << "\nWindows size: (" << renderer.getWidth() << ", " << renderer.getHeight() << ")" << Ansi::DefaultFG;
    //     std::cout << "\nColour Support: " << (renderer.getColourSupport() ? Ansi::Green : Ansi::Red) << (renderer.getColourSupport() ? "True" : "False") << Ansi::DefaultFG;
    //     std::cout << "\nANSI Support: " << (renderer.getAnsiSupport() ? Ansi::Green : Ansi::Red) << (renderer.getAnsiSupport() ? "True" : "False") << Ansi::DefaultFG;
        
    //     renderer.render();

    //     std::this_thread::sleep_for(std::chrono::milliseconds(100));
    // }

    while (true) {
        renderer.clear();
        renderer.appendGrid(grid);
        renderer.render();
    }

}