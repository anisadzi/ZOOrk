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
#include "Room.h"
#include <string>
#include <vector>
#include <algorithm>

class Player : public Character {
public:
    static Player *instance() {
        if (!playerInstance) {
            playerInstance = new Player();
        }
        return Player::playerInstance;
    }

    void setCurrentRoom(Room*);
    Room* getCurrentRoom() const;

    void addItem(const Item& item);
    void removeItem(const std::string& itenName);
    bool hasItem(const std::string& itemname) const;
    void showInventory() const;
    void printInventory() const;

    Item takeItem(const std::string& itemName); // Add this line
    bool move(const std::string& direction); // Add this line

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
