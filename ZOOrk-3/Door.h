#ifndef ZOORK_DOOR_H
#define ZOORK_DOOR_H

#include "Passage.h"
#include "Item.h"
#include "Player.h"

class Door : public Passage {
public:
    Door(const std::string &n, const std::string &d, Room* from, Room* to, const Item &requiredItem)
        : Passage(n, d, from, to), requiredItem(requiredItem) {}

    void enter() override {
        Player* player = Player::instance();
        if (player->hasItem(requiredItem.getName())) {
            std::cout << "You used the " << requiredItem.getName() << " to unlock the door.\n";
            Passage::enter();
        } else {
            std::cout << "The door is locked. You might need a " << requiredItem.getName() << " to open it.\n";
        }
    }

private:
    Item requiredItem;
};

#endif //ZOORK_DOOR_H
