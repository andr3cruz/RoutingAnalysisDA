#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <cfloat>
#include <algorithm>
#include <climits>
#include <execution>
#include <unordered_map>
#include <chrono>
#include <unordered_set>
#include <cmath>
#include <stack>
#include "VertexEdge.h"
#include "../model/Node.h"
#include "../model/Connection.h"
#include "MutablePriorityQueue.h"

/**
 * @brief Class that defines a Graph
 */

class Graph {
public:

    ~Graph();

    const unordered_map<int, Vertex *> & getVertexMap() const;

    /**
     * @brief Auxiliary function to find a vertex with a given ID
     * @details Time Complexity: O(1)
     * @param name
     * @returns The found vertex with the specified name
    */
    Vertex* findVertex(const int &id) const;

    /**
     * @brief Adds a vertex with a given content or info (in) to a graph (this).
     * @details Time Complexity: O(1)
     * @param station
     * @returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(const Node &node);

    /**
     * @brief Adds a bidirectional edge to a graph (this), given the contents of the source and destination vertices and the edge weight (w)
     * @details Time Complexity: O(1)
     * @param dest
     * @param sourc
     * @param w
     * @returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addBidirectionalEdge(const Node &sourc, const Node &dest, const Connection& w) const;

    /**
    * @brief Deletes Matrixes
    * @param m
    * @param n
    */
    static void deleteMatrix(double **m, int n);

    /**
    * @brief Edmonds-Karp algorithm adapted to this graph
    * @details Time Complexity: O(V*E^2) being V the number of vertexes and E the number of edges
    * @param s
    * @param t
    * @returns the maximum flow from vertex s to t
    */
    double edmondsKarp(Vertex* s, Vertex* t);

    /**
     * @brief Does the initial call to the Backtracking algorithm for solving the Traveling Salesman Problem and
     *        prints the optimal path and cost
     */
    void tspBacktrack();

    /**
     * @brief Prim's algorithm to find the Minimum Spanning Tree of a graph
     * @details Time Complexity:  O((V + E) log V), or O(V^2 log V) if using one of our denser graphs. V is the number of Vertexes and E the number of Edges in the graph
     * @return a graph that represents the said MST
     */
    Graph findMST();

    /**
     * @brief Find's the Vertexes with an odd degree in an MST
     * @details Time Complexity: O(V) being V the number of vertexes in the given MST
     * @param mst
     * @return an unordered map with said Vertexes. The keys are their Ids and the values the vertexes themselves
     */
    unordered_map<int, Vertex *> findOdds(unordered_map<int, Vertex *> mst);

    /**
     * @brief Finds a minimum cost perfect matching for the odd degree Vetexes selected in "findOdds" and adds the resulting edges to the original MST
     * @details Time Complexity: O(E log V + V^2) being V the number of Vertexes and E the number of Edges
     * @return a graph representing the final result of modifying the MST
     */
    Graph perfectMatching();

    /**
     * @brief the distance between two vertexes based on their GPS coordinates
     * @details Time Complexity: O(1)
     * @param v1
     * @param v2
     * @return the said distance
     */
    double calculateDistance(Vertex* v1, Vertex* v2);


    /**
     * @brief Resets every Vertexe's visitedEdges list
     * @details Time Complexity: O(V) being V the number of Vertexes
     */
    void resetEdges();

    /**
     * @brief Resets every Vertexe's visited state (Sets to false)
     * @details Time Complexity: O(V) being V the number of Vertexes
     */
    void resetVisits();

    /**
     * @brief Dijkstra's algorithm for finding shortest paths and corresponding distances
     * @details Time Complexity: O (V^2) being V the number of Vertexes
     * @param origin
     */
    void dijkstra(const int &origin);

    /**
     * @brief Analyzes an edge in single source shortest path algorithm.
     * @details Time Complexity: O(1)
     * @param edge
     * @return true if the target vertex was relaxed (dist, path), false otherwise
     */
    bool relax(Edge *edge);

protected:

    /// Vertex Map
    std::unordered_map<int, Vertex *> vertexMap;

    /// Dist matrix for Floyd-Warshall
    double ** distMatrix = nullptr;

    /// Path matrix for Floyd-Warshall
    double **pathMatrix = nullptr;

    /**
     * @brief Adapted Ford-Fulkerson algorithm for the graph in question
     * @details Time Complexity: O((V+E)*n), being V the number of vertexes, E the number of edges and n the number of vertexes along a path
     * @param source
     * @param target
     * @returns the maximum flow
     */
    int fordFulkerson(Vertex *source, Vertex *target) const;

    /**
     * @brief Adapted bfs algorithm for the graph in question
     * @details Time Complexity: O(V+E), being V the number of vertexes and E the number of edges
     * @param source
     * @param sink
     * @returns false if there is no path from source to sink and true otherwise
     */
    bool bfs(Vertex *source, Vertex *sink) const;


    /**
     * @brief Calculates the bottleneck capacity of a determined augmenting path
     * @details Time Complexity: O(n), being n the number of vertexes along a path
     * @param sink
     * @returns The value of the bottleneck capacity of the current path
     */
    static int getBottleneckCapacity(Vertex* sink);

    /**
     * @brief Follows the path from sink to source and updates the flow along each edge
     * @details Time Complexity: O(n), being n the number of  vertexes along a path
     * @param sink
     * @param bottleneck
     */
    static void updateFlow(Vertex* sink, int bottleneck);

    /**
     * @brief Finds the minimum residual capacity along a path
     * @details Time Complexity: O(n), being n the number of edges along the path between t and s
     * @param s
     * @param t
     * @returns the minimum residual capacity along a path from s to t
     */
    static double findMinResidualAlongPath(Vertex *s, Vertex *t);

    /**
     * @brief Finds an augmenting path
     * @details Time Complexity: O(V+E), being V the number of Vertexes and E the number of Edges
     * @param s
     * @param t
     * @returns true if an augmenting path was found and false otherwise
     */
    bool findAugmentingPath(Vertex *s, Vertex *t);

    /**
     * @brief Visits and tests vertices
     * @details Time Complexity: O(1)
     * @param q
     * @param e
     * @param w
     * @param residual
     */
    static void testAndVisit(queue<Vertex *> &q, Edge *e, Vertex *w, double residual);

    /**
     * @brief Finds paths with non-zero flow and updates the flow along those paths
     * @details Time Complexity: O(n), being n the number of edges along the path between t and s
     * @param s
     * @param t
     * @param f
     */
    static void augmentFlowAlongPath(Vertex *s, Vertex *t, double f);

    /**
     * @brief Backtracking algorithm for solving the Traveling Salesman Problem.
     * @details Time Complexity: O((V-1)!) where V is the number of vertices
     * @param currentVertex
     * @param currentCost
     * @param currentPath
     * @param visitedVertices
     * @param optimalCost
     * @param optimalPath
     * @param visitedCount
     * @param desiredPathSize
     * @param startVertex
     */
    void backtrack(Vertex* currentVertex, double currentCost, std::vector<Vertex*>& currentPath,
                   std::vector<bool>& visitedVertices, double& optimalCost, std::vector<Vertex*>& optimalPath,
                   int visitedCount, int desiredPathSize, Vertex* startVertex);

};

#endif /* DA_TP_CLASSES_GRAPH */