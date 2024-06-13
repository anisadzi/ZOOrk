//
// Created by Richard Skarbez on 5/7/23.
//

#ifndef ZOORK_ROOM_H
#define ZOORK_ROOM_H

#include "Character.h"
#include "RoomDefaultEnterCommand.h"
#include "Item.h"
#include "Location.h"
#include <map>
#include <algorithm>

class Passage;

class Room : public Location {
public:
    // Constructor with name and description
    Room(const std::string &, const std::string &);
    
    // Constructor with name, description, and command
    Room(const std::string &, const std::string &, std::shared_ptr<Command>);

    // Method to add, remove an item to the room
    void addItem(const Item& item);
    void removeItem(const std::string& itemName);
    
    // Method to check if the room contains a specific item by name
    bool hasItem(const std::string& itemName) const;
    
    // Method to check if the room has any items
    bool hasItems() const;
    
    // Method to take (remove) an item from the room by name
    Item takeItem(const std::string& itemName);
    
    // Method to list all items in the room
    void listItems() const;
    
    // Method to print the room's inventory
    void printInventory() const;


//    void addCharacter(Character*);
//    void removeCharacter(const std::string&);
//    Character* getCharacter(const std::string&);

    // Method to add a passage to the room
    void addPassage(const std::string &, std::shared_ptr<Passage>);
    
    // Method to remove a passage from the room by direction
    void removePassage(const std::string &);
    
    // Method to get a passage from the room by direction
    std::shared_ptr<Passage> getPassage(const std::string &);
    
    // Method to get the description of the room
    std::string getDescription() const;

protected:
//    std::vector<Item*> items;
//    std::vector<Character*> characters;
    std::map<std::string, std::shared_ptr<Passage>> passageMap; // Map to store passages by direction

private:
    std::string name;               // Name of the room
    std::string description;        // Description of the room
    std::vector<Item> items;        // Vector to store items in the room
    std::vector<std::string> inventory;  // Vector to store inventory
};



#endif //ZOORK_ROOM_H
