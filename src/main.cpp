#include <iostream>
#include <fstream>
#include <cstdlib> // For system() function
#include <string>

// Function to clear the terminal
void clearTerminal() {
    // System-specific command to clear the terminal screen
    #if defined(_WIN32) || defined(_WIN64)
        system("cls"); // Windows
    #else
        system("clear"); // Unix/Linux/MacOS
    #endif
}

int main() {
    clearTerminal();

    std::string userInput;
    bool exitFlag = false;

    while (!exitFlag) {
        std::cout << "Welcome to the mnemonic aid! How would you like to proceed?" << std::endl;
        std::cout << "1. Exit" << std::endl;
        std::cout << "Please enter your choice: ";
        std::getline(std::cin, userInput);

        if (userInput == "exit" || userInput == "Exit") {
            exitFlag = true;
        } else {
            std::cout << "Command not recognized! Please try again." << std::endl;
        }
    }

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

    return exitStatus;
}
