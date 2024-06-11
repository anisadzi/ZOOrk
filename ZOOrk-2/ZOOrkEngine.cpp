//
// Created by Richard Skarbez on 5/7/23.
//

#include "ZOOrkEngine.h"
#include "Passage.h"
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

void ZOOrkEngine::handleGoCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Go where?" << std::endl;
        return;
    }

    std::string direction = arguments[0];
    Room* currentRoom = player->getCurrentRoom();
    auto passage = currentRoom->getPassage(direction);

    if (!passage) {
        std::cout << "You can't go that way.\n";
        return;
    }

    if (passage->isLocked()) {
        std::cout << "The passage is locked. ";
        if (player->hasItem(passage->getKeyItem())) {
            std::cout << "Using your " << passage->getKeyItem() << ", you unlock the passage." << std::endl;
            passage->tryUnlock(*player);
        } else {
            std::cout << "You need a " << passage->getKeyItem() << " to unlock it." << std::endl;
            return;
        }
    }

    player->setCurrentRoom(passage->getTo());
    player->getCurrentRoom()->enter();
}

void ZOOrkEngine::handleLookCommand(std::vector<std::string> arguments) {
    Room* currentRoom = player->getCurrentRoom();

    if (arguments.empty()) {
        std::cout << currentRoom->getDescription() << std::endl;

        if (currentRoom->hasItems()) {
            for (const auto& item : currentRoom->getItems()) {
                std::cout << "You see a " << item.getName() << ": " << item.getDescription() << std::endl;
            }
        } else {
            std::cout << "The room is empty." << std::endl;
        }
    } else {
        bool itemFound = false;
        for (const auto& itemName : arguments) {
            if (currentRoom->hasItem(itemName)) {
                Item item = currentRoom->takeItem(itemName);
                std::cout << item.getDescription() << std::endl;
                itemFound = true;
                currentRoom->addItem(item); // Return the item to the room
            }
        }
        if (!itemFound) {
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

void ZOOrkEngine::handleTakeCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Take what?" << std::endl;
        return;
    }

    std::string itemName = arguments[0];
    Room* currentRoom = player->getCurrentRoom();

    if (currentRoom->hasItem(itemName)) {
        Item item = currentRoom->takeItem(itemName);
        player->addItem(item);
        std::cout << "You took the " << itemName << "." << std::endl;
    } else {
        std::cout << "There is no " << itemName << " here." << std::endl;
    }
}

void ZOOrkEngine::handleDropCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Drop what?" << std::endl;
        return;
    }

    std::string itemName = arguments[0];
    Player* currentPlayer = Player::instance();

    if (currentPlayer->hasItem(itemName)) {
        Room* currentRoom = currentPlayer->getCurrentRoom();
        Item item = currentPlayer->takeItem(itemName);
        currentRoom->addItem(item);
        std::cout << "You dropped the " << itemName << "." << std::endl;
    } else {
        std::cout << "You don't have a " << itemName << "." << std::endl;
    }
}

void ZOOrkEngine::handleQuitCommand(std::vector<std::string> arguments) {
    std::string input;
    std::cout << "Are you sure you want to QUIT?\n> ";
    std::getline(std::cin, input);
    std::string quitStr = makeLowercase(input);

    if (quitStr == "y" || quitStr == "yes") {
        gameOver = true;
    }
}

void ZOOrkEngine::handleInventoryCommand(std::vector<std::string> arguments) {
    player->showInventory();
}

std::vector<std::string> ZOOrkEngine::tokenizeString(const std::string &input) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, ' ')) {
        tokens.push_back(makeLowercase(token));
    }

    return tokens;
}

std::string ZOOrkEngine::makeLowercase(std::string input) {
    std::string output = std::move(input);
    std::transform(output.begin(), output.end(), output.begin(), ::tolower);

    return output;
}
