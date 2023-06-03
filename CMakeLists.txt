cmake_minimum_required(VERSION 3.24)
project(RoutingAnalysisDA)

set(CMAKE_CXX_STANDARD 17)

add_executable(RoutingAnalysisDA main.cpp src/data_structures/Graph.cpp src/builder/GraphBuilder.cpp src/parser/ParserData.cpp src/parser/NetworkParser.cpp src/model/Connection.cpp src/model/Node.cpp src/data_structures/VertexEdge.cpp src/ui/UserInterface.cpp src/heuristics/OtherHeuristics.cpp)
