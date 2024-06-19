#include "CardGame.h"
#include <iostream>
#include <cstdlib> // For system() function

// Function to clear the terminal
void clearTerminal() {
    // System-specific command to clear the terminal screen
    #if defined(_WIN32) || defined(_WIN64)
        system("cls"); // Windows
    #else
        system("clear"); // Unix/Linux/MacOS
    #endif
}

void CardGame::displayMenu() {
    bool exitFlag = false;
    while (!exitFlag) {
        clearTerminal();
        std::cout << "Card Game" << std::endl;
        std::cout << "1. Return to main menu" << std::endl;
        std::cout << "2. Exit" << std::endl;
        std::cout << "Please enter your choice: ";
        
        std::string userInput;
        std::getline(std::cin, userInput);
        
        if (userInput == "1") {
            exitFlag = true;
        } else if (userInput == "2") {
            // Define the exit status (0 for success, other values for failure)
            int exitStatus = 0; // Assuming successful execution for this example

            // Append exit status to a log file in the logs directory
            std::ofstream logFile("../logs/exit_log.txt", std::ios::app);
            if (logFile.is_open()) {
                logFile << "Exit status: " << exitStatus << std::endl;
                logFile.close();
            } else {
                std::cerr << "Unable to open log file." << std::endl;
                exitStatus = 1; // Update exit status to indicate an error
            }
            exit(exitStatus);
        } else {
            std::cout << "Command not recognized! Please try again." << std::endl;
        }
    }
}
