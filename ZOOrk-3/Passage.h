//
// Created by Richard Skarbez on 5/7/23.
//

#ifndef ZOORK_PASSAGE_H
#define ZOORK_PASSAGE_H

#include "NullRoom.h"
#include "Room.h"
#include <iostream>

class Passage : public Location {
public:
    // Static function to create a basic passage between two rooms
    static void
    createBasicPassage(Room*, Room*, const std::string &, bool);

    // Constructors for Passage class
    Passage(const std::string &, const std::string &, Room*, Room*);
    Passage(const std::string &, const std::string &, std::shared_ptr<Command>, Room*, Room*);

    // Setter and getter for 'from' room
    void setFrom(Room*);
    Room* getFrom() const;

    // Setter and getter for 'to' room
    void setTo(Room*);
    Room* getTo() const;
    
    // Static function to create a door passage between two rooms
    static void createDoor(Room* from, Room* to, const std::string &direction, 
    const Item &requiredItem, bool bidirectional = true);

protected:
    // Static function to find the opposite direction for bidirectional passages
    static std::string oppositeDirection(const std::string &);

    // Member variables representing the connected rooms
    Room* fromRoom;
    Room* toRoom;
};

#endif //ZOORK_PASSAGE_H
