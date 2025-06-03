#include "../include/graph.hpp"

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
    adjacencyList.removeEdge(P, Q);
}