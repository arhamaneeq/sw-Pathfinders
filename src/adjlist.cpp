#include "../include/adjlist.hpp"

bool AdjacencyList::nodeExists(const Coord& P) const {
    return !(adj.find(P) == adj.end());
}

bool AdjacencyList::edgeExists(const Coord& P, const Coord& Q) const {
    auto it = adj.find(P);
    if (it == adj.end()) return false;

    for (const auto& [neighbour, weight] : it->second) {
        if (neighbour == Q) return true;
    }

    return false;
}

void AdjacencyList::addNode(const Coord& P) {
    if (!nodeExists(P)) {
        adj[P] = {};
    }
}

void AdjacencyList::addEdge(const Coord& P, const Coord& Q, float w) {
    if (!nodeExists(P) || !nodeExists(Q)) {
        throw std::runtime_error("Attempting to create edge between one or two non-existent nodes.");
    }

    if (!edgeExists(P, Q)) {
        adj[P].emplace_back(Q, w);
    }
}

void AdjacencyList::removeNode(const Coord& P) {
    for (auto& [node, edges] : adj) {
        edges.erase(
            std::remove_if(
                edges.begin(),
                edges.end(),
                [&](const std::pair<Coord, float>& edge) {
                    return edge.first == P;
                }
            ),
            edges.end()
        );
    } 
}

void AdjacencyList::removeEdge(const Coord& P, const Coord& Q) {
    auto it = adj.find(P);
    if (it == adj.end()) return;

    auto& neighbours = it->second;
    neighbours.erase(
        std::remove_if(
            neighbours.begin(),
            neighbours.end(),
            [&](const std::pair<Coord, float>& edge) {
                return edge.first == Q;
            }),
        neighbours.end()
    );
}






