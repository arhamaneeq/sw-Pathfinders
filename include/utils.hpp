#ifndef UTILS_HPP
#define UTILS_HPP

#include "types.hpp"

namespace Utils {
    std::pair<int, int> getTerminalSize();
    bool getColourSupport();
    bool getUTF8Support();
    bool getAnsiSupport();

    void enableAnsiSupport();

    void wait(int ms);
}
#endif