#ifndef ADJACENCYLIST_HPP
#define ADJACENCYLIST_HPP

#include "types.hpp"

class AdjacencyList {
    private:
        std::unordered_map<Coord, std::vector<std::pair<Coord, float>>> adj;

    public:
        bool hasNode(const Coord& P) const;
        bool hasEdge(const Coord& P, const Coord& Q) const;

        void addNode(const Coord& P);
        void addEdge(const Coord& P, const Coord& Q, float w = 1.0f);

        void removeNode(const Coord& P);
        void removeEdge(const Coord& P, const Coord& Q);

        const std::vector<std::pair<Coord, float>> getNeighboursFrom(const Coord&P ) const;
        const std::vector<std::pair<Coord, float>> getNeighboursTo(const Coord& P) const;
        const std::vector<Coord> getAllNodes() const;

        int numberOfNodes() const;
        int numberOfEdges() const;
};

#endif