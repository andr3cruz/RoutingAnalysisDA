#include "Node.h"

Node::Node(const int &id, const double &longitude, const double &latitude) : id(id), longitude(longitude),
                                                                         latitude(latitude) {}

Node::Node() {}

const int Node::getId() const {
    return id;
}

const double Node::getLongitude() const {
    return longitude;
}

const double Node::getLatitude() const {
    return latitude;
}
