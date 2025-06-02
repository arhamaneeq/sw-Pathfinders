#ifndef ADJACENCYLIST_HPP
#define ADJACENCYLIST_HPP

#include "types.hpp"

class AdjacencyList {
    private:
        std::unordered_map<Coord, std::vector<std::pair<Coord, float>>> adj;
    public:
        void addNode(const Coord& P);
        void addEdge(const Coord& P, const Coord& Q);
        void removeNode(const Coord& P);
        void removeEdge(const Coord& P, const Coord& Q);
        bool nodeExists(const Coord& P) const;
        bool edgeExists(const Coord& P, const Coord& Q) const;

        int numberOfNodes() const;
        int numberOfEdges() const;
};

#endif