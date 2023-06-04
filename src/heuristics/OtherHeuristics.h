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
     * Finds the best path in the graph using the Christofides algorithm.
     *
     * @return A vector of pointers to the vertices representing the best path.
     */
    static vector<Vertex*> christofides();
    static vector<Vertex*> linKernighan();

private:
    /**
     * @brief Finds an Euler tour in the graph starting from the given start vertex.
     *
     * @param startVertex The starting vertex for the Euler tour.
     * @return A vector of pointers to the vertices representing the Euler tour.
     *
     * @note The time complexity of this method is O(|V| + |E|), where |V| is the number of vertices and |E| is the number of edges in the graph.
    */
    static vector<Vertex*> eulerTour(Vertex* startVertex);

    /**
     * @brief Constructs a Hamiltonian cycle from the given Euler tour and calculates the path cost.
     *
     * @param eulerTour The Euler tour used to construct the Hamiltonian cycle.
     * @param pathCost [out] The path cost of the Hamiltonian cycle.
     * @return A vector of pointers to the vertices representing the Hamiltonian cycle.
     *
     * @note The time complexity of this method is O(|V|), where |V| is the number of vertices in the Euler tour.
    */
    static vector<Vertex*> makeHamiltonian(vector<Vertex*> eulerTour, double& pathCost);
D
    /**
     * @brief Finds the path cost of the best path starting from the given start vertex using the Euler tour and Hamiltonian cycle heuristics.
     *
     * @param start The starting vertex for the best path search.
     * @return The path cost of the best path.
    */
    static double findBestPath(Vertex* start);

    /**
     * @brief Applies the 2-opt exchange operation to improve the given tour by swapping edges.
     *
     * @param tour The tour to improve.
     * @param i The starting index of the 2-opt exchange.
     * @param j The ending index of the 2-opt exchange.
    */
    static void apply2OptExchange(vector<Vertex*>& tour, int i, int j);

    /**
     * @brief Finds the best improvement by performing a 2-opt exchange operation on the given tour.
     *
     * @param tour The tour to search for improvement.
     * @param i [out] The starting index of the best improvement.
     * @param j [out] The ending index of the best improvement.
     * @return True if an improvement is found, false otherwise.
     *
     * @note The time complexity of this method is O(|V|^2), where |V| is the number of vertices in the tour.
    */
    static bool findBestImprovement(vector<Vertex*>& tour, int& i, int& j);

};

#endif //ROUTINGANALYSISDA_OTHERHEURISTICS_H
