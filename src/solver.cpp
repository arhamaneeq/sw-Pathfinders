#include "../include/solver.hpp"

Solver::Solver(Grid& grid) : grid(&grid), state(State::NO_INIT) {}

void Solver::setup() {
    //Find start and end points
    for (Cell cell : grid->getBoard()) {
        if (cell.type == cellType::Start) {startpoint = cell.coordinate;};
        if (cell.type == cellType::Goal) {endpoint = cell.coordinate;};

        if ((startpoint != Coord{-1, -1}) && (endpoint != Coord{-1, -1})) {break;};
    }

    // set heuristics
    for (Cell cell : grid->getBoard()) {
        cell.heuristic = (cell.coordinate - endpoint).manhattan();
    }

    state = State::INIT;
}

void Solver::reset() {
    // TODO: how tf should this work
}

void Solver::stepDjikstra() {
    // TODO:
}

void Solver::stepAStar() {
    // TODO:
}

void Solver::stepBFS() {
    // TODO:
}

void Solver::stepDFS() {
    // TODO:
}

void Solver::step() {
    switch (algo) {
        case Algorithm::AStar:
            stepAStar();
            break;
        case Algorithm::Djikstra:
            stepDjikstra();
            break;
        case Algorithm::BFS:
            stepBFS();
            break;
        case Algorithm::DFS:
            stepDFS();
            break;
    }
}

bool Solver::isStopped() const {
    return (state == State::SOLVED);
}

