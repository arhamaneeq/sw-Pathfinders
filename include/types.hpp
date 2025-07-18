#ifndef TYPES_HPP
#define TYPES_HPP

#include<vector>
#include<string>
#include<sstream>
#include<stdexcept>
#include<iostream>
#include<thread>
#include<chrono>
#include<algorithm>
#include<set>
#include<cmath>
#include<unordered_map>
#include<functional>
#include<queue>
#include<variant>
#include<stack>

struct Coord {
    int x, y;

    Coord operator+(const Coord& Q) const {
        return {x + Q.x, y + Q.y};
    }
    
    Coord operator-(const Coord& Q) const {
        return {x - Q.x, y - Q.y};
    }

    Coord operator-() const {
        return {-x, -y};
    }

    bool operator==(const Coord& Q) const {
        return ((x == Q.x) && (y == Q.y));
    }

    bool operator!=(const Coord& Q) const {
        return ((x != Q.x) || (y != Q.y));
    }

    int manhattan() const {
        return std::abs(x) + std::abs(y);
    }

    float magnitude() const {
        return std::sqrt(x*x + y*y);
    }

    std::vector<Coord> adjacent() {
        return {
            Coord{x - 1, y - 1},
            Coord{x,     y - 1},
            Coord{x + 1, y - 1},
            Coord{x + 1, y    },
            Coord{x + 1, y + 1},
            Coord{x    , y + 1},
            Coord{x - 1, y + 1},
            Coord{x - 1, y    }
        };
    }

    bool operator<(const Coord& other) const {
        return std::tie(x, y) < std::tie(other.x, other.y);
    }
};

namespace std {
    template <>
    struct hash<Coord> {
        std::size_t operator()(const Coord& c) const noexcept {
            return (std::hash<int>()(c.x) ^ (std::hash<int>()(c.y) << 1));
        }
    };
};


enum class Algorithm {
    Dijkstra,
    AStar,
    BFS,
    DFS,
    NONE
    // TODO: add support for more algorithms, RRT/RRT*, etc.
};

enum class State {
    NO_INIT,
    INIT,
    SOLVING,
    SOLVED
};

enum class UIState {
    LOADING,
    SETUP,
    SOLVING,
    SOLVED,
    END
};

enum class cellType {
    Empty,
    Wall,
    Start,
    Goal,
    Path,
    Visited,
    Frontier
};

struct Cell {
    cellType type;
    bool visited = false;
    float cost = 1.0f;
    float heuristic = 0.0f;
    Coord coordinate;
};

/**
 * @namespace Ansi
 * @brief Provides ANSI escape codes and utilities for terminal text formatting, colors, and cursor control.
 */
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
    constexpr const char* Grey      = "\033[90m";
    constexpr const char* Terracotta= "\033[91m";
    constexpr const char* Lime      = "\033[92m";
    constexpr const char* Sunny     = "\033[93m";
    constexpr const char* SkyBlue   = "\033[94m";
    constexpr const char* Pink      = "\033[95m";
    constexpr const char* Electric  = "\033[96m";

    constexpr const char* DefaultFG = "\033[39m";

    constexpr const char* ClearScreen   = "\033[2J";
    constexpr const char* ClearLine     = "\033[2K";
    constexpr const char* CursorHome    = "\033[H";
    constexpr const char* CursorSave    = "\033[s";
    constexpr const char* CursorRestore = "\033[u";

    inline std::string CursorUp(int n = 1)      {return "\033[" + std::to_string(n) + "A";}
    inline std::string CursorDown(int n = 1)    {return "\033[" + std::to_string(n) + "B";}
    inline std::string CursorRight(int n = 1)   {return "\033[" + std::to_string(n) + "C";}
    inline std::string CursorLeft(int n = 1)    {return "\033[" + std::to_string(n) + "D";}

    constexpr const char* CursorHide    = "\033[?25l";
    constexpr const char* CursorShow    = "\033[?25h";
}

struct ToolTip {
    std::string title;
    std::string text;
    int startingFrame, duration;
    std::initializer_list<std::string_view> styles;
    int width;
};


#endif
