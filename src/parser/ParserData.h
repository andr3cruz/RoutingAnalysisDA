#ifndef NETWORK_PARSERDATA_H
#define NETWORK_PARSERDATA_H

#include "../../src/builder/GraphBuilder.h"
#include "NetworkParser.h"

/**
 * @brief Class that holds Network parsed data
 */

class ParserData{
public:

    /**
     * @brief Getter for the Network Edges
     * @return Edges
     */
    vector<Connection> getEdges();

    /**
     * @brief Getter for the Network Nodes
     * @return Nodes
     */
    set<Node> getNodes();

    /**
     * @brief Getter for the Network Graph
     * @return Graph
     */
    Graph* getGraph();

    /**
     * @brief Getter for the Empty Network Graph
     * @return Empty Graph
     */
    Graph getEmptyGraph();

    /**
     * @brief Rebuilds the graph after manipulation
     * @details Time Complexity: O(V+E), being V the number of vertexes and E the number of edges
     */
    void rebuildGraph();

    /**
     * @brief Searches the set for the node with "id"
     * @param id
     * @returns true if found and false otherwise
     */
    bool searchNodeId(const int& id);

    /**
     * @brief Default constructor that prepares and build the whole graph to be used
     * @details Time Complexity: O(V+E), being V the number of vertexes and E the number of edges
     */
    ParserData();

private:
    /// Network Parser object
    NetworkParser parser;

    /// Vector of Edges
    vector<Connection> edges;

    /// Set of Nodes
    set<Node> nodes;

    /// Network Graph
    Graph graph;

    /// Empty Network Graph
    Graph emptyGraph = Graph();
};

inline ParserData parserData;
#endif //NETWORK_PARSERDATA_H
