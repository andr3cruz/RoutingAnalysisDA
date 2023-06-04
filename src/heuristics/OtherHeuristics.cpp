#include "OtherHeuristics.h"


vector<Vertex*> OtherHeuristics::eulerTour(Vertex* startVertex) {

    vector<Vertex*> eulerTour;
    // Create an empty stack to store the Euler tour
    stack<Vertex*> tourStack;

    // Push the starting vertex onto the stack
    tourStack.push(startVertex);

    while (!tourStack.empty()) {
        Vertex* currentVertex = tourStack.top();
        list<Edge *>* temp1 = currentVertex->getVisited();

        // Check if the current vertex has any remaining outgoing edges
        if (!temp1->empty()) {
            // Get the next adjacent vertex
            for (auto edge : *temp1) {
                Vertex* nextVertex = edge->getDest();

                list<Edge *>* temp2 = nextVertex->getVisited();

                // Remove the edge between the current vertex and the next vertex
                temp1->remove(currentVertex->getEdgeToVisited(nextVertex));
                temp2->remove(nextVertex->getEdgeToVisited(currentVertex));

                // Push the next vertex onto the stack
                 tourStack.push(nextVertex);
                 break;
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
    mstOdds.resetEdges();
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


vector<Vertex*> OtherHeuristics::linKernighan(){

    Graph graph = *parserData.getGraph();
    double totalCost = 0.0;

    unordered_map<int,Vertex*> tmp = graph.getVertexMap();

    // Perform nearest neighbor heuristic to construct the initial tour
    vector<Vertex*> initTour = TriangularApproximation::nearestNeighbor(tmp[0],graph.getVertexMap().size(),totalCost);

    int n = initTour.size();
    double minTotalCost = numeric_limits<double>::max();
    vector<Vertex*> bestTour;

    for (int i = 0; i < n; i++) {
        totalCost = 0.0;
        vector<Vertex*> tour = TriangularApproximation::nearestNeighbor(initTour[i], n, totalCost);

        if (totalCost < minTotalCost) {
            minTotalCost = totalCost;
            bestTour = tour;
        }
    }

    // Apply Lin-Kernighan Heuristic to improve the initial tour
    int iterations = 1000;  // Adjust the number of iterations as needed

    while (iterations > 0) {
        int i, j;
        bool improvement = findBestImprovement(bestTour, i, j);

        if (improvement) {
            apply2OptExchange(bestTour, i, j);
        } else {
            // No further improvement found, terminate the algorithm
            break;
        }

        iterations--;
    }

    return bestTour;
}

void OtherHeuristics::apply2OptExchange(vector<Vertex*>& tour, int i, int j) {
    while (i < j) {
        swap(tour[i], tour[j]);
        i++;
        j--;
    }
}

bool OtherHeuristics::findBestImprovement(vector<Vertex*>& tour, int& i, int& j) {
    int n = tour.size();
    double bestImprovement = 0.0;
    bool foundImprovement = false;

    for (int a = 0; a < n - 2; ++a) {
        for (int b = a + 2; b < n; ++b) {
            int c = (a + 1) % n;
            int d = (b + 1) % n;

            double gain = tour[a]->getEdgeTo(tour[c])->getWeight() + tour[b]->getEdgeTo(tour[d])->getWeight()
                    - tour[a]->getEdgeTo(tour[b])->getWeight() - tour[c]->getEdgeTo(tour[d])->getWeight();

            if (gain > bestImprovement) {
                bestImprovement = gain;
                i = a;
                j = b;
                foundImprovement = true;
            }
        }
    }

    return foundImprovement;
}