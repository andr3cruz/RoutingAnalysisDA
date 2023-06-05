#include "TriagularApproximation.h"

vector<Vertex*> TriangularApproximation::nearestNeighbor(Vertex* startVertex, int n, double &totalCost) {
    vector<Vertex*> tour;
    Vertex* currentVertex = startVertex;
    currentVertex->setVisited(true);
    tour.push_back(currentVertex);
    Vertex* loopCheck = nullptr;

    while (tour.size() < n) {
        Edge* nextEdge = nullptr;
        double minDistance = std::numeric_limits<double>::max();

        if (currentVertex == loopCheck){
            totalCost = std::numeric_limits<double>::max();
            cout << totalCost << "\n";
            return {};
        }
        // Find the nearest unvisited neighbor
        for (Edge* edge : currentVertex->getAdj()) {
            Vertex* neighbor = edge->getDest();
            int neighborId = neighbor->getId();
            auto temp = *currentVertex->getDistances();
            if (!neighbor->isVisited() && temp[neighborId] < minDistance) {
                nextEdge = edge;
                minDistance = temp[neighborId];
            }
        }
        loopCheck = currentVertex;
        if (nextEdge != nullptr) {
            Vertex* nextVertex = nextEdge->getDest();
            nextVertex->setVisited(true);
            tour.push_back(nextVertex);
            currentVertex = nextVertex;
        }
        totalCost += minDistance;
    }

    totalCost += (*(*tour.rbegin())->getDistances())[0];
    tour.push_back(startVertex);

    cout << totalCost << "\n";
    return tour;
}

vector<Vertex*> TriangularApproximation::triangularApprox(){
    Graph graph = *parserData.getGraph();
    graph.resetVisits();
    unordered_map<int,Vertex*> allVertexes = graph.getVertexMap();
    double cost;
    return nearestNeighbor(allVertexes[0],allVertexes.size(),cost);
}

