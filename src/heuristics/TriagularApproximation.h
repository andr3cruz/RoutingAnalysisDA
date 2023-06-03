#ifndef ROUTINGANALYSISDA_TRIAGULARAPPROXIMATION_H
#define ROUTINGANALYSISDA_TRIAGULARAPPROXIMATION_H

#include "../data_structures/Graph.h"
#include "../data_structures/VertexEdge.h"
#include "../parser/ParserData.h"


class TriangularApproximation {
public:
    static vector<Vertex *> nearestNeighbor(Vertex *startVertex, int n, double &totalCost);
    static vector<Vertex*> findBestPath();
};

#endif //ROUTINGANALYSISDA_TRIAGULARAPPROXIMATION_H
