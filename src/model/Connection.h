#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>

using namespace std;

/**
 * @brief Class that defines a segment that connects two nodes
 */

class Connection {
private:

    /// First Node's name
    int nodeA;

    /// Second Node's name
    int nodeB;

    /// Distance from nodeA to nodeB
    double distance;

public:

    /**
     * @brief Classe's Constructor
     * @param node_A
     * @param node_B
     * @param distance
    */
    Connection(const int& node_A, const int& node_B, double distance);

    /**
     * @brief Getter for the First Node's name
     * @returns The string of First Node's name
    */
    int getNodeA() const;

    /**
     * @brief Getter for the Second Node's name
     * @details Time Complexity: O(1)
     * @returns The string of Second Node's name
    */
    int getNodeB() const;

    /**
     * @brief Getter for the segment's distance
     * @details Time Complexity: O(1)
     * @returns The value of the segment's distance
    */
    double getDistance() const;
};

#endif //CONNECTION_H
