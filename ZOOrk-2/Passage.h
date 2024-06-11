//
// Created by Richard Skarbez on 5/7/23.
//

#ifndef ZOORK_PASSAGE_H
#define ZOORK_PASSAGE_H

#include "NullRoom.h"
#include "Room.h"
#include "Player.h"
#include "Location.h"
#include <iostream>

class Passage : public Location {
public:
    static void createBasicPassage(Room*, Room*, const std::string &, bool, bool, const std::string&);

    Passage(const std::string &, const std::string &, Room*, Room*);

    Passage(const std::string &, const std::string &, std::shared_ptr<Command>, Room*, Room*);

    void setFrom(Room*);

    Room* getFrom() const;

    void setTo(Room*);

    Room* getTo() const;
    
    bool isLocked() const;
    const std::string& getKeyItem() const;
    bool tryUnlock(Player& player);

protected:
    static std::string oppositeDirection(const std::string &);

    Room* fromRoom;
    Room* toRoom;
    bool locked;
    std::string keyItem;
};

#endif //ZOORK_PASSAGE_H
