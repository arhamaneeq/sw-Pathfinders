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

    while (true) {
        renderer.clear();

        std::cout << "\nWindows size: (" << renderer.getWidth() << ", " << renderer.getHeight() << ")" << Ansi::DefaultFG;
        std::cout << "\nColour Support: " << (renderer.getColourSupport() ? Ansi::Green : Ansi::Red) << (renderer.getColourSupport() ? "True" : "False") << Ansi::DefaultFG;
        std::cout << "\nANSI Support: " << (renderer.getAnsiSupport() ? Ansi::Green : Ansi::Red) << (renderer.getAnsiSupport() ? "True" : "False") << Ansi::DefaultFG;
        
        renderer.render();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

}