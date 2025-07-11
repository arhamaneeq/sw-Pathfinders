#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "types.hpp"
#include "gameboard.hpp"
#include "graph.hpp"

/**
 * @class Solver
 * @brief Provides pathfinding algorithms (Dijkstra, A*, DFS, BFS) for navigating a grid-based game board.
 *
 * The Solver class manages the state and execution of various pathfinding algorithms on a given grid.
 * It supports step-wise execution, algorithm selection, and path retrieval, facilitating visualization
 * and analysis of search strategies.
 */
class Solver {
    private:

        Grid& grid;
        // Graph graph;                                                         // TODO: add support for custom graphs later
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
        
        void stepDjikstra();
        void stepAStar();
        void stepDFS();
        void stepBFS();

    public:
        Solver(Grid& grid);
        ~Solver();
        
        int setup();
        void reset();

        void step();

        bool isStopped() const;
        std::vector<Coord> getPath() const;

        void setAlgo(Algorithm algo);

        int getFrames() const;
    };

#endif