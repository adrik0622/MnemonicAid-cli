#include "CardGame.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <thread>
#include <chrono>
#include <sstream>
#include <unordered_map>

// Constructor to initialize default values
CardGame::CardGame() : numDecks(1), numDraws(5), prepTime(10), memTime(300), recallTime(300) {
    initializeDeck();
}

void CardGame::initializeDeck() {
    deck.clear();
    cardMap.clear();
    std::vector<std::string> suits = {"Hearts", "Diamonds", "Clubs", "Spades"};
    std::vector<std::string> suitShort = {"h", "d", "c", "s"};
    std::vector<std::string> values = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    std::vector<std::string> valueShort = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "j", "q", "k", "a"};

    for (int i = 0; i < numDecks; ++i) {
        for (size_t j = 0; j < suits.size(); ++j) {
            for (size_t k = 0; k < values.size(); ++k) {
                std::string fullCard = values[k] + " of " + suits[j];
                std::string shortCard = valueShort[k] + suitShort[j];
                deck.push_back(fullCard);
                cardMap[fullCard] = shortCard;
                cardMap[shortCard] = fullCard;
            }
        }
    }
}

void CardGame::shuffleDeck() {
    std::srand(unsigned(std::time(0)));
    std::random_shuffle(deck.begin(), deck.end());
}

std::vector<std::string> CardGame::drawCards(int numDraws) {
    std::vector<std::string> drawnCards;
    for (int i = 0; i < numDraws && !deck.empty(); ++i) {
        drawnCards.push_back(deck.back());
        deck.pop_back();
    }
    return drawnCards;
}

void CardGame::prepPhase() {
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

void CardGame::memPhase(const std::vector<std::string>& drawnCards) {
    clearTerminal();
    std::cout << "Memorization Phase" << std::endl;
    std::cout << "You have " << memTime << " seconds to memorize the cards." << std::endl;

    for (const auto& card : drawnCards) {
        std::cout << card << std::endl;
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

void CardGame::recallPhase(const std::vector<std::string>& drawnCards) {
    clearTerminal();
    std::cout << "RECALL:" << std::endl;
    std::cout << "Input the cards you remember in a comma-delimited manner. Use '-' for unknowns." << std::endl;
    std::cout << "Example: 3h, as, -, kc, 5d or 3 of Hearts, A of Spades, -, K of Clubs, 5 of Diamonds" << std::endl;

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

    std::vector<std::string> userCards;
    std::string card;
    std::stringstream ss(userInput); // Initialize stringstream with userInput
    while (std::getline(ss, card, ',')) {
        // Remove leading and trailing whitespace
        card.erase(0, card.find_first_not_of(' '));
        card.erase(card.find_last_not_of(' ') + 1);
        userCards.push_back(card);
    }

    clearTerminal();
    reviewPhase(drawnCards, userCards);
}

std::string CardGame::toShorthand(const std::string& card) {
    auto it = cardMap.find(card);
    if (it != cardMap.end()) {
        return it->second;
    }
    return card;
}

void CardGame::reviewPhase(const std::vector<std::string>& drawnCards, const std::vector<std::string>& userInput) {
    std::cout << "Review Phase" << std::endl;

    std::ofstream logFile("../logs/exit_log.txt", std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Unable to open log file." << std::endl;
    }

    int correct = 0;
    for (size_t i = 0; i < drawnCards.size(); ++i) {
        std::string drawnCard = drawnCards[i];
        std::string drawnCardShort = toShorthand(drawnCard);
        
        std::string userCard = (i < userInput.size()) ? userInput[i] : "No input";
        std::string userCardShort = toShorthand(userCard);

        logFile << "Card " << (i + 1) << ": " << drawnCard << " (shorthand: " << drawnCardShort << "), ";
        logFile << "User input: " << userCard << " (shorthand: " << userCardShort << ")" << std::endl;

        std::cout << "Card " << (i + 1) << ": " << drawnCard;
        if (userCardShort == drawnCardShort) {
            std::cout << " (Correct)";
            correct++;
        } else {
            std::cout << " (Incorrect, you said: " << userCard << ")";
        }
        std::cout << std::endl;
    }

    logFile << "Score: " << correct << " out of " << drawnCards.size() << std::endl;
    logFile.close();

    std::cout << "Score: " << correct << " out of " << drawnCards.size() << std::endl;
    std::cout << "Press Enter to return to the main menu.";
    std::cin.ignore();
    std::cin.get();
    clearTerminal();
}

void CardGame::startGame() {
    shuffleDeck();
    std::vector<std::string> drawnCards = drawCards(numDraws);

    prepPhase();
    memPhase(drawnCards);
    recallPhase(drawnCards);
}

void CardGame::displayOptions() {
    bool backFlag = false;
    while (!backFlag) {
        clearTerminal();
        std::cout << "Options" << std::endl;
        std::cout << "1. Set number of decks (current: " << numDecks << ")" << std::endl;
        std::cout << "2. Set number of draws (current: " << numDraws << ")" << std::endl;
        std::cout << "3. Set prep time (current: " << prepTime << " seconds)" << std::endl;
        std::cout << "4. Set memorization time (current: " << memTime << " seconds)" << std::endl;
        std::cout << "5. Set recall time (current: " << recallTime << " seconds)" << std::endl;
        std::cout << "6. Return to card game menu" << std::endl;
        std::cout << "Please enter your choice: ";
        
        std::string userInput;
        std::getline(std::cin, userInput);
        
        if (userInput == "1") {
            std::cout << "Enter number of decks: ";
            std::getline(std::cin, userInput);
            numDecks = std::stoi(userInput);
            initializeDeck();
        } else if (userInput == "2") {
            std::cout << "Enter number of draws: ";
            std::getline(std::cin, userInput);
            numDraws = std::stoi(userInput);
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

void CardGame::displayMenu() {
    bool exitFlag = false;
    while (!exitFlag) {
        clearTerminal();
        std::cout << "Card Game" << std::endl;
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

