#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <iostream>
#include "../parser/ParserData.h"
#include "../heuristics/TriangularApproximation.h"

using namespace std;

/**
 * @brief Class for the User Interface
 */

class UserInterface {
public:
    /// Main menu
    static void mainMenu();
    static void otherHeuristicsMenu();
};

#endif //USERINTERFACE_H
