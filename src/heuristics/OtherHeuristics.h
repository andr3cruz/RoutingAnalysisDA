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

    /**
     * @brief Finds the best path in the graph using the Christofides algorithm.
     * @details Time Complexity: O(E log V + V^2)
     * @return A vector of pointers to the vertices representing the best path.
     */
    static pair<list<Vertex*>, double> christofides();

private:

    /**
     * @brief Finds an Euler tour in the graph starting from the given start vertex.
     *
     * @param startVertex The starting vertex for the Euler tour.
     * @return A vector of pointers to the vertices representing the Euler tour.
     *
     * @details Time Complexity: O(|V| + |E|), where |V| is the number of vertices and |E| is the number of edges in the graph.
    */
    static list<Vertex*> eulerTour(Vertex* startVertex);

    /**
     * @brief Constructs a Hamiltonian cycle from the given Euler tour and calculates the path cost.
     *
     * @param eulerTour The Euler tour used to construct the Hamiltonian cycle.
     * @param pathCost [out] The path cost of the Hamiltonian cycle.
     * @return A vector of pointers to the vertices representing the Hamiltonian cycle.
     *
     * @details Time Complexity: O(|V|), where |V| is the number of vertices in the Euler tour.
    */
    static void makeHamiltonian(list<Vertex*>& eulerTour, double& pathCost);
};

#endif //ROUTINGANALYSISDA_OTHERHEURISTICS_H
