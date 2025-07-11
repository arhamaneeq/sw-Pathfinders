#ifndef UTILS_HPP
#define UTILS_HPP

#include "types.hpp"

/**
 * @namespace Utils
 * @brief Provides utility functions for terminal and system feature detection and control.
 *
 * The Utils namespace contains helper functions to query terminal capabilities such as size,
 * color support, UTF-8 support, and ANSI escape sequence support. It also provides functions
 * to enable ANSI support and to pause execution for a specified duration.
 */
namespace Utils {
    std::pair<int, int> getTerminalSize();
    bool getColourSupport();
    bool getUTF8Support();
    bool getAnsiSupport();

    void enableAnsiSupport();

    void wait(int ms);
}
#endif