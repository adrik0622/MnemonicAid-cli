#ifndef WORDSGAME_H
#define WORDSGAME_H

#include <vector>
#include <string>
#include <unordered_map>

class WordsGame {
public:
    WordsGame();
    void displayMenu();
    void displayOptions();
    void startGame();

private:
    int numWords; // Number of words in each row
    int numRows;  // Number of rows (strings) to be generated
    int prepTime; // Preparation time in seconds
    int memTime;  // Memorization time in seconds
    int recallTime; // Recall time in seconds

    std::vector<std::string> wordList;
    std::vector<std::string> generateWords();
    void prepPhase();
    void memPhase(const std::vector<std::string>& generatedWords);
    void recallPhase(const std::vector<std::string>& generatedWords);
    void reviewPhase(const std::vector<std::string>& generatedWords, const std::vector<std::string>& userInput);

    void loadWords();
};

#endif // WORDSGAME_H

