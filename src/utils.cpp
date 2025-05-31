#include "../include/utils.hpp"

#if defined(__unix__) || defined(__APPLE__)

#include <sys/ioctl.h>
#include <unistd.h>
#include <cstdlib>
#include <string>

std::pair<int, int> Utils::getTerminalSize() {
    std::pair<int, int> dimensions;
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
        dimensions.first = 50;
        dimensions.second = 10;
        return dimensions; // fallback
    }

    dimensions.width = w.ws_col;
    dimensions.height = w.ws_row;
    return dimensions;
}

bool Utils::getColourSupport() {
    if (!isatty(fileno(stdout))) return false;

    const char* term = std::getenv("TERM");
    if (!term) return false;

    std::string termStr(term);
    return termStr.find("color") != std::string::npos ||
           termStr.find("ansi")  != std::string::npos ||
           termStr.find("xterm") != std::string::npos ||
           termStr.find("screen")!= std::string::npos;
}

#endif

#if defined(_WIN32)
#include<Windows.h>
#include<io.h>

std::pair<int, int> Utils::getTerminalSize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    std::pair<int, int> dimensions;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        dimensions.first  = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        dimensions.second = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }

    return dimensions;
}

bool Utils::getColourSupport() {
    if (!_isatty(_fileno(stdout))) return false;

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return false;

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return false;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode)) return false;

    return true;
}

#endif


#if defined(_WIN32)
bool Utils::getUTF8Support() {
    return GetConsoleOutputCP() == 65001;
}
#else
bool Utils::getCharsetSupport() {
    const char* charsetEnvVars[] = { "LC_ALL", "LC_CTYPE", "LANG" };
    for (const char* var : charsetEnvVars) {
        const char* val = std::getenv(var);
        if (val) {
            std::string locale(val);
            if (locale.find("UTF-8") != std::string::npos || locale.find("utf8") != std::string::npos)
                return true;
        }
    }
    return false;
}

#endif

#if defined(_WIN32)
#include <windows.h>

void Utils::enableAnsiSupport() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    if (GetConsoleMode(hOut, &dwMode)) {
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        if (!SetConsoleMode(hOut, dwMode)) {
            throw std::runtime_error("Failed to enable ANSI Support!");
        }
    }
}

#else 

void Utils::enableAnsiSupport() {
    // No-op
}

#endif

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <io.h>

bool Utils::getAnsiSupport() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE || !_isatty(_fileno(stdout)))
        return false;

    DWORD mode = 0;
    if (!GetConsoleMode(hOut, &mode))
        return false;

    // Check if ANSI escape sequence support is already enabled
    return (mode & ENABLE_VIRTUAL_TERMINAL_PROCESSING) != 0;
}

#else // Unix-like systems

#include <unistd.h>

bool Utils::getAnsiSupport() {
    return isatty(fileno(stdout)); // Assume ANSI if writing to terminal
}

#endif