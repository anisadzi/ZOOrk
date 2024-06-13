#include <iostream>
#include <memory>
#include "RoomDefaultEnterCommand.h"
#include "Passage.h"
#include "Player.h"
#include "Room.h"
#include "ZOOrkEngine.h"


int main() {

    std::shared_ptr<Room> start = std::make_shared<Room>("start-room",
                           "You are standing in an open field west of a white house, with a boarded front door.\n");

    std::shared_ptr<Room> south_of_house = std::make_shared<Room>("south-of-house",
                            "You are facing the south side of a white house.  There is no door here, and all the windows are barred.\n");

    std::shared_ptr<Room> behind_house = std::make_shared<Room>("behind-house",
                            "You are behind the white house. A path leads into the forest to the east. In one corner of the house there is a small window which is slightly ajar.\n");
	
	std::shared_ptr<Room> white_house = std::make_shared<Room>("white-house",
                           "You are in the white house. Look around and explore around you!\n");

    std::shared_ptr<Room> south_of_white_house = std::make_shared<Room>("south-of-white-house",
                            "You are facing the south side of a white house.  There is a door here that leads to a swamp.\n");
                                    
    std::shared_ptr<Room> swamp = std::make_shared<Room>("swamp",
                            "You are in a swamp. It's game over, you need to restart.\n");

    std::shared_ptr<Room> east_of_white_house = std::make_shared<Room>("east-of-white-house",
                            "You are east of the white house, near a dense forest.\n");
    
    std::shared_ptr<Room> forest = std::make_shared<Room>("forest",
                            "You are lost in a dense forest. You need to return to the previous room.\n");
                                
    std::shared_ptr<Room> north_of_white_house = std::make_shared<Room>("north-of-white-house",
                            "You are facing the north side of the white house. There's a tall trick tower up here.\n");

    std::shared_ptr<Room> trick_tower= std::make_shared<Room>("trick-tower",
                            "You are inside the trick tower, look around!.\n");
    
    std::shared_ptr<Room> monster_castle = std::make_shared<Room>("monster-castle",
                            "You are in the monster trap. It's game over. You need to restart.\n");
    
    std::shared_ptr<Room> cave_entrance = std::make_shared<Room>("cave-entrance",
                            "You are at the cave entrance of a dark cave.\n");

    std::shared_ptr<Room> waterfall = std::make_shared<Room>("waterfall",
                            "You have passed the dark cave. You are in the waterfall now.\n");
    
    std::shared_ptr<Room> first_door = std::make_shared<Room>("first-door",
                            "You are in front of a large door.\n");

    std::shared_ptr<Room> second_door = std::make_shared<Room>("second-door",
                            "You are in front of another large door, and you need a key to open the door.\n");

    std::shared_ptr<Room> rainbow_road = std::make_shared<Room>("rainbow-road",
                            "Congratulations! You've reached the Rainbow Road. You win!.\n");
	
	 // Create items
    Item torch("torch", "A burning torch to light your way.");
    Item key("key", "A rusty key that seems to fit into a lock.");

    // Add items to the white house
    white_house->addItem(torch);
    white_house->addItem(key);
	
	
	
    Passage::createBasicPassage(start.get(), white_house.get(), "east", true);
    Passage::createBasicPassage(start.get(), cave_entrance.get(), "west", true);
    Passage::createBasicPassage(white_house.get(), south_of_white_house.get(), "south", true);
    Passage::createBasicPassage(south_of_white_house.get(), swamp.get(), "south", true);
    Passage::createBasicPassage(swamp.get(), south_of_white_house.get(), "north", true);
    Passage::createBasicPassage(south_of_white_house.get(), white_house.get(), "north", true);
    Passage::createBasicPassage(white_house.get(), north_of_white_house.get(), "north", true);
    Passage::createBasicPassage(north_of_white_house.get(), trick_tower.get(), "north", true);
    Passage::createBasicPassage(trick_tower.get(), monster_castle.get(), "east", true);
    Passage::createBasicPassage(monster_castle.get(), trick_tower.get(), "west", true);
    Passage::createBasicPassage(trick_tower.get(), north_of_white_house.get(), "south", true);
    Passage::createBasicPassage(north_of_white_house.get(), white_house.get(), "south", true);
    Passage::createBasicPassage(white_house.get(), east_of_white_house.get(), "east", true);
    Passage::createBasicPassage(east_of_white_house.get(), forest.get(), "east", true);
    Passage::createBasicPassage(forest.get(), east_of_white_house.get(), "west", true);
    Passage::createBasicPassage(east_of_white_house.get(), white_house.get(), "west", true);
    Passage::createBasicPassage(cave_entrance.get(), waterfall.get(), "south", true);
    Passage::createBasicPassage(waterfall.get(),  first_door.get(), "south", true);
    Passage::createBasicPassage(first_door.get(),  second_door.get(), "east", true);
    Passage::createDoor(second_door.get(),  rainbow_road.get(), "east", key, true);
    Passage::createBasicPassage(second_door.get(),  first_door.get(), "west", true);
    Passage::createBasicPassage(first_door.get(),  waterfall.get(), "north", true);
    Passage::createBasicPassage(waterfall.get(),  cave_entrance.get(), "north", true);
    Passage::createBasicPassage(cave_entrance.get(), start.get(), "east", true);
	
	
    ZOOrkEngine zoork(start);

    zoork.run();

    return 0;
}
