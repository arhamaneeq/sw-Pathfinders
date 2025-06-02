#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "types.hpp"
#include "gameboard.hpp"

class Solver {
    private:
        Grid grid;
        Coord starting, ending;
        Algorithm algo;
        Graph graph; //TODO: build Graph

        void stepDjikstra();
        void stepAStar();
        void stepDFS();
        void stepBFS();

        void setup();
    public:
        Solver(const Grid& grid);
        ~Solver();

        void step();

        bool isStopped() const;
        std::vector<Coord> getPath() const;

        void setAlgo(Algorithm algo);
    };

#endif