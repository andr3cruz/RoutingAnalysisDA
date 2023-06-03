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
};

#endif //USERINTERFACE_H
