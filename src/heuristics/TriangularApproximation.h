#ifndef ROUTINGANALYSISDA_TRIANGULARAPPROXIMATION_H
#define ROUTINGANALYSISDA_TRIANGULARAPPROXIMATION_H

#include "../data_structures/VertexEdge.h"
#include "../data_structures/Graph.h"

class TriangularApproximation{
public:
    vector<Vertex*> eulerTour(Vertex* startVertex);
    vector<Vertex*> makeHamiltonian(vector<Vertex*> eulerTour, int& pathCost);
    int findBestPath(Vertex* start);
    vector<Vertex*> christofides(Graph graph);

};


#endif //ROUTINGANALYSISDA_TRIANGULARAPPROXIMATION_H
