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
    static void otherHeuristicsMenu();
    static void triangularApproximationMenu();
    static void chooseDataSetMenu();

    static void toyGraphsMenu();

    static void mediumSizedGraphsMenu();

    static void realWorldGraphsMenu();

    static void customGraphsMenu();
};

#endif //USERINTERFACE_H
