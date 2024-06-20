#include "Utils.h"
#include <cstdlib> // For system() function

void clearTerminal() {
    // System-specific command to clear the terminal screen
    #if defined(_WIN32) || defined(_WIN64)
        system("cls"); // Windows
    #else
        system("clear"); // Unix/Linux/MacOS
    #endif
}

