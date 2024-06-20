#ifndef CARDGAME_H
#define CARDGAME_H

#include <vector>
#include <string>
#include <unordered_map>

class CardGame {
public:
    CardGame(); // Constructor to initialize default values
    void displayMenu();
    void startGame();
    void displayOptions();

private:
    int numDecks;
    int numDraws;
    int prepTime;
    int memTime;
    int recallTime;
    std::vector<std::string> deck;
    std::unordered_map<std::string, std::string> cardMap;

    void initializeDeck();
    void shuffleDeck();
    std::vector<std::string> drawCards(int numDraws);
    void prepPhase();
    void memPhase(const std::vector<std::string>& drawnCards);
    void recallPhase(const std::vector<std::string>& drawnCards);
    void reviewPhase(const std::vector<std::string>& drawnCards, const std::vector<std::string>& userInput);
    std::string toShorthand(const std::string& card);
};

#endif // CARDGAME_H

