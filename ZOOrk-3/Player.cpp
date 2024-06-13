//
// Created by Richard Skarbez on 5/7/23.
//

#include "Player.h"

#include <algorithm>

Player *Player::playerInstance = nullptr;

void Player::setCurrentRoom(Room* room) {
    currentRoom = room;
}

Room* Player::getCurrentRoom() const {
    return currentRoom;
}

Item Player::takeItem(const std::string& itemName) {
    auto it = std::find_if(inventory.begin(), inventory.end(), [&](const Item& item) {
        return item.getName() == itemName; // Lambda function to find item by name in inventory
    });
    if (it != inventory.end()) {
        Item item = *it; // Retrieves the item found
        inventory.erase(it); // Removes item from inventory
        return item; // Returns the item taken
    }
    throw std::runtime_error("Item not found in inventory"); // Throws exception if item not found
}

void Player::addItem(const Item& item) {
    inventory.push_back(item); // Adds an item to the player's inventory
}

void Player::removeItem(const std::string& itemName) {
    auto it = std::remove_if(inventory.begin(), inventory.end(), [&](const Item& item) {
        return item.getName() == itemName; // Lambda function to find and remove item by name from inventory
    });
    if (it != inventory.end()) {
        inventory.erase(it); // Erase item from inventory
    }
}

bool Player::hasItem(const std::string& itemName) const {
    return std::any_of(inventory.begin(), inventory.end(), [&](const Item& item) {
        return item.getName() == itemName; // Lambda function to check if player has an item by name in inventory
    });
}

// Public method to print player's inventory
void Player::showInventory() const {
    printInventory();
}

void Player::printInventory() const {
    if (inventory.empty()) {
        std::cout << "Your inventory is empty" << std::endl;
    } else {
        std::cout << "You are carrying: " << std::endl;
        for (const auto& item : inventory) {
            std::cout << "- " << item.getName() << ": " << item.getDescription() << std::endl;
        }
    }
}
