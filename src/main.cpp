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
        Utils::getCharsetSupport()
    );

    GameBoard board(Utils::getTerminalSize());

    while (true) {
        renderer.clear();

        renderer.testCheckerBoard();
        renderer.render();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

}