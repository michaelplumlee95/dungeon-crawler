#ifndef ITEMS_H
#define ITEMS_H

#include <string>
using namespace std;

class Item {
	private:
		string name;
		string description;
		int price;
		string itemtype;
		int rarity;
		int healAmount;
		int attackBonus;
		int defBonus;
		int damage;
		int numDice = 0;
		int diceSides = 0;
		int flatDmg = 0;

	public:
		// Constructors
		Item();
		Item(const std::string& name,
				const string& description,
				const int price,
				const string itemtype,
				const int rarity,
				const int healAmount,
				const int attackBonus,
				const int defBonus,
				const int flatDmg);
		Item(const std::string& name,
				const string& description,
				const int price,
				const string itemtype,
				const int rarity,
				const int healAmount,
				const int attackBonus,
				const int defBonus,
				const int numDice,
				const int diceSides,
				const int flatDmg);
		// Getters
		string getName() const;
		string getDescription() const;
		int getPrice() const;
		string getItemType() const;
		int getRarity() const;
		int getHealAmount() const;
		int getAttackBonus() const;
		int getDefBonus() const;
		int getDamage() const;
		int getNumDice() const;
		int getDiceSides() const;
		// Setters
		void setName(const string& newName);
		void setDescription(const string& newDescription);
		void setPrice(int newPrice);
		void setRarity(int newRarity);
		void setHealAmount(int newHealAmount);
		void setAttackBonus(int newAttackBonus);
		void setDefBonus(int newDefBonus);
		// Behavior
		int rollDamage() const;
};

#endif
