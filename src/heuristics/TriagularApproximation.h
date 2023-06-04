#ifndef ROUTINGANALYSISDA_TRIAGULARAPPROXIMATION_H
#define ROUTINGANALYSISDA_TRIAGULARAPPROXIMATION_H

#include "../data_structures/Graph.h"
#include "../data_structures/VertexEdge.h"
#include "../parser/ParserData.h"

/**
 * @brief A class that implements a triangular approximation algorithm for finding nearest neighbors and the best path in a graph.
 */

class TriangularApproximation {
public:
    /**
    * Finds the nearest neighbors of a given start vertex using a triangular approximation algorithm.
    *
    * @param startVertex The starting vertex for the nearest neighbor search.
    * @param n The number of nearest neighbors to find.
    * @param totalCost [out] The total cost of the nearest neighbor tour.
    * @return A vector of pointers to the nearest neighbor vertices.
    *
    * @note The time complexity of this method is O(n^2), where n is the number of vertices in the graph.
    */
    static vector<Vertex *> nearestNeighbor(Vertex *startVertex, int n, double &totalCost);

    /**
    * Finds the best path in the graph using the triangular approximation algorithm.
    *
    * @return A vector of pointers to the vertices representing the best path.
    *
    * @note The time complexity of this method is O(n^3), where n is the number of vertices in the graph.
    */
    static vector<Vertex*> findBestPath();
};

#endif //ROUTINGANALYSISDA_TRIAGULARAPPROXIMATION_H
