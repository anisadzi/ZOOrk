//
// Created by Richard Skarbez on 5/7/23.
//

#include "Door.h"
#include "Passage.h"
#include "Room.h"
#include "Item.h"
#include <memory>
#include <string>
#include <utility>
#include "PassageDefaultEnterCommand.h"

std::string Passage::oppositeDirection(const std::string &s) {
    if (s == "north") return "south";
    else if (s == "south") return "north";
    else if (s == "east") return "west";
    else if (s == "west") return "east";
    else if (s == "up") return "down";
    else if (s == "down") return "up";
    else if (s == "in") return "out";
    else if (s == "out") return "in";
    else return "unknown_direction";
}

// Static method to create a basic passage between two rooms
void Passage::createBasicPassage(Room* from, Room* to,
                                 const std::string &direction, bool bidirectional = true) {
    std::string passageName = from->getName() + "_to_" + to->getName();
    auto temp1 = std::make_shared<Passage>(passageName, "A totally normal passageway.", from, to);
    from->addPassage(direction, temp1);
    if (bidirectional) {
        std::string passageName2 = to->getName() + "_to_" + from->getName();
        auto temp2 = std::make_shared<Passage>(passageName, "A totally normal passageway.", to, from);
        to->addPassage(oppositeDirection(direction), temp2);
    }
}

// Static method to create a door passage between two rooms
void Passage::createDoor(Room* from, Room* to, const std::string &direction, const Item &requiredItem, bool bidirectional) {
    std::string passageName = from->getName() + "_to_" + to->getName();
    auto temp1 = std::make_shared<Door>(passageName, "A locked door.", from, to, requiredItem);
    from->addPassage(direction, temp1);
    if (bidirectional) {
        std::string passageName2 = to->getName() + "_to_" + from->getName();
        auto temp2 = std::make_shared<Door>(passageName2, "A locked door.", to, from, requiredItem);
        to->addPassage(oppositeDirection(direction), temp2);
    }
}

// Constructor for Passage class, initializing with name, description, and connected rooms
Passage::Passage(const std::string &n, const std::string &d, Room* from, Room* to)
        : Location(n, d), fromRoom(from), toRoom(to) {
    setEnterCommand(std::make_shared<PassageDefaultEnterCommand>(this));
}

// Constructor for Passage class, initializing with name, description, command, and connected rooms
Passage::Passage(const std::string &n, const std::string &d, std::shared_ptr<Command> c, Room* from,
                 Room* to)
        : Location(n, d, std::move(c)), fromRoom(from), toRoom(to) {}

// Setter Getter method for 'from' room
void Passage::setFrom(Room* r) {
    fromRoom = r;
}
Room* Passage::getFrom() const {
    return fromRoom;
}

// Setter Getter method for 'to' room
void Passage::setTo(Room* r) {
    toRoom = r;
}
Room* Passage::getTo() const {
    return toRoom;
}

