#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
#include "UserInterface.h"

void UserInterface::mainMenu() {
    int choice;

    cout << "Welcome to Routing Analysis\n";
    cout << "1. Backtracking Algorithm\n";
    cout << "2. Triangular Approximation Heuristic\n";
    cout << "3. Other Heuristics\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
    //cin >> choice;
    choice = 2;

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
            return;
        default:
            cout << "Invalid choice\n";
            mainMenu();
            break;
    }
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

    cout << "\n" << "Total Cost: " << cost;
    cout << "\n\n";
    cout << "Execution time: " << duration << " ms" << std::endl;

}

void UserInterface::triangularApproximationMenu(){
    vector<Vertex*> path;

    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    path = TriangularApproximation::triangularApprox();

    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();

    // Calculate the duration in milliseconds
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    cout << "Path: ";
    for (Vertex* vertex : path){
        cout << " -> " << vertex->getNode()->getId();
    }

    cout << "\n\n";
    cout << "Execution time: " << duration << " ms" << "\n";
}



#pragma clang diagnostic pop