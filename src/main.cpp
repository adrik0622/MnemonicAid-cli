#include <iostream>
#include <fstream>
#include <string>
#include "CardGame.h"
#include "NumbersGame.h"
#include "WordsGame.h"
#include "Utils.h"

int main() {
    std::string userInput;
    bool exitFlag = false;

    while (!exitFlag) {
        clearTerminal();
        std::cout << "Welcome to the mnemonic aid! How would you like to proceed?" << std::endl;
        std::cout << "1. Exit" << std::endl;
        std::cout << "2. Card Game" << std::endl;
        std::cout << "3. Numbers Game" << std::endl;
        std::cout << "4. Words Game" << std::endl;
        std::cout << "Please enter your choice: ";
        std::getline(std::cin, userInput);

        if (userInput == "exit" || userInput == "Exit" || userInput == "1") {
            exitFlag = true;
        } else if (userInput == "2") {
            CardGame cardGame;
            cardGame.displayMenu();
        } else if (userInput == "3") {
            NumbersGame numbersGame;
            numbersGame.displayMenu();
        } else if (userInput == "4") {
            WordsGame wordsGame;
            wordsGame.displayMenu();
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

