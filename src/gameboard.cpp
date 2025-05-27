#include "../include/gameboard.hpp"
#include "../include/types.hpp"
#include "../include/errors.hpp"

GameBoard::GameBoard(int w, int h) : width(w), height(h), grid((w + 2) * (h + 2)), config(this) {}
GameBoard::~GameBoard() = default;

int GameBoard::getIndex(int x, int y) const {
    x++; y++;
    if (x < 0 || y < 0 || x > width || y > height) {
        Errors::outOfBoundingBox(x, y, width, height);
    }

    return x + y * width;
}

const Cell& GameBoard::getCell(int x, int y) const {
    return grid[getIndex(x, y)];
}

void GameBoard::setCell(int x, int y, const Cell& cell) {
    int i = getIndex(x, y);

    grid[i].cost = cell.cost;
    grid[i].heuristic = cell.heuristic;
    grid[i].type = cell.type;
    grid[i].visited = cell.visited;
}

void GameBoard::setCellType(int x, int y, cellType type) {
    grid[getIndex(x, y)].type = type;
}

void GameBoard::setCellVisit(int x, int y, bool visited) {
    grid[getIndex(x, y)].visited = visited;
}

void GameBoard::setCellCost(int x, int y, float cost) {
    grid[getIndex(x, y)].cost = cost;
}

void GameBoard::setCellHeuristic(int x, int y, float h) {
    grid[getIndex(x, y)].heuristic = h;
}

void GameBoard::Configurator::createWallHorizontal(int X, int Y, int len) {
    if (X + len > board->getWidth()) {Errors::outOfBoundingRange(X + len, board->getWidth());}
    
    for (int x = X; x < X + len; x++) {
        (*board).setCellType(x, Y, cellType::Wall);
    }
}

void GameBoard::Configurator::createWallVertical(int X, int Y, int len) {
    if (Y + len > board->getHeight()) {Errors::outOfBoundingRange(Y + len, board->getHeight());}
    
    for (int y = Y; y < Y + len; y++) {
        (*board).setCellType(X, y, cellType::Wall);
    }
}