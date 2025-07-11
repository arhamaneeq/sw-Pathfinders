#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "types.hpp"
#include "gameboard.hpp"
#include "graph.hpp"

class Solver {
    private:

        Grid& grid;
        Graph graph;
        std::variant<std::stack<Coord>,
                     std::queue<Coord>,
                     std::priority_queue<std::pair<float, Coord>,
                                         std::vector<std::pair<float, Coord>>,
                                         std::greater<>>> frontier;

        std::unordered_map<Coord, Coord> cameFrom;
        std::set<Coord> visited;
        std::unordered_map<Coord, Coord> parent;
        Coord startpoint, endpoint;
        
        Algorithm algo;
        State state;
        int numFrames;
        
        void stepDjikstra(); // TODO:
        void stepAStar();
        void stepDFS();
        void stepBFS();

    public:
        Solver(Grid& grid); // TODO:
        ~Solver();
        
        int setup(); // TODO:
        void reset();

        void step(); // TODO:

        bool isStopped() const;
        std::vector<Coord> getPath() const;

        void setAlgo(Algorithm algo);

        int getFrames() const;
    };

#endif