#include "../include/adjlist.hpp"

AdjacencyList::AdjacencyList() : numNodes(0), numEdges(0), adj(0) {} // TODO: does this even makes sense
AdjacencyList::~AdjacencyList() = default;

bool AdjacencyList::hasNode(const Coord& P) const {
    return !(adj.find(P) == adj.end());
}

bool AdjacencyList::hasEdge(const Coord& P, const Coord& Q) const {
    auto it = adj.find(P);
    if (it == adj.end()) return false;

    for (const auto& [neighbour, weight] : it->second) {
        if (neighbour == Q) return true;
    }

    return false;
}

void AdjacencyList::addNode(const Coord& P) {
    if (!hasNode(P)) {
        adj[P] = {};
        numNodes++;
    }
}

void AdjacencyList::addEdge(const Coord& P, const Coord& Q, float w) {
    if (!hasNode(P) || !hasNode(Q)) {
        throw std::runtime_error("Attempting to create edge between one or two non-existent nodes.");
    }

    if (!hasEdge(P, Q)) {
        adj[P].emplace_back(Q, w);
        numEdges++;
    }

}

void AdjacencyList::removeNode(const Coord& P) {
    if (hasNode(P)) {
        for (auto& [node, edges] : adj) {
            edges.erase(
                std::remove_if(
                    edges.begin(),
                    edges.end(),
                    [&](const std::pair<Coord, float>& edge) {
                        if (edge.first == P) {
                            numEdges--;
                            return true;
                        } else {return false;};
                    }
                ),
                edges.end()
            );
        }
    
        adj.erase(P);
        numNodes--;
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
                if (edge.first == Q) {
                    numEdges--;
                    return true;
                } else {return false;};
            }),
        neighbours.end()
    );
}

const std::vector<std::pair<Coord, float>> AdjacencyList::getNeighboursFrom(const Coord& P) const {
    if (hasNode(P)) {
        return adj.find(P)->second;
    } else {
        return {};
    }
}

const std::vector<std::pair<Coord, float>> AdjacencyList::getNeighboursTo(const Coord& P) const {
    std::vector<std::pair<Coord, float>> incoming;

    for (const auto& [node, neighbours] : adj) {
        for (const auto& [neighbour, weight] : neighbours) {
            if (neighbour == P) {
                incoming.emplace_back(node, weight);
            }
        }
    }

    return incoming;
}

const std::vector<Coord> AdjacencyList::getAllNodes() const {
    std::vector<Coord> nodes;

    for (const auto& [node, _] : adj) {
        nodes.push_back(node);
    }

    return nodes;
}

int AdjacencyList::numberOfNodes() const {
    return numNodes;
}

int AdjacencyList::numberOfEdges() const {
    return numEdges;
}

void AdjacencyList::clear() {
    adj.clear();
    numEdges = 0;
    numNodes = 0;
}



