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
     * @brief Rebuilds the graph using a new edges and nodes files
     * @details Time Complexity: O(V+E), being V the number of vertexes and E the number of edges
    */
    void rebuildGraph(const string &nodesPath, const string &edgesPath, const string &dataSetName);

    /**
     * @brief Rebuilds the graph using a new edges file
     * @details Time Complexity: O(V+E), being V the number of vertexes and E the number of edges
    */
    void rebuildGraph(const string &edgesPath, const string &dataSetName);

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

    /**
     * @brief Getter for the Data Set string field
     * @returns Current Data Set string
    */
    const string &getDataSet() const;

    /**
     * @brief Setter for the Data Set string field
    */
    void setDataSet(const string &newDataSet);

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

    /// Current Data Set
    string dataSet;
};

inline ParserData parserData;
#endif //NETWORK_PARSERDATA_H
