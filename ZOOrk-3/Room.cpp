//
// Created by Richard Skarbez on 5/7/23.
//

#include "NullPassage.h"
#include "Room.h"
#include "Item.h"

#include <utility>
#include <iostream>
#include <stdexcept>

#include "GameObject.h"

// Constructor for Room class, initializing with name and description
Room::Room(const std::string &n, const std::string &d) : Location(n, d) {
    enterCommand = std::make_shared<RoomDefaultEnterCommand>(this);
}

// Constructor for Room class, initializing with name, description, and custom command
Room::Room(const std::string &n, const std::string &d, std::shared_ptr<Command> c) : Location(n, d, std::move(c)) {}

// Method to add an item to the room
void Room::addItem(const Item& item) {
    items.push_back(item);
}

// Method to remove an item from the room by its name
void Room::removeItem(const std::string& itemName) {
    auto it = std::remove_if(items.begin(), items.end(), [&](const Item& item) {
        return item.getName() == itemName;
    });
    if (it != items.end()) {
        items.erase(it);
    }
}

// Method to check if the room has any items
bool Room::hasItems() const {
    return !items.empty();
}

// Method to list all items in the room
void Room::listItems() const {
    for (const auto& item : items) {
        std::cout << "- " << item.getName() << std::endl;
    }
}

// Method to check if the room contains a specific item by its name
bool Room::hasItem(const std::string& itemName) const {
    return std::any_of(items.begin(), items.end(), [&](const Item& item) {
        return item.getName() == itemName;
    });
}

// Method to take (remove) an item from the room by its name
Item Room::takeItem(const std::string& itemName) {
    auto it = std::find_if(items.begin(), items.end(), [&](const Item& item) {
        return item.getName() == itemName;
    });
    if (it != items.end()) {
        Item item = *it;
        items.erase(it);
        return item;
    }
    throw std::runtime_error("Item not found");
}

// Method to add a passage to the room in a specific direction
void Room::addPassage(const std::string &direction, std::shared_ptr<Passage> p) {
    passageMap[direction] = std::move(p);
}

// Method to remove a passage from the room in a specific direction
void Room::removePassage(const std::string &direction) {
    auto it = passageMap.find(direction);
    if (it != passageMap.end()) {
        passageMap.erase(it);
    }
}

// Method to get a passage from the room in a specific direction
std::shared_ptr<Passage> Room::getPassage(const std::string &direction) {
    auto it = passageMap.find(direction);
    if (it != passageMap.end()) {
        return it->second;
    } else {
        return nullptr;
    }
}

// Method to get the description of the room, including any items present
std::string Room::getDescription() const {
    std::string roomDescription = description;
    if(!items.empty()) {
        roomDescription += "\n\nItems in the room:\n";
        for(const auto& item : items) {
             roomDescription += "- " + item.getDescription() + "\n";
        }
    }
    return roomDescription;
}
