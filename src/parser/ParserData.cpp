#include "ParserData.h"

ParserData::ParserData(){
    edges = parser.parseConnections("../data/RealWorldGraphs/graph1/edges.csv");
    nodes = parser.parseNodes("../data/RealWorldGraphs/graph1/nodes.csv");
    graph = GraphBuilder::buildGraph(nodes, edges);
    dataSet = "Real World Graph 1";
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

void ParserData::rebuildGraph(const string& nodesPath, const string& edgesPath, const string& dataSetName) {
    edges = parser.parseConnections("../data/" + edgesPath);
    nodes = parser.parseNodes("../data/" + nodesPath);
    graph = GraphBuilder::buildGraph(nodes, edges);
    dataSet = dataSetName;
}

void ParserData::rebuildGraph(const string& edgesPath, const string& dataSetName) {
    edges = parser.parseConnections("../data/" + edgesPath);
    nodes = parser.parseDefaultNodes();
    graph = GraphBuilder::buildGraph(nodes, edges);
    dataSet = dataSetName;
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

const string &ParserData::getDataSet() const {
    return dataSet;
}

void ParserData::setDataSet(const string &newDataSet) {
    dataSet = newDataSet;
}
