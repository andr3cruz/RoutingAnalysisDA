
#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-transparent-functors"
#pragma ide diagnostic ignored "misc-no-recursion"

#include "Graph.h"


Vertex * Graph::findVertex(const int &id) const {
    auto iter = vertexMap.find(id);
    if (iter != vertexMap.end()) {
        return iter->second;
    } else {
        return nullptr;
    }
}

bool Graph::addVertex(const Node &node) {
    if (findVertex(node.getId()) != nullptr)
        return false;
    vertexMap.insert({node.getId(), new Vertex(node)});
    return true;
}

bool Graph::addBidirectionalEdge(const Node &sourc, const Node &dest, const Connection& w) const {
    auto v1 = findVertex(sourc.getId());
    auto v2 = findVertex(dest.getId());
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w.getDistance());
    auto e2 = v2->addEdge(v1, w.getDistance());
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

void Graph::deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

double Graph::edmondsKarp(Vertex* s, Vertex* t) {
    if (s == nullptr || t == nullptr ||  s == t)
        throw std::logic_error("Invalid source and/or target vertex");

    for (const auto& v : vertexMap) {
        for (auto e: v.second->getAdj()) {
            e->setFlow(0);
        }
    }

    double maxFlow = 0;
    while(findAugmentingPath(s, t)) {
        double f = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, f);
        maxFlow += f;
    }

    return maxFlow;
}

void Graph::testAndVisit(std::queue< Vertex*> &q, Edge *e, Vertex *w, double residual) {
    if (! w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

bool Graph::findAugmentingPath(Vertex *s, Vertex *t) {
    for(auto v : vertexMap) {
        v.second->setVisited(false);
    }
    s->setVisited(true);
    std::queue<Vertex *> q;
    q.push(s);
    while( ! q.empty() && ! t->isVisited()) {
        auto v = q.front();
        q.pop();
        for(auto e: v->getAdj()) {
            testAndVisit(q, e, e->getDest(), e->getWeight() - e->getFlow());
        }
        for(auto e: v->getIncoming()) {
            testAndVisit(q, e, e->getOrig(), e->getFlow());
        }
    }
    return t->isVisited();
}

double Graph::findMinResidualAlongPath(Vertex *s, Vertex *t) {
    double f = INF;
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = std::min(f, e->getWeight() - e->getFlow());
            v = e->getOrig();
        }
        else {
            f = std::min(f, e->getFlow());
            v = e->getDest();
        }
    }
    return f;
}

void Graph::augmentFlowAlongPath(Vertex *s, Vertex *t, double f) {
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow + f);
            v = e->getOrig();
        }
        else {
            e->setFlow(flow - f);
            v = e->getDest();
        }
    }
}

int Graph::fordFulkerson(Vertex *source, Vertex *target) const {
    int maxFlow = 0;

    while (bfs(source, target)) {
        int bottleneck = getBottleneckCapacity(target);

        updateFlow(target, bottleneck);

        maxFlow += bottleneck;
    }
    return maxFlow;

}

bool Graph::bfs(Vertex *source, Vertex* sink) const {
    for (auto& vertex : vertexMap) {
        Vertex* v = vertex.second;
        v->setVisited(false);
        v->setPath(nullptr);
    }

    std::queue<Vertex*> queue;

    source->setVisited(true);
    queue.push(source);

    while (!queue.empty()) {
        Vertex* v = queue.front();
        queue.pop();

        for (Edge* e : v->getAdj()) {
            Vertex* w = e->getDest();
            if (!w->isVisited() && e->getWeight() > 0) {
                w->setVisited(true);
                w->setPath(e);
                if (w == sink) {
                    return true;
                }
                queue.push(w);
            }
        }

    }

    return false;
}

int Graph::getBottleneckCapacity(Vertex* sink) {
    double bottleneck = DBL_MAX;

    for (Vertex* v = sink; v->getPath() != nullptr; v = v->getPath()->getOrig()) {
        Edge* e = v->getPath();
        bottleneck = min(bottleneck, e->getWeight());
    }

    return bottleneck;
}

void Graph::updateFlow(Vertex* sink, int bottleneck) {
    for (Vertex *v = sink; v->getPath() != nullptr; v = v->getPath()->getOrig()) {
        Edge *e = v->getPath();
        e->setWeight(e->getWeight() - bottleneck);
        Edge *reverse = e->getReverse();
        if (reverse != nullptr) {
            reverse->setWeight(reverse->getWeight() + bottleneck);
        }
    }
}


Graph::~Graph() {
    deleteMatrix(distMatrix, (int) vertexMap.size());
    deleteMatrix(pathMatrix, (int) vertexMap.size());
}

const unordered_map<int, Vertex *> & Graph::getVertexMap() const {
    return this->vertexMap;
}

#pragma clang diagnostic pop