#ifndef NUMBERSGAME_H
#define NUMBERSGAME_H

#include <vector>
#include <string>
#include <unordered_map>

class NumbersGame {
public:
    NumbersGame();
    void displayMenu();
    void displayOptions();
    void startGame();

private:
    int numChars; // Number of digits in each string
    int numRows;  // Number of rows (strings) to be generated
    int prepTime; // Preparation time in seconds
    int memTime;  // Memorization time in seconds
    int recallTime; // Recall time in seconds

    std::vector<std::string> generateNumbers();
    void prepPhase();
    void memPhase(const std::vector<std::string>& generatedNumbers);
    void recallPhase(const std::vector<std::string>& generatedNumbers);
    void reviewPhase(const std::vector<std::string>& generatedNumbers, const std::vector<std::string>& userInput);
};

#endif // NUMBERSGAME_H
