#ifndef TYPES_HPP
#define TYPES_HPP

struct dims {
    int width;
    int height;
};

enum class cellType {
    Empty,
    Wall,
    Start,
    Goal,
    Path,
    Visited
};

struct Cell {
    cellType type;
    bool visited = false;
    float cost = 1.0f;
    float heuristic = 0.0f;
};

namespace Ansi {
    constexpr const char* Reset = "\033[0m";

    constexpr const char* Bold   = "\033[1m";
    constexpr const char* Dim    = "\033[2m";
    constexpr const char* Italic = "\033[3m";
    constexpr const char* Blink  = "\033[5m"; 

    constexpr const char* Black     = "\033[30m";
    constexpr const char* Red       = "\033[31m";
    constexpr const char* Green     = "\033[32m";
    constexpr const char* Yellow    = "\033[33m";
    constexpr const char* Blue      = "\033[34m";
    constexpr const char* Magenta   = "\033[35m";
    constexpr const char* Cyan      = "\033[36m";
    constexpr const char* White     = "\033[37m";
    constexpr const char* DefaultFG = "\033[39m";

    constexpr const char* ClearScreen   = "\033[2J";
    constexpr const char* ClearLine     = "\033[2K";
    constexpr const char* CursorHome    = "\033[H";
    constexpr const char* CursorSave    = "\033[s";
    constexpr const char* CursorRestore = "\033[u";
}

#endif