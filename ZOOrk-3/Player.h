//
// Created by Richard Skarbez on 5/7/23.
//

// Player.h

#ifndef ZOORK_PLAYER_H
#define ZOORK_PLAYER_H

#include "Character.h"
#include "Location.h"
#include "NullRoom.h"
#include "Item.h"

#include <vector>
#include <algorithm>

class Player : public Character {
public:
    static Player *instance() {
        // Note: lazy instantiation of the singleton Player object
        if (!playerInstance) {
            playerInstance = new Player();
        }
        return Player::playerInstance;
    }

    void setCurrentRoom(Room*);                   // Set the current room for the player
    Room* getCurrentRoom() const;                 // Get the current room where the player is located

    void addItem(const Item& item);               // Add an item to the player's inventory
    void removeItem(const std::string& itemName); // Remove an item from the player's inventory by name
    bool hasItem(const std::string& itemName) const; // Check if the player has a specific item by name
    void showInventory() const;                   // Public method to show the player's inventory
    void printInventory() const;                  // Print the player's inventory

    Item takeItem(const std::string& itemName);   // Take (remove) an item from the player's inventory

    Player(const Player &) = delete;
    Player &operator=(const Player &) = delete;

private:
    static Player *playerInstance;
    Room* currentRoom;
    std::vector<Item> inventory;

    Player() : Character("You", "You are a person, alike in dignity to any other, but uniquely you."),
               currentRoom(new NullRoom()) {}
};

#endif //ZOORK_PLAYER_H
