#include "NumbersGame.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <thread>
#include <chrono>

// Constructor to initialize default values
NumbersGame::NumbersGame() : numChars(5), numRows(5), prepTime(10), memTime(300), recallTime(300) {}

std::vector<std::string> NumbersGame::generateNumbers() {
    std::vector<std::string> numbers;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 9);

    for (int i = 0; i < numRows; ++i) {
        std::string number;
        for (int j = 0; j < numChars; ++j) {
            number += std::to_string(dis(gen));
        }
        numbers.push_back(number);
    }

    return numbers;
}

void NumbersGame::prepPhase() {
    clearTerminal();
    std::cout << "Prep Phase" << std::endl;
    std::cout << "Prep time: " << prepTime << " seconds. Press Enter to skip." << std::endl;

    for (int i = prepTime; i > 0; --i) {
        std::cout << "\r" << i << " seconds remaining." << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (std::cin.peek() != EOF) {
            std::cin.ignore();
            break;
        }
    }

    clearTerminal();
}

void NumbersGame::memPhase(const std::vector<std::string>& generatedNumbers) {
    clearTerminal();
    std::cout << "Memorization Phase" << std::endl;
    std::cout << "You have " << memTime << " seconds to memorize the numbers." << std::endl;

    for (const auto& number : generatedNumbers) {
        std::cout << number << std::endl;
    }

    for (int i = memTime; i > 0; --i) {
        std::cout << "\r" << i << " seconds remaining." << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (std::cin.peek() != EOF) {
            std::cin.ignore();
            break;
        }
    }

    clearTerminal();
}

void NumbersGame::recallPhase(const std::vector<std::string>& generatedNumbers) {
    clearTerminal();
    std::cout << "RECALL:" << std::endl;
    std::cout << "Input the numbers you remember in a comma-delimited manner. Use '-' for unknowns." << std::endl;
    std::cout << "Example: 12345, 67890, -, 54321, 09876" << std::endl;

    std::cout << "Recall time: " << recallTime << " seconds." << std::endl;

    std::string userInput;
    auto start = std::chrono::steady_clock::now();
    while (true) {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = now - start;
        int remaining_time = recallTime - static_cast<int>(elapsed_seconds.count());

        if (remaining_time <= 0) {
            break;
        }

        std::cout << "\r" << remaining_time << " seconds remaining." << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));

        if (std::cin.peek() != EOF) {
            std::getline(std::cin, userInput);
            break;
        }
    }

    std::vector<std::string> userNumbers;
    std::string number;
    std::stringstream ss(userInput); // Initialize stringstream with userInput
    while (std::getline(ss, number, ',')) {
        // Remove leading and trailing whitespace
        number.erase(0, number.find_first_not_of(' '));
        number.erase(number.find_last_not_of(' ') + 1);
        userNumbers.push_back(number);
    }

    clearTerminal();
    reviewPhase(generatedNumbers, userNumbers);
}

void NumbersGame::reviewPhase(const std::vector<std::string>& generatedNumbers, const std::vector<std::string>& userInput) {
    std::cout << "Review Phase" << std::endl;

    std::ofstream logFile("../logs/exit_log.txt", std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Unable to open log file." << std::endl;
    }

    int correct = 0;
    for (size_t i = 0; i < generatedNumbers.size(); ++i) {
        std::string generatedNumber = generatedNumbers[i];
        std::string userNumber = (i < userInput.size()) ? userInput[i] : "No input";

        logFile << "Number " << (i + 1) << ": " << generatedNumber << ", User input: " << userNumber << std::endl;

        std::cout << "Number " << (i + 1) << ": " << generatedNumber;
        if (userNumber == generatedNumber) {
            std::cout << " (Correct)";
            correct++;
        } else {
            std::cout << " (Incorrect, you said: " << userNumber << ")";
        }
        std::cout << std::endl;
    }

    logFile << "Score: " << correct << " out of " << generatedNumbers.size() << std::endl;
    logFile.close();

    std::cout << "Score: " << correct << " out of " << generatedNumbers.size() << std::endl;
    std::cout << "Press Enter to return to the main menu.";
    std::cin.ignore();
    std::cin.get();
    clearTerminal();
}

void NumbersGame::startGame() {
    std::vector<std::string> generatedNumbers = generateNumbers();

    prepPhase();
    memPhase(generatedNumbers);
    recallPhase(generatedNumbers);
}

void NumbersGame::displayOptions() {
    bool backFlag = false;
    while (!backFlag) {
        clearTerminal();
        std::cout << "Options" << std::endl;
        std::cout << "1. Set number of characters (current: " << numChars << ")" << std::endl;
        std::cout << "2. Set number of rows (current: " << numRows << ")" << std::endl;
        std::cout << "3. Set prep time (current: " << prepTime << " seconds)" << std::endl;
        std::cout << "4. Set memorization time (current: " << memTime << " seconds)" << std::endl;
        std::cout << "5. Set recall time (current: " << recallTime << " seconds)" << std::endl;
        std::cout << "6. Return to numbers game menu" << std::endl;
        std::cout << "Please enter your choice: ";
        
        std::string userInput;
        std::getline(std::cin, userInput);
        
        if (userInput == "1") {
            std::cout << "Enter number of characters: ";
            std::getline(std::cin, userInput);
            numChars = std::stoi(userInput);
        } else if (userInput == "2") {
            std::cout << "Enter number of rows: ";
            std::getline(std::cin, userInput);
            numRows = std::stoi(userInput);
        } else if (userInput == "3") {
            std::cout << "Enter prep time in seconds: ";
            std::getline(std::cin, userInput);
            prepTime = std::stoi(userInput);
        } else if (userInput == "4") {
            std::cout << "Enter memorization time in seconds: ";
            std::getline(std::cin, userInput);
            memTime = std::stoi(userInput);
        } else if (userInput == "5") {
            std::cout << "Enter recall time in seconds: ";
            std::getline(std::cin, userInput);
            recallTime = std::stoi(userInput);
        } else if (userInput == "6") {
            backFlag = true;
        } else {
            std::cout << "Command not recognized! Please try again." << std::endl;
        }
    }
}

void NumbersGame::displayMenu() {
    bool exitFlag = false;
    while (!exitFlag) {
        clearTerminal();
        std::cout << "Numbers Game" << std::endl;
        std::cout << "1. Start Game" << std::endl;
        std::cout << "2. Options" << std::endl;
        std::cout << "3. Return to main menu" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Please enter your choice: ";
        
        std::string userInput;
        std::getline(std::cin, userInput);
        
        if (userInput == "1") {
            startGame();
        } else if (userInput == "2") {
            displayOptions();
        } else if (userInput == "3") {
            exitFlag = true;
        } else if (userInput == "4") {
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

