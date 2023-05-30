#include "VertexEdge.h"

/************************* Vertex  **************************/

Vertex::Vertex(Node node): id(node.getId()), node(node) {}


Edge * Vertex::addEdge(Vertex *d, double w) {
    auto newEdge = new Edge(this, d, w);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
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

Node* Vertex::getNode() {
    return &this->node;
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

