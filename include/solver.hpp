#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "types.hpp"
#include "gameboard.hpp"
#include "graph.hpp"

class Solver {
    private:

        Grid* grid;
        Graph graph;
        std::set<Coord> visited;
        std::unordered_map<Coord, Coord> parent;
        Coord startpoint, endpoint;
        
        Algorithm algo;
        State state;
        
        void stepDjikstra(); // TODO:
        void stepAStar();
        void stepDFS();
        void stepBFS();

    public:
        Solver(Grid& grid); // TODO:
        ~Solver();
        
        void setup(); // TODO:
        void reset();

        void step(); // TODO:

        bool isStopped() const;
        std::vector<Coord> getPath() const;

        void setAlgo(Algorithm algo);
    };

#endif