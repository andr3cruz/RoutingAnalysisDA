#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <iostream>
#include "../parser/ParserData.h"
#include "../heuristics/OtherHeuristics.h"
#include "../heuristics/TriagularApproximation.h"


using namespace std;

/**
 * @brief Class for the User Interface
 */

class UserInterface {
public:
    /// Main menu
    static void mainMenu();

    /// Other Heuristics menu
    static void otherHeuristicsMenu();

    /// Triangular Approximation menu
    static void triangularApproximationMenu();

    /// Choose Data Set menu
    static void chooseDataSetMenu();

    /// Toy Graphs Pick menu
    static void toyGraphsMenu();

    /// Medium Sized Graphs Pick menu
    static void mediumSizedGraphsMenu();

    /// Real World Graphs Pick menu
    static void realWorldGraphsMenu();

    /// Custom Graphs Pick menu
    static void customGraphsMenu();
};

#endif //USERINTERFACE_H
