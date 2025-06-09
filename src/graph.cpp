#include "../include/graph.hpp"

bool Graph::hasNode(const Coord& P) const {
    return adjacencyList.hasNode(P);
}

bool Graph::hasEdge(const Coord& P, const Coord& Q) const {
    return adjacencyList.hasEdge(P, Q);
}

void Graph::addNode(const Coord& P) {
    adjacencyList.addNode(P);
}

void Graph::addEdge(const Coord& P, const Coord& Q, float w) {
    if (isDirected) {
        adjacencyList.addEdge(P, Q, w);
    } else {
        adjacencyList.addEdge(P, Q, w);
        adjacencyList.addEdge(Q, P, w);
    }
}

void Graph::removeNode(const Coord& P) {
    adjacencyList.removeNode(P);
}

void Graph::removeEdge(const Coord& P, const Coord& Q) {
    if (isDirected) {
        adjacencyList.removeEdge(P, Q);
    } else {
        adjacencyList.removeEdge(P, Q);
        adjacencyList.removeEdge(Q, P);
    }
}

const std::vector<std::pair<Coord, float>> Graph::getNeighbours(const Coord& P) const {
    std::vector<std::pair<Coord, float>> neighbours;

    if (!adjacencyList.hasNode(P)) return neighbours;

    for (const auto& [q, w] : adjacencyList.getNeighboursFrom(P)) {
        neighbours.emplace_back(q, w);
    }

    if (isDirected) {
        for (const Coord& node : adjacencyList.getAllNodes()) {
            for (const auto& [target, weight] : adjacencyList.getNeighboursFrom(node)) {
                if (target == P) {
                    neighbours.emplace_back(node, weight);
                }
            }
        }
    }

    return neighbours;
}

int Graph::getNumberOfNodes() const {
    return adjacencyList.numberOfNodes();
}

int Graph::getNumberOfEdges() const {
    return ((isDirected) 
        ? adjacencyList.numberOfEdges() 
        : (adjacencyList.numberOfEdges() / 2));
}

void Graph::setDirected(bool directed) {
    isDirected = directed;
}

void Graph::clear() {
    adjacencyList.clear();
}