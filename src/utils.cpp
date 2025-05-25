#include "../include/utils.hpp"

#if defined(__unix__) || defined(__APPLE__)

#include <sys/ioctl.h>
#include <unistd.h>
#include <cstdlib>
#include <string>

dims Utils::getTerminalSize() {
    dims dimensions;
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
        dimensions.width = 50;
        dimensions.height = 10;
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

#if defined(_WIN32) || defined(_WIN64)
#include<Windows.h>
#include<io.h>

dims Utils::getTerminalSize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    dims dimensions;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        dimensions.width  = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        dimensions.height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
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


#if defined(_WIN32) || defined(_WIN64)
bool Utils::getCharsetSupport() {
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