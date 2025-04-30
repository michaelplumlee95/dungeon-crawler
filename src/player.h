#ifndef PLAYER_H
#define PLAYER_H

#include <algorithm>
#include <string>
#include "items.h"
#include <vector>
using namespace std;


class Player{
	private:
		string name;
		int maxHP;
		int HP;
		int baseArmourClass;
		int baseAtkBonus;
		int gold;
		vector<Item> inventory;
		Item weaponSlot{ "hands", "empty", 0, "weapon", 0, 0, 0, 0, 1, 4, 0, }; // default initialize empty hands
		Item armourSlot;
		vector<Item>::iterator findItem(const string& name);				// Iterator helper functions for searching inventories
		vector<Item>::const_iterator findItem(const string& name) const;

	public:
		// Constructors
		Player();
		Player(string name, int maxHP, int AC, int baseAttackBonus);
		// Getters
		int getHP() const;
		int getMaxHP() const;
		int getArmourClass() const;
		int getAtkBonus() const;
		int getGold() const;
		vector<Item> getPlayerInventory() const;
		Item getWeapon() const;
		Item getArmour() const;
		// Behavior
		void setHP(int newHP);
		int attackRoll(); 								// Rolls a d20 and applies baseAtkBonus and weapon atkbonus
		void takeDmg(int amount); 						// Subtracts playerHP by an amount
		int damageRoll();								// handles players damage roll
		bool isAlive() const; 							// return playerHP > 0
		bool attemptFlee(); 							// Rolls a d20 and returns true if greater than 12
		void useItem(const std::string& itemName);	 	// searches inventory for an item with matching name, and attempts to use it.
		bool equipItem(const string& itemName);		// searches invenotry for matching itemname, removes, and assigns to weaponSlot													
		void showStatus() const;						// Print HP/maxHP, AC, AtkBonus, gold, and list items in inventory
		void addItemToInventory(const Item& i);
		void spendGold(int amt);
		void addGold(int amt);
};

#endif
