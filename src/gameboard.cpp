#include "../include/gameboard.hpp"
#include "../include/types.hpp"
#include "../include/errors.hpp"

Grid::Grid(std::pair<int, int> wd) : width(wd.first), height(wd.second), grid((wd.first + 2) * (wd.second + 2)), config(this) {}
Grid::~Grid() = default;

int Grid::getIndex(const Coord& P) const {
    int x = P.x, y = P.y;

    x++; y++;
    if (x < 0 || y < 0 || x > width || y > height) {
        Errors::outOfBoundingBox(x, y, width, height);
    }
    return x + y * width;
}

int Grid::getWidth() const {
    return width;
}

int Grid::getHeight() const {
    return height;
}

const Cell& Grid::getCell(const Coord& P) const {
    return grid[getIndex(P)];
}

void Grid::setCell(const Coord& P, const Cell& cell) {
    int i = getIndex(P);

    grid[i].cost = cell.cost;
    grid[i].heuristic = cell.heuristic;
    grid[i].type = cell.type;
    grid[i].visited = cell.visited;
}

void Grid::setCellType(const Coord& P, cellType type) {
    grid[getIndex(P)].type = type;
}

void Grid::setCellVisit(const Coord& P, bool visited) {
    grid[getIndex(P)].visited = visited;
}

void Grid::setCellCost(const Coord& P, float cost) {
    grid[getIndex(P)].cost = cost;
}

void Grid::setCellHeuristic(const Coord& P, float h) {
    grid[getIndex(P)].heuristic = h;
}

Grid::Configurator::Configurator(Grid* b) : grid(b) {};

void Grid::Configurator::createWallAt(const Coord& P) {
    (*grid).setCellType(P, cellType::Wall);
}

void Grid::Configurator::createWallHorizontal(const Coord& P, int len) {
    if (P.x + len > grid->getWidth()) {Errors::outOfBoundingRange(P.x + len, grid->getWidth());}
    
    for (int x = P.x; x < P.x + len; x++) {
        (*grid).setCellType(Coord{x, P.y}, cellType::Wall);
    }
}

void Grid::Configurator::createWallVertical(const Coord& P, int len) {
    if (P.y + len > grid->getHeight()) {Errors::outOfBoundingRange(P.y + len, grid->getHeight());}
    
    for (int y = P.y; y < P.y + len; y++) {
        (*grid).setCellType(Coord{P.x, y}, cellType::Wall);
    }
}

void Grid::Configurator::createTypeAt(const Coord&P, cellType type) {
    (*grid).setCellType(P, type);
}

void Grid::Configurator::createEmptyAt(const Coord& P) {
    (*grid).setCellType(P, cellType::Empty);
}