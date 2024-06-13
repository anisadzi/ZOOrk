//
// Created by Richard Skarbez on 5/7/23.
//

#ifndef ZOORK_ZOORKENGINE_H
#define ZOORK_ZOORKENGINE_H

#include "Player.h"
#include "Location.h"
#include "Passage.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class ZOOrkEngine {
public:
    ZOOrkEngine(std::shared_ptr<Room>);

    void run();

private:
     bool gameOver = false;               // Flag indicating if the game is over
    Player *player;                      // Pointer to the player object

    // Private methods to handle different commands
    void handleGoCommand(std::vector<std::string>);         // Handle 'go' command
    void handleLookCommand(std::vector<std::string>);       // Handle 'look' command
    void handleTakeCommand(std::vector<std::string>);       // Handle 'take' command
    void handleDropCommand(std::vector<std::string>);       // Handle 'drop' command
    void handleQuitCommand(std::vector<std::string>);       // Handle 'quit' command
    void handleInventoryCommand(std::vector<std::string>);  // Handle 'inventory' command

    // Utility methods
    static std::vector<std::string> tokenizeString(const std::string&);  // Tokenize a string into a vector of strings
    static std::string makeLowercase(std::string);          // Convert a string to lowercase
};

#endif //ZOORK_ZOORKENGINE_H
