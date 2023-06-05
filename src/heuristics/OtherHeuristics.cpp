#include "OtherHeuristics.h"


list<Vertex*> OtherHeuristics::eulerTour(Vertex* startVertex) {

    list<Vertex*> eulerTour;
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



void OtherHeuristics::makeHamiltonian(list<Vertex*>& eulerTour, double& pathCost){

    set<Vertex *> aux;
    list<Vertex *> temp;

    for (auto elem = eulerTour.begin(); elem != eulerTour.end(); elem++) {
        auto next = std::next(elem, 1);
        if (next != eulerTour.end()) {
            pathCost += (*elem)->getEdgeTo(*next)->getWeight();
        }
        if (aux.find(*elem) == aux.end()) {
            aux.insert(*elem);
            temp.push_back(*elem);
        }
    }
    temp.push_back(eulerTour.back());

    eulerTour = temp;
}

pair<list<Vertex*>, double> OtherHeuristics::christofides(){

    Graph graph = *parserData.getGraph();

    Graph mstOdds = graph.perfectMatching();
    auto mstOddsVertexes = mstOdds.getVertexMap();

    double bestCost = 0;

    mstOdds.resetEdges();

    list<Vertex *> euler = eulerTour(mstOddsVertexes[0]);

    makeHamiltonian(euler, bestCost);

    return {euler, bestCost};

}

