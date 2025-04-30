#include "player.h"
#include <iostream>
#include <algorithm>
#include "items.h"
#include "rng.h"
#include <iomanip>

using namespace std;

// Constructors

Player::Player()
	: name("Player"),
	maxHP(100),
	HP(maxHP),
	baseArmourClass(14),
	baseAtkBonus(1),
	gold(0)
{

}

Player::Player(string name, int maxHP, int AC, int baseAttackBonus)
	: name(name),
	maxHP(maxHP),
	HP(maxHP),
	baseArmourClass(AC),
	baseAtkBonus(baseAttackBonus),
	gold(0)
{

}

// Iterator helper functions
vector<Item>::iterator Player::findItem(const string& itemName)
{
	// Im gonna use pointers and shit for this one because i wanna try it
	// Find the first matching item in the inventory
		return find_if( 
			inventory.begin(),
			inventory.end(),
			[&](const Item &i)
			{
			return i.getName() == itemName;
			}
		);
}

vector<Item>::const_iterator Player::findItem(const string& itemName) const // This one is for if we need to call from const methods
{
		return find_if( 
			inventory.begin(),
			inventory.end(),
			[&](const Item &i)
			{
			return i.getName() == itemName;
			}
		);
}

// Getters

int Player::getHP() const
{
	return HP;
}
 
int Player::getMaxHP() const
{
	return maxHP;
}
 
int Player::getArmourClass() const
{
	return baseArmourClass + armourSlot.getDefBonus();
}
 
int Player::getAtkBonus() const
{
	return baseAtkBonus + weaponSlot.getAttackBonus();
}

int Player::getGold() const
{
	return gold;
}

vector<Item> Player::getPlayerInventory() const
{
	return inventory;
}

Item Player::getWeapon() const
{
	return weaponSlot;
}

Item Player::getArmour() const
{
	return armourSlot;
}

// Behaviors

int Player::attackRoll()
{
	int roll = d20(rng);
	return roll + Player::getAtkBonus();
}

void Player::takeDmg(int amount)
{
	HP -= amount;
}

int Player::damageRoll()
{
	int numDice = weaponSlot.getNumDice(); 
	int numSides = weaponSlot.getDiceSides();

	std::uniform_int_distribution<> dist(1, numSides);
	int total = 0;
	for (int i = 0; i < numDice; i++)
		total += dist(rng);
	return total;
}


bool Player::isAlive() const
{
	return HP > 0;
}

bool Player::attemptFlee()
{
	int roll = d20(rng);
	return roll > 12;
}

void Player::useItem(const string& itemName)
{
	auto it = findItem(itemName);
	if (it == inventory.end()) // If item is not found
	{
		cout << "You don't have a " << itemName << "to use!\n";
		return;
	}
	if (it->getItemType() != "consumable")
	{
		cout << "You may not be using this item properly...\n";
		return;
	}

	// Apply the items effect
	int heal = it->getHealAmount(); // The iterator here is pointing at an item, to get its heal amount
	HP = min(maxHP, HP + heal); // sorry, no overheal
	cout << "You used a " << itemName << " and recovered " << heal << " HP.\n";

	// Remove the item after it is consumed
	inventory.erase(it); // Removes the item by iterator
}

bool Player::equipItem(const string& itemName)
{
	auto it = findItem(itemName);
	if (it == inventory.end()) // If item is not found
	{
		cout << "You don't have a " << itemName << "to equip!\n";
		return false;
	}
	if (it->getItemType() != "weapon" && it->getItemType() != "armour")
	{
		cout << itemName << " doesn't seem like a good thing to equip...\n";
		return false;
	}

	// Move the item into weaponSlot 
	if (it->getItemType() == "weapon")
	{
	weaponSlot = *it; // The weaponslot is assigned to whatever the iterator is pointing at
	cout << itemName << " is now equipped in the weapon slot!\n";
	}
	else if (it->getItemType() == "armour")
	{
	armourSlot = *it; // The weaponslot is assigned to whatever the iterator is pointing at
	cout << itemName << " is now equipped in the armour slot!\n";
	}
	inventory.erase(it); // Removes the item by iterator from the inventory
	return true;
}

void Player::showStatus() const {
    std::printf(
        "+----------------------------+\n"
        "|         STATUS             |\n"
        "+----------------------------+\n"
        "| HP:  %3d / %3d             |\n"
        "| AC:   %2d                   |\n"
        "| Gold: %5d                |\n"
        "+----------------------------+\n",
		HP, maxHP, getArmourClass(), gold
    );
}
void Player::addItemToInventory(const Item& i)
{
	inventory.push_back(i);
}


void Player::setHP(int newHP)
{
	HP = newHP;
}

void Player::spendGold(int amt)
{
	gold -= amt;
}

void Player::addGold(int amt)
{
	gold += amt;
}

