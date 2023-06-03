#ifndef ROUTINGANALYSISDA_OTHERHEURISTICS_H
#define ROUTINGANALYSISDA_OTHERHEURISTICS_H

#include "../data_structures/VertexEdge.h"
#include "../parser/ParserData.h"
#include "../builder/GraphBuilder.h"
#include "TriagularApproximation.h"

class OtherHeuristics{
public:
    static vector<Vertex*> christofides();
    static vector<Vertex*> linKernighan();

private:
    static vector<Vertex*> eulerTour(Vertex* startVertex);
    static vector<Vertex*> makeHamiltonian(vector<Vertex*> eulerTour, double& pathCost);
    static double findBestPath(Vertex* start);
    static void apply2OptExchange(vector<Vertex*>& tour, int i, int j);
    static bool findBestImprovement(vector<Vertex*>& tour, int& i, int& j);

};

#endif //ROUTINGANALYSISDA_OTHERHEURISTICS_H
