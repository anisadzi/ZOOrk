//
// Created by Richard Skarbez on 5/7/23.
//

#include "ZOOrkEngine.h"

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

ZOOrkEngine::ZOOrkEngine(std::shared_ptr<Room> start) {
    player = Player::instance();
    player->setCurrentRoom(start.get());
    player->getCurrentRoom()->enter();
}

void ZOOrkEngine::run() {
    while (!gameOver) {
        std::cout << "> ";

        std::string input;
        std::getline(std::cin, input);

        std::vector<std::string> words = tokenizeString(input);
        std::string command = words[0];
        std::vector<std::string> arguments(words.begin() + 1, words.end());
        
        
        // Determine which command to execute based on the first word
        if (command == "go") {
            handleGoCommand(arguments);
        } else if ((command == "look") || (command == "inspect")) {
            handleLookCommand(arguments);
        } else if ((command == "take") || (command == "get")) {
            handleTakeCommand(arguments);
        } else if (command == "drop") {
            handleDropCommand(arguments);
        } else if (command == "quit") {
            handleQuitCommand(arguments);
        } else if (command == "inventory") {
            handleInventoryCommand(arguments);
        } else {
            std::cout << "I don't understand that command.\n";
        }
    }
}


// Handler for the 'go' command
void ZOOrkEngine::handleGoCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Go where?" << std::endl;
        return;
    }

    std::string direction;
    if (arguments[0] == "n" || arguments[0] == "north") {
        direction = "north";
    } else if (arguments[0] == "s" || arguments[0] == "south") {
        direction = "south";
    } else if (arguments[0] == "e" || arguments[0] == "east") {
        direction = "east";
    } else if (arguments[0] == "w" || arguments[0] == "west") {
        direction = "west";
    } else if (arguments[0] == "u" || arguments[0] == "up") {
        direction = "up";
    } else if (arguments[0] == "d" || arguments[0] == "down") {
        direction = "down";
    } else {
        direction = arguments[0];
    }

    Room* currentRoom = player->getCurrentRoom();
    auto passage = currentRoom->getPassage(direction);
    if (passage == nullptr) {
        std::cout << "It is impossible to go " << direction << "!" << std::endl;
    } else {
        player->setCurrentRoom(passage->getTo());
        passage->enter();
    }
}


// Handler for the 'look' command
void ZOOrkEngine::handleLookCommand(std::vector<std::string> arguments) {
    Room* currentRoom = player->getCurrentRoom();

    if (arguments.empty()) {
        // If no arguments provided, print the description of the current room
        std::cout << currentRoom->getDescription() << std::endl;

        // Check if the room has any items and list them
        if (currentRoom->hasItems()) {
            
        } else {
            std::cout << "The room is empty." << std::endl;
        }

    } else {
        bool itemFound = false;
        for (const auto& itemName : arguments) {
            if (currentRoom->hasItem(itemName)) {
            // If the item exists, print its description
            Item item = currentRoom->takeItem(itemName);
            std::cout << item.getDescription() << std::endl;
            itemFound = true;
            } 
        }
        if (!itemFound) {
            // If no matching item found, print a message
            std::cout << "There is no ";
            for (size_t i = 0; i < arguments.size(); ++i) {
                std::cout << arguments[i];
                if (i < arguments.size() - 1) {
                    std::cout << " ";
                }
            }
            std::cout << " here." << std::endl;
        }
    }
}


// Handler for the 'take' command
void ZOOrkEngine::handleTakeCommand(std::vector<std::string> arguments) {
    // To be implemented
    if (arguments.empty()) {
        std::cout << "Take what?" << std::endl;
        return;
    }

    std::string itemName = arguments[0]; // Assuming single word item names for simplicity
    Room* currentRoom = Player::instance()->getCurrentRoom();

    if (currentRoom->hasItem(itemName)) {
        Item item = currentRoom->takeItem(itemName);
        Player::instance()->addItem(item);
        // currentRoom -> removeItem(itemName);
        std::cout << "You took the " << itemName << "." << std::endl;
    } else {
        std::cout << "There is no " << itemName << " here." << std::endl;
    }
    // std::cout << "This functionality is not yet enabled.\n";
}


// Handler for the 'drop' command
void ZOOrkEngine::handleDropCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Drop what?" << std::endl;
        return;
    }

    std::string itemName = arguments[0]; // Assuming single word item names for simplicity
    Player* currentPlayer = Player::instance();

    if (currentPlayer->hasItem(itemName)) {
        Room* currentRoom = currentPlayer->getCurrentRoom();
        Item item = currentPlayer->takeItem(itemName); // Use takeItem to get the item object
        currentRoom->addItem(item);
        std::cout << "You dropped the " << itemName << "." << std::endl;
    } else {
        std::cout << "You don't have a " << itemName << "." << std::endl;
    }
}


// Handler for the 'quit' command
void ZOOrkEngine::handleQuitCommand(std::vector<std::string> arguments) {
    std::string input;
    std::cout << "Are you sure you want to QUIT?\n> ";
    std::getline(std::cin, input);
    std::string quitStr = makeLowercase(input);

    if (quitStr == "y" || quitStr == "yes") {
        gameOver = true;
    } else if (quitStr == "n" || quitStr == "no") {
        std::cout << "Quit aborted.\n";
    } else {
        std::cout << "Invalid input. Quit aborted.\n";
    }
}


// Handler for the 'inventory' command
void ZOOrkEngine::handleInventoryCommand(std::vector<std::string> arguments) {
    player->showInventory();
}


// Utility method to tokenize a string into words
std::vector<std::string> ZOOrkEngine::tokenizeString(const std::string &input) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, ' ')) {
        tokens.push_back(makeLowercase(token));
    }

    return tokens;
}


// Utility method to convert a string to lowercase
std::string ZOOrkEngine::makeLowercase(std::string input) {
    std::string output = std::move(input);
    std::transform(output.begin(), output.end(), output.begin(), ::tolower);

    return output;
}
