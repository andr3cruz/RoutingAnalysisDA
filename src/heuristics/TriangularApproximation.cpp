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
            return {};
        }
        // Find the nearest unvisited neighbor
        for (Edge* edge : currentVertex->getAdj()) {
            Vertex* neighbor = edge->getDest();
            if (!neighbor->isVisited() && edge->getWeight() < minDistance) {
                nextEdge = edge;
                minDistance = edge->getWeight();
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

    return tour;
}

vector<Vertex*> TriangularApproximation::findBestPath(){
    Graph graph = *parserData.getGraph();
    graph.resetVisits();
    int n = graph.getVertexMap().size();
    Vertex* bestVertex;
    double bestCost = std::numeric_limits<double>::max();
    double cost;
    for (auto pair : graph.getVertexMap()){
        cost = 0;
        nearestNeighbor(pair.second,n,cost);
        if (cost < bestCost){
            bestCost = cost;
            bestVertex = pair.second;
        }
        graph.resetVisits();
    }
    cost = 0;
    return nearestNeighbor(bestVertex,n,cost);
}

