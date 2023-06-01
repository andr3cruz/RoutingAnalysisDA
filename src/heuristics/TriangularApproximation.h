#ifndef ROUTINGANALYSISDA_TRIANGULARAPPROXIMATION_H
#define ROUTINGANALYSISDA_TRIANGULARAPPROXIMATION_H

#include "../data_structures/VertexEdge.h"
#include "../parser/ParserData.h"
#include "../builder/GraphBuilder.h"

class TriangularApproximation{
public:
    static vector<Vertex*> christofides();
private:
    static vector<Vertex*> eulerTour(Vertex* startVertex);
    static vector<Vertex*> makeHamiltonian(vector<Vertex*> eulerTour, int& pathCost);
    static int findBestPath(Vertex* start);
};

#endif //ROUTINGANALYSISDA_TRIANGULARAPPROXIMATION_H
