#include "GraphBuilder.h"

Graph GraphBuilder::buildGraph(const set<Node>& nodes, const vector<Connection>& connections) {
    Graph networkGraph;

    buildNodes(nodes, networkGraph);
    buildEdges(nodes, connections, networkGraph);

    return networkGraph;
}

void GraphBuilder::buildNodes(const set<Node>& nodes, Graph& graph) {
    for (const auto& node : nodes) {
        bool result;
        result = graph.addVertex(node);
        if(!result) {
            cout << "WARNING operation='buildGraph', msg='Vertex already exists', station=" << node.getId() << endl;
        }
    }
}

void GraphBuilder::buildEdges(const set<Node>& nodes, const vector<Connection>& connections, Graph& graph) {
    // Build mapping of node IDs to nodes
    unordered_map<int, Node> nodeMap;
    for (const auto &node: nodes) {
        nodeMap[node.getId()] = node;
    }

    // Iterate over connections using the node mapping
    for (const auto &connection: connections) {
        auto itA = nodeMap.find(connection.getNodeA());
        auto itB = nodeMap.find(connection.getNodeB());

        if (itA != nodeMap.end() && itB != nodeMap.end()) {
            Node &sourceNode = itA->second;
            Node &destNode = itB->second;

            bool result = graph.addBidirectionalEdge(sourceNode, destNode, connection);
            if (!result) {
                cout << "WARNING operation='buildGraph', msg='Edge already exists', sourceStation="
                     << to_string(sourceNode.getId()) << ", " << "destStation=" << to_string(destNode.getId()) << endl;
            }
        }
    }
}