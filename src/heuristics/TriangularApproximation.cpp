#include "TriangularApproximation.h"


vector<Vertex*> TriangularApproximation::eulerTour(Vertex* startVertex) {

    vector<Vertex*> eulerTour;
    // Create an empty stack to store the Euler tour
    stack<Vertex*> tourStack;

    // Push the starting vertex onto the stack
    tourStack.push(startVertex);

    while (!tourStack.empty()) {
        Vertex* currentVertex = tourStack.top();

        // Check if the current vertex has any remaining outgoing edges
        if (!currentVertex->getAdj().empty()) {
            // Get the next adjacent vertex
            Vertex* nextVertex = currentVertex->getAdj()[0]->getDest();

            // Remove the edge between the current vertex and the next vertex
            currentVertex->removeEdge(nextVertex->getId());

            // Push the next vertex onto the stack
            tourStack.push(nextVertex);
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



vector<Vertex*> TriangularApproximation::makeHamiltonian(vector<Vertex*> eulerTour, int& pathCost){

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
                pathCost += aux->getWeight();
            }
        }
    }

    // Add the cost of the last edge to the pathCost
    Vertex* lastVertex = hamiltonianCycle.back();
    Vertex* firstVertex = hamiltonianCycle.front();
    Edge* edge = lastVertex->getEdgeTo(firstVertex);
    pathCost += edge->getWeight();

    return hamiltonianCycle;
}


int TriangularApproximation::findBestPath(Vertex* start){
    vector<Vertex*> path = eulerTour(start);
    int pathCost;
    makeHamiltonian(path,pathCost);
    return pathCost;
}



vector<Vertex*> TriangularApproximation::christofides(Graph graph){
    vector<Vertex*> finalPath;
    int finalCost;

    unordered_map<int, Vertex*> mstOdds = graph.perfectMatching();
    int bestCost = INT_MAX;
    Vertex* bestVertex= mstOdds[0];
    for (auto elem : mstOdds) {
        int result = findBestPath(elem.second);
        if (result < bestCost){
            bestCost = result;
            bestVertex = elem.second;
        }
    }

    finalPath = makeHamiltonian(eulerTour(bestVertex), finalCost);

    return finalPath;

}