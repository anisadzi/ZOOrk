#include <iostream>
#include <memory>
#include "RoomDefaultEnterCommand.h"
#include "Passage.h"
#include "Player.h"
#include "Room.h"
#include "ZOOrkEngine.h"


int main() {

    // Create shared pointers for all the rooms in the game
    std::shared_ptr<Room> start = std::make_shared<Room>("start-room",
                           "You find yourself in an open field west of a white house, its front door are open wide.\n");

    std::shared_ptr<Room> south_of_house = std::make_shared<Room>("south-of-house",
                            "You stand facing the south side of a white house. There's no door, and all windows are barred.\n");

    std::shared_ptr<Room> behind_house = std::make_shared<Room>("behind-house",
                            "You are behind the white house. A path leads into the forest to the east. A small window on the house's corner is slightly ajar.\n");
	
    std::shared_ptr<Room> white_house = std::make_shared<Room>("white-house",
                           "You are inside the white house. Look around and explore!\n");

    std::shared_ptr<Room> south_of_white_house = std::make_shared<Room>("south-of-white-house",
                            "You are at the south side of the white house. There's a door here leading to a swamp.\n");
                                    
    std::shared_ptr<Room> swamp = std::make_shared<Room>("swamp",
                            "You find yourself in a murky swamp. Game over. You need to restart.\n");

    std::shared_ptr<Room> east_of_white_house = std::make_shared<Room>("east-of-white-house",
                            "You are east of the white house, near a dense forest.\n");
    
    std::shared_ptr<Room> forest = std::make_shared<Room>("forest",
                            "You are lost in a dense forest. You need to find your way back.\n");
                                
    std::shared_ptr<Room> north_of_white_house = std::make_shared<Room>("north-of-white-house",
                            "You are at the north side of the white house. There's a tall, tricky tower nearby.\n");

    std::shared_ptr<Room> trick_tower= std::make_shared<Room>("trick-tower",
                            "You are inside the tricky tower. Look around and beware of tricks!\n");
    
    std::shared_ptr<Room> monster_castle = std::make_shared<Room>("monster-castle",
                            "You are trapped in the monster's castle. Game over. You need to restart.\n");
    
    std::shared_ptr<Room> cave_entrance = std::make_shared<Room>("cave-entrance",
                            "You are at the entrance of a dark cave.\n");

    std::shared_ptr<Room> waterfall = std::make_shared<Room>("waterfall",
                            "You have passed through the dark cave and reached a beautiful waterfall. You noticed something behind the waterfall.\n");
    
    std::shared_ptr<Room> first_door = std::make_shared<Room>("first-door",
                            "It was a door hidden behind the waterfall. You open the door and found yourself in a large hallway with a massive door at the end.\n");

    std::shared_ptr<Room> second_door = std::make_shared<Room>("second-door",
                            "You stand before a large door. It is locked with a padlock. You may need something to open it.\n");

    std::shared_ptr<Room> rainbow_road = std::make_shared<Room>("rainbow-road",
                            "Entering the room you noticed a large chest. Opening it, you realize it is a treasure chest. Congratulations! You have won the game!");
	
	 // Create items
    Item key("key", "A rusty key that seems to fit into a lock.");

    // Add items to the area
    trick_tower->addItem(key);
	
	
	// Create passages between different rooms using Passage static functions
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
	
	// Initialize the game engine with the starting room
    ZOOrkEngine zoork(start);

    // Run the game engine
    zoork.run();

    return 0;
}
