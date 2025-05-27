#include "../include/gameboard.hpp"
#include "../include/types.hpp"

GameBoard::GameBoard(int w, int h) : width(w), height(h), grid((w + 2) * (h + 2)) {}
GameBoard::~GameBoard() = default;

int GameBoard::getIndex(int x, int y) {
    x++; y++;
    if (x < 0 || y < 0 || x > width || y > height) {
        Errors::outOfBoundingBox(x, y, width, height);
    }

    return x + y * width;
}

