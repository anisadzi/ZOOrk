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


Room::Room(const std::string &n, const std::string &d) : Location(n, d) {
    enterCommand = std::make_shared<RoomDefaultEnterCommand>(this);
}

Room::Room(const std::string &n, const std::string &d, std::shared_ptr<Command> c) : Location(n, d, std::move(c)) {}

void Room::addItem(const Item& item) {
    items.push_back(item);
}

void Room::removeItem(const std::string& itemName) {
    auto it = std::remove_if(items.begin(), items.end(), [&](const Item& item) {
        return item.getName() == itemName;
    });
    if (it != items.end()) {
        items.erase(it);
    }
}

bool Room::hasItems() const {
    return !items.empty();
}

void Room::listItems() const {
    for (const auto& item : items) {
        std::cout << "- " << item.getName() << std::endl;
    }
}

bool Room::hasItem(const std::string& itemName) const {
    return std::any_of(items.begin(), items.end(), [&](const Item& item) {
        return item.getName() == itemName;
    });
}

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

std::vector<Item> Room::getItems() const {
    return items;
}

void Room::addPassage(const std::string &direction, std::shared_ptr<Passage> p) {
    passageMap[direction] = std::move(p);
}

void Room::removePassage(const std::string &direction) {
    auto it = passageMap.find(direction);
    if (it != passageMap.end()) {
        passageMap.erase(it);
    }
}

std::shared_ptr<Passage> Room::getPassage(const std::string &direction) {
    auto it = passageMap.find(direction);
    if (it != passageMap.end()) {
        return it->second;
    } else {
        std::cout << "It is impossible to go " << direction << "!\n";
        return nullptr;
    }
}

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
