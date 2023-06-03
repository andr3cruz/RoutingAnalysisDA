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
    cin >> choice;

    switch (choice) {
        case 1:
            parserData.getGraph()->tspBacktrack();
            break;
        case 2:
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
    vector<Vertex*> path;
    path = OtherHeuristics::christofides();
    cout << "Path:";
    for (Vertex* vertex : path){
        cout << vertex->getNode()->getId() << " ";
    }
}



#pragma clang diagnostic pop