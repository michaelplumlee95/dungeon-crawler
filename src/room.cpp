#include <iostream>
#include "rng.h"
#include "room.h"
using namespace std;


    // Constructor that initializes the room with default values
    Room::Room()
    : isUnlocked(false), //default not unLocked 
      isTreasure(false), //default is no treasure
      isMonster(false) //default is no monster
    {
    }

    Room::Room(bool isUnlocked, bool isTreasure, bool isMonster)
      : isUnlocked(isUnlocked), //initialize treasure with parameter value
      isTreasure(isTreasure), //initialize treasure with parameter value
      isMonster(isMonster) //initialize monster with parameter value
    {
    }

    Room::Room(bool isUnlocked, bool isTreasure, bool isMonster, bool isShop)
      : isUnlocked(isUnlocked), //initialize treasure with parameter value
      isTreasure(isTreasure), //initialize treasure with parameter value
      isMonster(isMonster),
	  isShop(isShop)//initialize monster with parameter value
    {
    }


//getter functions
bool Room::getisUnlocked() { //return if there is treasure
    return isUnlocked; //return true if there is treasure, false otherwise
}
bool Room::getisTreasure() { //return if there is treasure
    return isTreasure; //return true if there is treasure, false otherwise
}
bool Room::getisMonster() { //return if there is a monster
    return isMonster; //return true if there is a monster, false otherwise
}

//setter functions
void Room::setisUnlocked(bool unlocked) { //set if the trapdoor is open
    isUnlocked = unlocked; //set the trapdoor status to the parameter value
}
void Room::setisTreasure(bool treasure) { //set if there is treasure
    isTreasure = treasure; //set the treasure status to the parameter value
}
void Room::setisMonster(bool monster) { //set if there is a monster
    isMonster = monster; //set the monster status to the parameter value
}
void Room::setisShop(bool shop) { //set if there is a shop 
    isShop = shop; //set the shop status to the parameter value
}

//behavior functions describing room
    // method to print the room's description
void Room::describe() { 
   //output attributes/features if true/they exist
   cout << "There is a trapdoor in the corner...\n";
   if (isMonster) cout << "There is a monster here!" << endl;
   if (isTreasure) cout << "You see a treasure chest glittering in the corner." << endl;
   if (isShop) cout << "Johnny is here... with a cart full of items.\n";
   // if none of the attributes are true, output that the room is empty
   if (!isMonster && !isTreasure) cout << "The room is empty and quiet." << endl;
}

Room Room::generateRoom()
{
	return Room(false, coinFlip(), coinFlip());
}
Room Room::generateShopRoom()
{
	return Room(true, false, false, true);
}
