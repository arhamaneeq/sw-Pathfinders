#include "../include/solver.hpp"

Solver::Solver(Grid& grid) : grid(grid), state(State::NO_INIT), startpoint(Coord{-1, -1}), endpoint(Coord{-1, -1}) {}
Solver::~Solver() = default;

void Solver::setup() {
    //Find start and end points
    for (Cell cell : grid.getBoard()) {
        if (cell.type == cellType::Start) {startpoint = cell.coordinate;};
        if (cell.type == cellType::Goal) {endpoint = cell.coordinate;};

        if ((startpoint != Coord{-1, -1}) && (endpoint != Coord{-1, -1})) {break;};
    }

    // set heuristics
    for (Cell cell : grid.getBoard()) {
        grid.setCellHeuristic(cell.coordinate, (cell.coordinate - endpoint).manhattan());
    }

    state = State::INIT;
}

void Solver::reset() {
    // TODO: how tf should this work
}

void Solver::setAlgo(Algorithm alg) {
    algo = alg;
}

void Solver::stepDjikstra() {
    // TODO:
}

void Solver::stepAStar() {
    // TODO:
}

void Solver::stepBFS() {
    auto get = [](auto& var) -> std::queue<Coord>& {
        return std::get<std::queue<Coord>>(var);
    };

    if (state == State::INIT) {
        get(frontier).push(startpoint);
        cameFrom[startpoint] = startpoint;

        state = State::SOLVING;

        return;
    }

    if (get(frontier).empty()) {
        state = State::SOLVED;
        return;
    }

    if (state == State::SOLVED || state == State::NO_INIT) {return;}

    Coord current = get(frontier).front();
    get(frontier).pop();

    if (current == endpoint) {
        Coord step = endpoint;
        while (step != startpoint) {
            step = cameFrom[step];
            if (step != startpoint) {
                grid.setCellType(step, cellType::Path);
            }
        }

        state = State::SOLVED;
        return;
    }

    if (grid.getCell(current).type != cellType::Start) {grid.setCellType(current, cellType::Visited);}

    for (const Coord& neighbour : current.adjacent()) {
        if (cameFrom.count(neighbour) == 0 && grid.getCell(neighbour).type != cellType::Wall && grid.getCell(neighbour).type != cellType::Start) {
            get(frontier).push(neighbour);
            cameFrom[neighbour] = current;

            if (neighbour != endpoint) {grid.setCellType(neighbour, cellType::Frontier);}
        }
    }
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

