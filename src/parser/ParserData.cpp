#include "ParserData.h"

ParserData::ParserData(){
    edges = parser.parseConnections("../data/testEdges.csv"); //TODO: change path
    nodes = parser.parseNodes("../data/testNodes.csv"); // TODO: change path
    graph = GraphBuilder::buildGraph(nodes, edges);
}

vector<Connection> ParserData::getEdges() {
    return edges;
}

set<Node> ParserData::getNodes() {
    return nodes;
}

Graph* ParserData::getGraph() {
    return &graph;
}

void ParserData::rebuildGraph() {
    graph = GraphBuilder::buildGraph(nodes, edges);
}

Graph ParserData::getEmptyGraph() {
    return emptyGraph;
}

bool ParserData::searchNodeId(const int &id) {
    for (const auto& node : nodes) {
        if (node.getId() == id) return true;
    }
    return false;
}
