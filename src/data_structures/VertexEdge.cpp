#include "VertexEdge.h"

/************************* Vertex  **************************/

Vertex::Vertex(Node node): id(node.getId()), node(node) {}


Edge * Vertex::addEdge(Vertex *d, double w) {
    auto newEdge = new Edge(this, d, w);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

bool Vertex::removeEdge(int destID) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->getId() == destID) {
            it = adj.erase(it);
            deleteEdge(edge);
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedEdge;
}

void Vertex::deleteEdge(Edge *edge) {
    Vertex *dest = edge->getDest();
    // Remove the corresponding edge from the incoming list
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        if ((*it)->getOrig()->getId() == id) {
            it = dest->incoming.erase(it);
        }
        else {
            it++;
        }
    }
    delete edge;
}

bool Vertex::operator<(Vertex & vertex) const {
    return this->dist < vertex.dist;
}

int Vertex::getId() const {
    return this->id;
}

vector<Edge *> Vertex::getAdj() const {
    return this->adj;
}

bool Vertex::isVisited() const {
    return this->visited;
}

Edge *Vertex::getPath() const {
    return this->path;
}

std::vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}


void Vertex::setPath(Edge *path) {
    this->path = path;
}

bool Vertex::isAdjacentTo(Vertex* otherVertex) const {
    for (Edge* edge : adj) {
        if (edge->getOrig() == this && edge->getDest() == otherVertex) {
            return true;
        }
    }
    return false;
}

Edge* Vertex::getEdgeTo(Vertex* otherVertex) const {
    for (Edge* edge : adj) {
        if (edge->getOrig() == this && edge->getDest() == otherVertex) {
            return edge;
        }
    }
    return nullptr;  // If no edge is found between the vertices
}

Edge* Vertex::getEdgeToVisited(Vertex* otherVertex) {
    for (Edge* edge : visitedEdges) {
        if (edge->getOrig() == this && edge->getDest() == otherVertex) {
            return edge;
        }
    }
    return nullptr;  // If no edge is found between the vertices
}

Node* Vertex::getNode() {
    return &this->node;
}

bool Vertex::isAllTraversed(){
    for (Edge* edge: adj){
        if (!edge->getTraversed()){
            return false;
        }
    }
    return true;
}


/********************** Edge  ****************************/

Edge::Edge(Vertex *orig, Vertex *dest, double w): orig(orig), dest(dest), weight(w) {}

Vertex * Edge::getDest() const {
    return this->dest;
}

double Edge::getWeight() const {
    return this->weight;
}

Vertex * Edge::getOrig() const {
    return this->orig;
}

Edge *Edge::getReverse() const {
    return this->reverse;
}

double Edge::getFlow() const {
    return flow;
}

double Vertex::getDist() const {
    return this->dist;
}

void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}

void Edge::setFlow(double flow) {
    this->flow = flow;
}

void Edge::setWeight(double weight) {
    this->weight = weight;
}

void Vertex::setDist(double dist) {
    this->dist = dist;
}

list<Edge *>* Vertex::getVisited() {
    return &visitedEdges;
}

void Vertex::loadVisited() {
    for (auto edge: adj) {
        visitedEdges.push_back(edge);
    }
}

void Edge::setTraversed(bool traversed) {
    this->traversed=traversed;
}

bool Edge::getTraversed() const {
    return this->traversed;
}
