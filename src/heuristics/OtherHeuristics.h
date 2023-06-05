#ifndef ROUTINGANALYSISDA_OTHERHEURISTICS_H
#define ROUTINGANALYSISDA_OTHERHEURISTICS_H

#include "../data_structures/VertexEdge.h"
#include "../parser/ParserData.h"
#include "../builder/GraphBuilder.h"
#include "TriagularApproximation.h"

/**
 * @brief A class that implements various heuristics for solving graph optimization problems.
 */

class OtherHeuristics{
public:
    static pair<list<Vertex*>, double> christofides();
private:
    static list<Vertex*> eulerTour(Vertex* startVertex);
    static void makeHamiltonian(list<Vertex*>& eulerTour, double& pathCost);
};

#endif //ROUTINGANALYSISDA_OTHERHEURISTICS_H
