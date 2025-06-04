#include "../include/solver.hpp"

void Solver::setup() {
    // TODO: find start and end points
    // TODO: set state
    // TODO: calculate heuristics
}

void Solver::reset() {
    // TODO: how tf should this work
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