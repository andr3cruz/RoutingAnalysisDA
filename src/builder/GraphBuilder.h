#ifndef ROUTINGANALYSISDA_GRAPHBUILDER_H
#define ROUTINGANALYSISDA_GRAPHBUILDER_H

#include <set>
#include "../data_structures/Graph.h"
#include "../model/Node.h"
#include "../model/Connection.h"
#include "../heuristics/TriagularApproximation.h"


using namespace std;

/**
 * @brief Builder class for Graphs
 */

class GraphBuilder {
public:

    /**
     * @brief Network graph builder
     * @details Time Complexity: O(V+E), being V the number of vertexes and E the number of edges
     * @param nodes
     * @param connections
     * @returns Graph
     */
    static Graph buildGraph(const set<Node>& nodes, const vector<Connection>& connections);
private:

    /**
     * @brief Nodes builder
     * @details Time Complexity: O(V) being V the number of nodes in the nodes.csv file
     * @param nodes
     * @param graph
     */
    static void buildNodes(const set<Node>& nodes, Graph& graph);

    /**
     * @brief Runs dijkstra's algorithm through every vertex of the graph to store all the distances
     * @details Time Complexity: O(V^2 + VE log V), being V the number of vertexes and E the nuber of edges
     * @param graph
     */
    static void setUp(Graph graph);


    /**
     * @brief Edges builder
     * @details Time Complexity: O(E) being E the number of connections in the edges.csv file
     * @param nodes
     * @param connections
     * @param graph
     */
    static void buildEdges(const set<Node>& nodes, const vector<Connection>& connections, Graph& graph);
};

#endif //ROUTINGANALYSISDA_GRAPHBUILDER_H