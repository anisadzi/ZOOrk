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
        return item.getName() == itemName;
    });
    if (it != inventory.end()) {
        Item item = *it;
        inventory.erase(it);
        return item;
    }
    throw std::runtime_error("Item not found in inventory");
}

void Player::addItem(const Item& item) {
    inventory.push_back(item);
}

void Player::removeItem(const std::string& itemName) {
    auto it = std::remove_if(inventory.begin(), inventory.end(), [&](const Item& item) {
        return item.getName() == itemName;
    });
    if (it != inventory.end()) {
        inventory.erase(it);
    }
}

bool Player::hasItem(const std::string& itemName) const {
    return std::any_of(inventory.begin(), inventory.end(), [&](const Item& item) {
        return item.getName() == itemName;
    });
}

void Player::showInventory() const {
    if (inventory.empty()) {
        std::cout << "Your inventory is empty" << std::endl;
    } else {
        std::cout << "You are carryinng: " << std::endl;
        for (const auto& item : inventory) {
            std::cout << "- " << item.getName() << ": " << item.getDescription() << std::endl;
        }
    }
}
