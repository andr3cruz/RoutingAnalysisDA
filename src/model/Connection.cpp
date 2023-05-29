#include "Connection.h"

Connection::Connection(const int &nodeA, const int &nodeB, const double distance) : nodeA(nodeA), nodeB(nodeB), distance(distance) {}

int Connection::getNodeA() const {
    return nodeA;
}

int Connection::getNodeB() const {
    return nodeB;
}

double Connection::getDistance() const {
    return distance;
}
