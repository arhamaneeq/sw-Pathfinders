#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "types.hpp"
#include "adjlist.hpp"

class Graph {
    private:
        AdjacencyList adjacencyList;
        bool isDirected;

    public:
        Graph(); // TODO:
        ~Graph();

        bool hasNode(const Coord& P) const;
        bool hasEdge(const Coord& P, const Coord& Q) const;

        void addNode(const Coord& P);
        void addEdge(const Coord& P, const Coord& Q, float w = 1.0f);

        void removeNode(const Coord& P);
        void removeEdge(const Coord& P, const Coord& Q);
        
        int getNumberOfNodes() const;
        int getNumberOfEdges() const;
        const std::vector<std::pair<Coord, float>> getNeighbours(const Coord& P) const;

        void clear();
        void setDirected(bool directed);
};

#endif