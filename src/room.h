#ifndef ROOM_H
#define ROOM_H
#include <iostream>
using namespace std;

class Room{
private: //attributes and methods are public -> accessible from outside the class
    bool isUnlocked; //true if room has treasure; false is no treasure
    bool isTreasure; //true if room has treasure; false is no treasure
    bool isMonster; //true if room has monster; false is no monster
	bool isShop = 0;

public: 
//constructor
Room();
Room(bool isUnlocked,  bool isTreasure, bool isMonster); //constructor with parameters
Room(bool isUnlocked,  bool isTreasure, bool isMonster, bool isShop); //constructor with parameters

//these are getter functions below
bool getisUnlocked();
bool getisTreasure();
bool getisMonster();
bool getisShop();
//setter functions below to be used in main
void setisUnlocked(bool unlocked);
void setisTreasure(bool treasure);
void setisMonster(bool monster);
void setisShop(bool shop);
//behavior functioned named describe
void describe();
Room generateRoom();
Room generateShopRoom();
};

#endif
