#ifndef UTILS_HPP
#define UTILS_HPP

#include "types.hpp"

namespace Utils {
    std::pair<int, int> getTerminalSize();
    bool getColourSupport();
    bool getCharsetSupport();
    void sleep(int t);
}

namespace Errors {
    void outOfBoundingBox(int x, int y, int W, int H);
}

#endif