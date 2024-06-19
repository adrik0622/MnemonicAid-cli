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

    std::cout << "Welcome!" << std::endl;

    // Read user input
    std::string userInput;
    std::cout << "Please enter some input: ";
    std::getline(std::cin, userInput);

    // Perform some action with user input (for now we just output it)
    std::cout << "You entered: " << userInput << std::endl;

    // Define the exit status (0 for success, other values for failure)
    int exitStatus = 0; // Assuming successful execution for this example

    // Append exit status to a log file
    std::ofstream logFile("exit_log.txt", std::ios::app);
    if (logFile.is_open()) {
        logFile << "Exit status: " << exitStatus << std::endl;
        logFile.close();
    } else {
        std::cerr << "Unable to open log file." << std::endl;
        exitStatus = 1; // Update exit status to indicate an error
    }

    return exitStatus;
}

