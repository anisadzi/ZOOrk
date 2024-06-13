#ifndef ZOORK_DOOR_H
#define ZOORK_DOOR_H

#include "Passage.h"   // Include the base class Passage header file
#include "Item.h"      // Include the Item header file for requiredItem
#include "Player.h"    // Include the Player header file for interacting with the player

class Door : public Passage {  // Declare Door class which inherits from Passage
public:
    // Constructor for Door class
    // Parameters:
    //   - n: Name of the door
    //   - d: Description of the door
    //   - from: Pointer to the Room where the door originates
    //   - to: Pointer to the Room where the door leads to
    //   - requiredItem: Item required to unlock the door
    Door(const std::string &n, const std::string &d, Room* from, Room* to, const Item &requiredItem)
        : Passage(n, d, from, to), requiredItem(requiredItem) {} // Initialize base class Passage with provided parameters
        // Initialize member variable requiredItem with provided Item


// Override the enter method from Passage class
    void enter() override {
        Player* player = Player::instance(); // Get the singleton instance of Player
        if (player->hasItem(requiredItem.getName())) { // Check if player has the required item
            std::cout << "You used the " << requiredItem.getName() << " to unlock the door.\n";
            Passage::enter(); // Call the base class enter method
        } else {
            std::cout << "The door is locked. You might need a " << requiredItem.getName() << " to open it.\n";
        }
    }

private:
    Item requiredItem; // Member variable to store the required item for unlocking the door
};

#endif //ZOORK_DOOR_H
