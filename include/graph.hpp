#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "types.hpp"
#include "adjlist.hpp"

class Graph {
    private:
        AdjacencyList adjacencyList;
        bool isDirected;

    public:
        Graph();
        ~Graph();

        void addNode(const Coord& P);
        void addEdge(const Coord& P, const Coord& Q, float w = 1.0f);

        void removeNode(const Coord& P);
        void removeEdge(const Coord& P, const Coord& Q);

        const std::vector<Coord>& neighbours(const Coord& P);
};

#endif