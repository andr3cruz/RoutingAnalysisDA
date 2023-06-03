#include "OtherHeuristics.h"


vector<Vertex*> OtherHeuristics::eulerTour(Vertex* startVertex) {

    vector<Vertex*> eulerTour;
    // Create an empty stack to store the Euler tour
    stack<Vertex*> tourStack;

    // Push the starting vertex onto the stack
    tourStack.push(startVertex);

    while (!tourStack.empty()) {
        Vertex* currentVertex = tourStack.top();

        // Check if the current vertex has any remaining outgoing edges
        if (!currentVertex->isAllTraversed()) {
            // Get the next adjacent vertex
            for (auto edge : currentVertex->getAdj()) {
                if (!edge->getTraversed()) {
                    Vertex* nextVertex = edge->getDest();

                    // Remove the edge between the current vertex and the next vertex
                    currentVertex->getEdgeTo(nextVertex)->setTraversed(true);
                    nextVertex->getEdgeTo(currentVertex)->setTraversed(true);

                    // Push the next vertex onto the stack
                    tourStack.push(nextVertex);
                    break;
                }
            }
        }
        else {
            // If the current vertex has no more outgoing edges, it is part of the Euler tour
            // Print or process the vertex as desired
            eulerTour.push_back(currentVertex);

            // Pop the current vertex from the stack
            tourStack.pop();
        }
    }
    return eulerTour;
}



vector<Vertex*> OtherHeuristics::makeHamiltonian(vector<Vertex*> eulerTour, double& pathCost){

    vector<Vertex*> hamiltonianCycle;
    int n = eulerTour.size();

    // Initialize visited array
    vector<bool> visited(n, false);

    pathCost = 0;

    // Traverse the Euler tour
    for (int i = 0; i < n; i++) {
        Vertex* vertex = eulerTour[i];

        // Check if the vertex has been visited
        if (!visited[vertex->getId()]) {
            hamiltonianCycle.push_back(vertex);
            visited[vertex->getId()] = true;

            // Add the cost of the edge to the pathCost
            if (i < n - 1) {
                Vertex* nextVertex = eulerTour[i + 1];
                Edge* aux= eulerTour[i]->getEdgeTo(nextVertex);
                if (aux != nullptr) {
                    pathCost += aux->getWeight();
                }
            }
        }
    }

    // Add the cost of the last edge to the pathCost
    Vertex* lastVertex = hamiltonianCycle.back();
    Vertex* firstVertex = hamiltonianCycle.front();
    Edge* edge = lastVertex->getEdgeTo(firstVertex);
    if (edge == nullptr) {
        pathCost = std::numeric_limits<double>::max();
        return {};
    }
    pathCost += edge->getWeight();

    return hamiltonianCycle;
}


double OtherHeuristics::findBestPath(Vertex* start){
    vector<Vertex*> path = eulerTour(start);
    double pathCost;
    makeHamiltonian(path,pathCost);
    return pathCost;
}



vector<Vertex*> OtherHeuristics::christofides(){

    Graph graph = *parserData.getGraph();

    vector<Vertex*> finalPath;
    double finalCost;

    Graph mstOdds = graph.perfectMatching();
    auto mstOddsVertexes = mstOdds.getVertexMap();

    double bestCost = std::numeric_limits<double>::max();
    Vertex* bestVertex= mstOddsVertexes[1];
    for (auto elem : mstOddsVertexes) {
        double result = findBestPath(elem.second);
        if (result < bestCost){
            bestCost = result;
            bestVertex = elem.second;
        }
        mstOdds.resetEdges();
    }

    finalPath = makeHamiltonian(eulerTour(bestVertex), finalCost);

    return finalPath;

}