#ifndef UTILS_HPP
#define UTILS_HPP

#include "types.hpp"
#include<chrono>

namespace Utils {
    dims getTerminalSize();
    bool getColourSupport();
    bool getCharsetSupport();
    void sleep(int t);
}

#endif