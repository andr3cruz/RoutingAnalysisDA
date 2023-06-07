#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
#include "UserInterface.h"

void UserInterface::mainMenu() {
    int choice;

    cout << "Welcome to Routing Analysis\n";
    cout << "Current Data Set: " << parserData.getDataSet() << endl;
    cout << "1. Backtracking Algorithm\n";
    cout << "2. Triangular Approximation Heuristic\n";
    cout << "3. Other Heuristics\n";
    cout << "4. Choose Data Set\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            parserData.getGraph()->tspBacktrack();
            break;
        case 2:
            triangularApproximationMenu();
            break;
        case 3:
            otherHeuristicsMenu();
            break;
        case 4:
            chooseDataSetMenu();
            break;
        case 5:
            return;
        default:
            cout << "Invalid choice\n";
            mainMenu();
            break;
    }
    mainMenu();
}

void UserInterface::otherHeuristicsMenu() {

    list<Vertex*> path;
    double cost;

    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    auto pair = OtherHeuristics::christofides();
    path = pair.first;
    cost = pair.second;
    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();

    // Calculate the duration in milliseconds
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    cout << endl;
    cout << "Path: ";
    for (Vertex* vertex : path){
        cout << " -> " << vertex->getNode()->getId();
    }

    cout << "\n\n" << "Total Cost: " << cost;
    cout << "\n";
    cout << "Execution time: " << duration << " ms" << std::endl;

}

void UserInterface::triangularApproximationMenu(){
    vector<Vertex*> path;
    double cost;

    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    auto pair = TriangularApproximation::triangularApprox();
    path = pair.first;
    cost = pair.second;

    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();

    // Calculate the duration in milliseconds
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    cout << "Path: ";
    for (Vertex* vertex : path){
        cout << " -> " << vertex->getNode()->getId();
    }

    cout << "\n\n" << "Total Cost: " << cost;
    cout << "\n";
    cout << "Execution time: " << duration << " ms" << "\n";
}

void UserInterface::chooseDataSetMenu() {
    int choice;

    cout << "Pick a Data Set\n";
    cout << "1. Toy Graphs\n";
    cout << "2. Medium Sized Graphs\n";
    cout << "3. Real World Graphs\n";
    cout << "4. Custom Graphs\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            toyGraphsMenu();
            break;
        case 2:
            mediumSizedGraphsMenu();
            break;
        case 3:
            realWorldGraphsMenu();
            break;
        case 4:
            customGraphsMenu();
            break;
        case 5:
            return;
        default:
            cout << "Invalid choice\n";
            chooseDataSetMenu();
            break;
    }
}

void UserInterface::toyGraphsMenu() {
    int choice;
    cout << "Pick a Toy Graph Data Set\n";
    cout << "1. Shipping\n";
    cout << "2. Stadiums\n";
    cout << "3. Tourism\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            parserData.rebuildGraph("ToyGraphs/shipping.csv", "Toy Graph Shipping");
            break;
        case 2:
            parserData.rebuildGraph("ToyGraphs/stadiums.csv", "Toy Graph Stadiums");
            break;
        case 3:
            parserData.rebuildGraph("ToyGraphs/tourism.csv", "Toy Graph Tourism");
            break;
        case 4:
            chooseDataSetMenu();
            break;
        default:
            cout << "Invalid choice\n";
            toyGraphsMenu();
            break;
    }
    mainMenu();
}

