#include "WordsGame.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <thread>
#include <chrono>

// Constructor to initialize default values and load the word list
WordsGame::WordsGame() : numWords(5), numRows(5), prepTime(10), memTime(300), recallTime(300) {
    loadWords();
}

void WordsGame::loadWords() {
    // Example word list, you can replace this with loading from a file
    wordList = {"apple", "banana", "cherry", "date", "elderberry", "fig", "grape", "honeydew", "kiwi", "lemon",
            "mango", "nectarine", "orange", "papaya", "quince", "raspberry", "strawberry", "tangerine", "ugli",
            "violet", "watermelon", "xigua", "yam", "zucchini", "acorn", "beet", "coconut", "durian", "eggplant",
            "fennel", "guava", "huckleberry", "jackfruit", "kumquat", "lime", "mulberry", "nectar", "olive", "peach",
            "quinoa", "radish", "spinach", "tomato", "ugli", "vanilla", "walnut", "xanthan", "yucca", "zest",
            "almond", "blueberry", "cranberry", "dragonfruit", "endive", "fig", "grapefruit", "hazelnut", "indigo",
            "jujube", "kale", "lemonade", "mango", "nutmeg", "okra", "pear", "quince", "rhubarb", "squash",
            "turnip", "uva", "valencia", "walnut", "xylitol", "yogurt", "ziti", "apricot", "blackberry", "celery",
            "dill", "elderberry", "feijoa", "ginger", "honey", "iceberg", "jalapeno", "kiwi", "lychee", "mandarin",
            "nut", "orange", "pineapple", "quiche", "radicchio", "shallot", "tangelo", "ugni", "vanilla", "watercress",
            "xanthan", "yam", "zucchini", "artichoke", "broccoli", "cabbage", "daikon", "eggplant", "fiddlehead",
            "ginseng", "horseradish", "iris", "jicama", "kohlrabi", "lettuce", "mushroom", "nectarine", "onion",
            "pepper", "quinoa", "rutabaga", "scallion", "turnip", "uva", "vetch", "watermelon", "xigua", "yarrow",
            "zucchini", "asparagus", "brussels", "carrot", "dandelion", "endive", "fennel", "grape", "hibiscus",
            "ivy", "jalapeno", "kale", "lemon", "melon", "nut", "okra", "plum", "quinine", "radicchio", "spinach",
            "tamarind", "ugni", "violet", "wasabi", "xanthan", "yogurt", "zest", "avocado", "beet", "cauliflower",
            "dragonfruit", "elderberry", "fig", "grapefruit", "honeydew", "iceberg", "jicama", "kiwifruit", "leek",
            "mango", "nectarine", "orange", "papaya", "quinoa", "rhubarb", "squash", "tangerine", "ugli", "violet",
            "watercress", "xigua", "yam", "zucchini", "alfalfa", "beetroot", "cashew", "daikon", "escarole",
            "figs", "guava", "hibiscus", "jackfruit", "kumquat", "lemon", "mango", "nectarine", "orange", "papaya",
            "quince", "raspberry", "strawberry", "tangerine", "ugli", "vanilla", "walnut", "xigua", "yam", "zucchini",
            "acorn", "beet", "coconut", "durian", "eggplant", "fennel", "guava", "huckleberry", "jackfruit",
            "kumquat", "lime", "mulberry", "nectar", "olive", "peach", "quinoa", "radish", "spinach", "tomato",
            "ugli", "vanilla", "walnut", "xanthan", "yucca", "zest", "almond", "blueberry", "cranberry", "dragonfruit",
            "endive", "fig", "grapefruit", "hazelnut", "indigo", "jujube", "kale", "lemonade", "mango", "nutmeg",
            "okra", "pear", "quince", "rhubarb", "squash", "turnip", "uva", "valencia", "walnut", "xylitol", "yogurt",
            "ziti", "apricot", "blackberry", "celery", "dill", "elderberry", "feijoa", "ginger", "honey", "iceberg",
            "jalapeno", "kiwi", "lychee", "mandarin", "nut", "orange", "pineapple", "quiche", "radicchio", "shallot",
            "tangelo", "ugni", "vanilla", "watercress", "xanthan", "yam", "zucchini", "artichoke", "broccoli",
            "cabbage", "daikon", "eggplant", "fiddlehead", "ginseng", "horseradish", "iris", "jicama", "kohlrabi",
            "lettuce", "mushroom", "nectarine", "onion", "pepper", "quinoa", "rutabaga", "scallion", "turnip", "uva",
            "vetch", "watermelon", "xigua", "yarrow", "zucchini", "asparagus", "brussels", "carrot", "dandelion",
            "endive", "fennel", "grape", "hibiscus", "ivy", "jalapeno", "kale", "lemon", "melon", "nut", "okra",
            "plum", "quinine", "radicchio", "spinach", "tamarind", "ugni", "violet", "wasabi", "xanthan", "yogurt",
            "zest", "avocado", "beet", "cauliflower", "dragonfruit", "elderberry", "fig", "grapefruit", "honeydew",
            "iceberg", "jicama", "kiwifruit", "leek", "mango", "nectarine", "orange", "papaya", "quinoa", "rhubarb",
            "squash", "tangerine", "ugli", "violet", "watercress", "xigua", "yam", "zucchini", "alfalfa", "beetroot",
            "cashew", "daikon", "escarole", "figs", "guava", "hibiscus", "jackfruit", "kumquat", "lemon", "mango",
            "nectarine", "orange", "papaya", "quince", "raspberry", "strawberry", "tangerine", "ugli", "vanilla",
            "walnut", "xigua", "yam", "zucchini", "acorn", "beet", "coconut", "durian", "eggplant", "fennel", "guava",
            "huckleberry", "jackfruit", "kumquat", "lime", "mulberry", "nectar", "olive", "peach", "quinoa", "radish",
            "spinach", "tomato", "ugli", "vanilla", "walnut", "xanthan", "yucca", "zest", "almond", "blueberry",
            "cranberry", "dragonfruit", "endive", "fig", "grapefruit", "hazelnut", "indigo", "jujube", "kale",
            "lemonade", "mango", "nutmeg", "okra", "pear", "quince", "rhubarb", "squash", "turnip", "uva", "valencia",
            "walnut", "xylitol", "yogurt", "ziti", "apricot", "blackberry", "celery", "dill", "elderberry", "feijoa",
            "ginger", "honey", "iceberg", "jalapeno", "kiwi", "lychee", "mandarin", "nut", "orange", "pineapple",
            "quiche", "radicchio", "shallot", "tangelo", "ugni", "vanilla", "watercress", "xanthan", "yam", "zucchini",
            "artichoke", "broccoli", "cabbage", "daikon", "eggplant", "fiddlehead", "ginseng", "horseradish", "iris",
            "jicama", "kohlrabi", "lettuce", "mushroom", "nectarine", "onion", "pepper", "quinoa", "rutabaga",
            "scallion", "turnip", "uva", "vetch", "watermelon", "xigua", "yarrow", "zucchini", "asparagus", "brussels",
            "carrot", "dandelion", "endive", "fennel", "grape", "hibiscus", "ivy", "jalapeno", "kale", "lemon",
            "melon", "nut", "okra", "plum", "quinine", "radicchio", "spinach", "tamarind", "ugni", "violet", "wasabi",
            "xanthan", "yogurt", "zest", "avocado", "beet", "cauliflower", "dragonfruit", "elderberry", "fig",
            "grapefruit", "honeydew", "iceberg", "jicama", "kiwifruit", "leek", "mango", "nectarine", "orange",
            "papaya", "quinoa", "rhubarb", "squash", "tangerine", "ugli", "violet", "watercress", "xigua", "yam",
            "zucchini"};

}

