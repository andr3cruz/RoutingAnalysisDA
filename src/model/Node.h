#ifndef NODE_H
#define NODE_H

#include <string>

using namespace std;

/**
 * @brief Class that defines a Node
 */

class Node {
private:

    /// Node's id
    int id;

    /// Node's latitude
    double longitude;

    /// Node's longitude
    double latitude;

public:

    /**
     * @brief Default Constructor
     */
    Node();

    /**
     * @brief Constructor
     * @param id
     * @param longitude
     * @param latitude
     */
    Node(const  int &id, const double &longitude, const double &latitude);

    /**
     * @brief Getter for the Node's id
     * @details Time Complexity: O(1)
     * @returns The integer of the Node's id
    */
    const int getId() const;

    /**
    * @brief Getter for the Node's longitude
    * @details Time Complexity: O(1)
    * @returns The double of the Node's longitude
    */
    const double getLongitude() const;

    /**
     * @brief Getter for the Node's latitude
     * @details Time Complexity: O(1)
     * @returns The double of the Node's latitude
    */
    const double getLatitude() const;

    /**
     * @brief Operator < overload
    */
    bool operator<(const Node& other) const {
        return id < other.id;
    }

};

#endif //NODE_H