void UserInterface::mediumSizedGraphsMenu() {
    int choice;
    cout << "Pick a Medium Size Data Set\n";
    cout << "1. edges25\n";
    cout << "2. edges50\n";
    cout << "3. edges75\n";
    cout << "4. edges100\n";
    cout << "5. edges200\n";
    cout << "6. edges300\n";
    cout << "7. edges400\n";
    cout << "8. edges500\n";
    cout << "9. edges600\n";
    cout << "10. edges700\n";
    cout << "11. edges800\n";
    cout << "12. edges900\n";
    cout << "13. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice) {
        case 1:
            parserData.rebuildGraph("MediumSizedGraphs/edges_25.csv", "Medium Sized Graph Edges 25");
            break;
        case 2:
            parserData.rebuildGraph("MediumSizedGraphs/edges_50.csv", "Medium Sized Graph Edges 50");
            break;
        case 3:
            parserData.rebuildGraph("MediumSizedGraphs/edges_75.csv", "Medium Sized Graph Edges 75");
            break;
        case 4:
            parserData.rebuildGraph("MediumSizedGraphs/edges_100.csv", "Medium Sized Graph Edges 100");
            break;
        case 5:
            parserData.rebuildGraph("MediumSizedGraphs/edges_200.csv", "Medium Sized Graph Edges 200");
            break;
        case 6:
            parserData.rebuildGraph("MediumSizedGraphs/edges_300.csv", "Medium Sized Graph Edges 300");
            break;
        case 7:
            parserData.rebuildGraph("MediumSizedGraphs/edges_400.csv", "Medium Sized Graph Edges 400");
            break;
        case 8:
            parserData.rebuildGraph("MediumSizedGraphs/edges_500.csv", "Medium Sized Graph Edges 500");
            break;
        case 9:
            parserData.rebuildGraph("MediumSizedGraphs/edges_600.csv", "Medium Sized Graph Edges 600");
            break;
        case 10:
            parserData.rebuildGraph("MediumSizedGraphs/edges_700.csv", "Medium Sized Graph Edges 700");
            break;
        case 111:
            parserData.rebuildGraph("MediumSizedGraphs/edges_800.csv", "Medium Sized Graph Edges 800");
            break;
        case 12:
            parserData.rebuildGraph("MediumSizedGraphs/edges_900.csv", "Medium Sized Graph Edges 900");
            break;
        case 13:
            chooseDataSetMenu();
            break;
        default:
            cout << "Invalid choice\n";
            mediumSizedGraphsMenu();
            break;
    }
    mainMenu();
}

void UserInterface::realWorldGraphsMenu() {
    int choice;
    cout << "Pick a Real World Data Set\n";
    cout << "1. graph1\n";
    cout << "2. graph2\n";
    cout << "3. graph3\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            parserData.rebuildGraph("RealWorldGraphs/graph1/nodes.csv", "RealWorldGraphs/graph1/edges.csv", "Real World Graph 1");
            break;
        case 2:
            parserData.rebuildGraph("RealWorldGraphs/graph2/nodes.csv", "RealWorldGraphs/graph2/edges.csv", "Real World Graph 2");
            break;
        case 3:
            parserData.rebuildGraph("RealWorldGraphs/graph3/nodes.csv", "RealWorldGraphs/graph3/edges.csv", "Real World Graph 3");
            break;
        case 4:
            chooseDataSetMenu();
            break;
        default:
            cout << "Invalid choice\n";
            realWorldGraphsMenu();
            break;
    }
    mainMenu();
}

void UserInterface::customGraphsMenu() {
    int choice;
    string nodesFile;
    string edgesFile;
    string nodesFilePath;
    string edgesFilePath;

    cout << "Type the Edges file name\n";
    cin >> edgesFile;
    edgesFilePath = "OtherGraphs/" + edgesFile + ".csv";

    cout << "Is there a Nodes file?\n";
    cout << "1. Yes\n";
    cout << "2. No\n";
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "Type the Nodes file name\n";
            cin >> nodesFile;
            nodesFilePath = "OtherGraphs/" + nodesFile + ".csv";
            parserData.rebuildGraph(nodesFilePath, edgesFilePath, "Custom Graph");
            break;
        case 2:
            parserData.rebuildGraph(edgesFilePath, "Custom Graph");
            break;
        default:
            cout << "Invalid choice\n";
            customGraphsMenu();
            break;
    }
    mainMenu();
}


#pragma clang diagnostic pop