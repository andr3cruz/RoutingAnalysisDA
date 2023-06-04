#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-transparent-functors"
#pragma ide diagnostic ignored "misc-no-recursion"

#include "Graph.h"
#include "../parser/ParserData.h"
#include <utility>

Graph parderDataGraph = *ParserData().getGraph();


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

void Graph::backtrack(Vertex* currentVertex, double currentCost, std::vector<Vertex*>& currentPath,
                         std::vector<bool>& visitedVertices, double& optimalCost, std::vector<Vertex*>& optimalPath,
                         int visitedCount, int desiredPathSize, Vertex* startVertex) {
    currentPath.push_back(currentVertex);
    visitedVertices[currentVertex->getId()] = true;
    visitedCount++;

    // Base case: All desired vertices have been visited, and the current vertex is adjacent to the start vertex
    if (visitedCount == desiredPathSize && currentVertex->isAdjacentTo(startVertex)) {
        double newCost = currentCost + currentVertex->getEdgeTo(startVertex)->getWeight();
        // Check if the current path is better than the current optimal path
        if (newCost < optimalCost) {
            optimalCost = newCost;
            optimalPath = currentPath;
            optimalPath.push_back(startVertex);
        }
    } else {
        // Explore unvisited neighbors
        for (Edge* edge : currentVertex->getAdj()) {
            if (edge->getOrig() == currentVertex && !visitedVertices[edge->getDest()->getId()]) {
                Vertex* neighbor = edge->getDest();
                double newCost = currentCost + edge->getWeight();

                backtrack(neighbor, newCost, currentPath, visitedVertices, optimalCost, optimalPath,
                             visitedCount, desiredPathSize, startVertex);
            }
        }
    }

    // Backtrack: Remove the current vertex from the path and mark it as not visited
    currentPath.pop_back();
    visitedVertices[currentVertex->getId()] = false;
    visitedCount--;
}

void Graph::tspBacktrack() {
    double optimalCost = std::numeric_limits<double>::max();
    std::vector<Vertex*> optimalPath;
    int visitedCount = 0;  // Counter to keep track of the visited vertices

    Vertex* startVertex = vertexMap.find(0)->second;

    std::vector<Vertex*> currentPath;
    std::vector<bool> visitedVertices(vertexMap.size(), false);

    // Calculate the desired path size based on the edges
    int desiredPathSize = 0;
    for (const auto& entry : vertexMap) {
        Vertex* vertex = entry.second;
        if (!vertex->getAdj().empty()) {
            desiredPathSize++;
        }
    }

    // Start measuring the execution time
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    backtrack(startVertex, 0, currentPath, visitedVertices, optimalCost, optimalPath, visitedCount,
                 desiredPathSize, startVertex);

    // Stop measuring the execution time
    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();

    // Calculate the duration in milliseconds
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    std::cout << "Optimal Path: ";
    for (int i = optimalPath.size() - 1; i >= 0; i--) {
        std::cout << optimalPath[i]->getId() << " ";
    }
    std::cout << endl;
    std::cout << "Optimal Cost: " << optimalCost << std::endl;
    std::cout << "Execution time: " << duration << " ms" << std::endl;
}


Graph Graph::findMST() {

    Graph mstGraph;

    if (vertexMap.empty()) {
        return mstGraph;
    }
    // Reset auxiliary info
    for(auto v : vertexMap) {
        v.second->setDist(INF);
        v.second->setPath(nullptr);
        v.second->setVisited(false);
    }

    // start with an arbitrary vertex
    Vertex* s = vertexMap[1];
    s->setDist(0);

    // initialize priority queue
    MutablePriorityQueue<Vertex> q;
    q.insert(s);
    // process vertices in the priority queue
    while( ! q.empty() ) {
        auto v = q.extractMin();
        v->setVisited(true);
        for(auto &e : v->getAdj()) {
            Vertex* w = e->getDest();
            if (!w->isVisited()) {
                auto oldDist = w->getDist();
                if(e->getWeight() < oldDist) {
                    w->setDist(e->getWeight());
                    w->setPath(e);
                    if (oldDist == INF) {
                        q.insert(w);
                    }
                    else {
                        q.decreaseKey(w);
                    }
                }
            }
        }
    }

    for (auto& entry : vertexMap) {
        Vertex* v = entry.second;
        mstGraph.addVertex(*v->getNode());
    }

    for (auto& entry : vertexMap) {
        Vertex* v = entry.second;
        if (v->getPath() != nullptr) {
            Vertex* destVertex = v->getPath()->getOrig();
            double weight = v->getPath()->getWeight();
            mstGraph.addBidirectionalEdge(*v->getNode(), *destVertex->getNode(), Connection(v->getId(), destVertex->getId(), weight));
        }
    }

    return mstGraph;
}

unordered_map<int, Vertex *> Graph::findOdds(unordered_map<int, Vertex *> mst){
    unordered_map<int, Vertex *> odds;
    for (auto v : mst){
        if ((v.second->getAdj().size() % 2) != 0){
            odds[v.first] = v.second;
        }
    }
    return odds;
}

double Graph::calculateDistance(Vertex* v1, Vertex* v2){

    Node n1 = *v1->getNode();
    Node n2 = *v2->getNode();

    double lat1 = n1.getLatitude(), lon1 = n1.getLongitude(), lat2 = n2.getLatitude(), lon2 = n2.getLongitude();

    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLong = (lon2 - lon1) * M_PI / 180.0;

    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) + pow(sin(dLong / 2), 2) * cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));

    return rad * c;

}

Graph Graph::perfectMatching() {

    double length;
    int closest;
    std::unordered_map<int, Vertex*>::iterator tmp, first;
    // Get the minimum spanning tree
    Graph mst = findMST();

    // Get the vertices with odd degrees from the minimum spanning tree
    std::unordered_map<int, Vertex*> odds = findOdds(mst.vertexMap);

    while (!odds.empty()) {
        first = odds.begin();
        auto it = next(odds.begin(), 1);
        auto end = odds.end();
        length = std::numeric_limits<double>::max();

        for (; it != end; ++it) {
            auto vertexId1 = first->second->getId();
            auto vertexId2 = it->second->getId();

            Vertex* vertex1 = parderDataGraph.findVertex(vertexId1);
            Vertex* vertex2 = parderDataGraph.findVertex(vertexId2);

            auto edge = vertex1->getEdgeTo(vertex2);

            double tempDistance;

            if (edge == nullptr){
                tempDistance = calculateDistance(first->second, it->second);
            } else {
                tempDistance = edge->getWeight();
            }
            // If this node is closer than the current closest, update closest and length
            if (tempDistance < length) {
                length = tempDistance;
                closest = it->first;
                tmp = it;
            }
        }


        mst.vertexMap[first->first]->addEdge(mst.vertexMap[closest], length);
        mst.vertexMap[closest]->addEdge(mst.vertexMap[first->first], length);

        // Add edges between the two closest vertices
        //first->second->addEdge(odds[closest], length);
        //odds[closest]->addEdge(first->second, length);

        // Remove the matched vertices from the odds map

        odds.erase(tmp);
        odds.erase(first);
    }

    return mst;
}

void Graph::resetEdges() {
    for (auto vertex: vertexMap){
        if (!vertex.second->getVisited()->empty()) {
            vertex.second->getVisited()->clear();
        }
        vertex.second->loadVisited();
    }
}

void Graph::resetVisits(){
    for (auto vertex: vertexMap){
        vertex.second->setVisited(false);
    }
}

#pragma clang diagnostic pop