std::vector<std::string> WordsGame::generateWords() {
    std::vector<std::string> words;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, wordList.size() - 1);

    for (int i = 0; i < numRows; ++i) {
        std::string row;
        for (int j = 0; j < numWords; ++j) {
            if (!row.empty()) row += " ";
            row += wordList[dis(gen)];
        }
        words.push_back(row);
    }

    return words;
}

void WordsGame::prepPhase() {
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

void WordsGame::memPhase(const std::vector<std::string>& generatedWords) {
    clearTerminal();
    std::cout << "Memorization Phase" << std::endl;
    std::cout << "You have " << memTime << " seconds to memorize the words." << std::endl;

    for (const auto& wordRow : generatedWords) {
        std::cout << wordRow << std::endl;
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

void WordsGame::recallPhase(const std::vector<std::string>& generatedWords) {
    clearTerminal();
    std::cout << "RECALL:" << std::endl;
    std::cout << "Input the words you remember in a comma-delimited manner. Use '-' for unknowns." << std::endl;
    std::cout << "Example: apple banana cherry, -, grape honeydew" << std::endl;

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

    std::vector<std::string> userWords;
    std::string word;
    std::stringstream ss(userInput); // Initialize stringstream with userInput
    while (std::getline(ss, word, ',')) {
        // Remove leading and trailing whitespace
        word.erase(0, word.find_first_not_of(' '));
        word.erase(word.find_last_not_of(' ') + 1);
        userWords.push_back(word);
    }

    clearTerminal();
    reviewPhase(generatedWords, userWords);
}

void WordsGame::reviewPhase(const std::vector<std::string>& generatedWords, const std::vector<std::string>& userInput) {
    std::cout << "Review Phase" << std::endl;

    std::ofstream logFile("../logs/exit_log.txt", std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Unable to open log file." << std::endl;
    }

    int correct = 0;
    for (size_t i = 0; i < generatedWords.size(); ++i) {
        std::string generatedWordRow = generatedWords[i];
        std::string userWordRow = (i < userInput.size()) ? userInput[i] : "No input";

        logFile << "Row " << (i + 1) << ": " << generatedWordRow << ", User input: " << userWordRow << std::endl;

        std::cout << "Row " << (i + 1) << ": " << generatedWordRow;
        if (userWordRow == generatedWordRow) {
            std::cout << " (Correct)";
            correct++;
        } else {
            std::cout << " (Incorrect, you said: " << userWordRow << ")";
        }
        std::cout << std::endl;
    }

    logFile << "Score: " << correct << " out of " << generatedWords.size() << std::endl;
    logFile.close();

    std::cout << "Score: " << correct << " out of " << generatedWords.size() << std::endl;
    std::cout << "Press Enter to return to the main menu.";
    std::cin.ignore();
    std::cin.get();
    clearTerminal();
}

void WordsGame::startGame() {
    std::vector<std::string> generatedWords = generateWords();

    prepPhase();
    memPhase(generatedWords);
    recallPhase(generatedWords);
}

void WordsGame::displayOptions() {
    bool backFlag = false;
    while (!backFlag) {
        clearTerminal();
        std::cout << "Options" << std::endl;
        std::cout << "1. Set number of words per row (current: " << numWords << ")" << std::endl;
        std::cout << "2. Set number of rows (current: " << numRows << ")" << std::endl;
        std::cout << "3. Set prep time (current: " << prepTime << " seconds)" << std::endl;
        std::cout << "4. Set memorization time (current: " << memTime << " seconds)" << std::endl;
        std::cout << "5. Set recall time (current: " << recallTime << " seconds)" << std::endl;
        std::cout << "6. Return to words game menu" << std::endl;
        std::cout << "Please enter your choice: ";
        
        std::string userInput;
        std::getline(std::cin, userInput);
        
        if (userInput == "1") {
            std::cout << "Enter number of words per row: ";
            std::getline(std::cin, userInput);
            numWords = std::stoi(userInput);
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

void WordsGame::displayMenu() {
    bool exitFlag = false;
    while (!exitFlag) {
        clearTerminal();
        std::cout << "Words Game" << std::endl;
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

