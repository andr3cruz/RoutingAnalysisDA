#ifndef NETWORK_PARSER_H
#define NETWORK_PARSER_H

#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <codecvt>
#include <algorithm>
#include "../data_structures/VertexEdge.h"

using namespace std;

/**
 * @brief Class responsible for parsing the files
 */

class NetworkParser {

private:

    ///String that separates the different bits of info in the csv files
    const string splitter = ";";

    /**
     * @brief Processes a line
     * @details Time Complexity: O(n), being n the number of characters on the string
     * @param line
     * @returns the processed line as a string
     */
    static string lineTransformer(string line);

public:

    /**
     * @brief Parses edges.csv files
     * @details Time Complexity: O(E), being E the number of edges
     * @param file
     * @returns a vector with all edge objects that define a connection between two nodes
     */
    vector<Connection> parseConnections(const string& file);

    /**
     * @brief Parses nodes.csv files
     * @details Time Complexity: O(V), being V the number of vertexes
     * @param file
     * @returns a set with all node objects
     */
    set<Node> parseNodes(const string& file);

    set<Node> parseDefaultNodes();

    };

#endif //NETWORK_PARSER_H
