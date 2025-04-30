#include "items.h"
#include "rng.h"

using namespace std;

Item::Item()
	: name("potion"), description("Heals 10 HP"), price(10), itemtype("consumable"), healAmount(5), attackBonus(0), defBonus(0)
	{

	}

Item::Item(const string& name,
		const string& description,
		int price,
		const string itemtype,
		int rarity,
		int healAmount,
		int attackBonus,
		int defBonus,
		int flatDamage)
	: name(name),
	description(description),
	price(price),
	itemtype(itemtype),
	rarity(rarity),
	healAmount(healAmount),
	attackBonus(attackBonus),
	defBonus(defBonus),
	damage(flatDamage)
{

}
Item::Item(const string& name,
		const string& description,
		int price,
		const string itemtype,
		int rarity,
		int healAmount,
		int attackBonus,
		int defBonus,
		int diceCount,
		int diceSides,
		int flatBonus = 0)
	: name(name),
	description(description),
	price(price),
	itemtype(itemtype),
	rarity(rarity),
	healAmount(healAmount),
	attackBonus(attackBonus),
	defBonus(defBonus),
	numDice(diceCount),
	diceSides(diceSides),
	flatDmg(flatBonus)
{

}

// Getters
string Item::getName() const
{
	return name;
}

string Item::getDescription() const
{
	return description;
}

int Item::getPrice() const
{
	return price;
}

string Item::getItemType() const
{
	return itemtype;
}

int Item::getRarity() const
{
	return rarity;
}

int Item::getHealAmount() const
{
	return healAmount;
}

int Item::getAttackBonus() const
{
	return attackBonus;
}

int Item::getDefBonus() const
{
	return defBonus;
}

int Item:: getDamage() const
{
	return damage;
}
int Item:: getNumDice() const
{
	return numDice;
}
int Item:: getDiceSides() const
{
	return diceSides;
}

// Setters
void Item::setName(const string& newName)
{
	name = newName;
}
void Item::setDescription(const string& newDescription)
{
	description = newDescription;
}
void Item::setPrice(int newPrice)
{
	price = newPrice;
}

void Item::setRarity(int newRarity)
{
	rarity = newRarity;
}

void Item::setHealAmount(int newHealAmount)
{
	healAmount = newHealAmount;
}

void Item::setAttackBonus(int newAttackBonus)
{
	attackBonus = newAttackBonus;
}

void Item::setDefBonus(int newDefBonus)
{
	defBonus = newDefBonus;
}

int Item::rollDamage() const
{
	if (diceSides == 0) return flatDmg; // flat damage behaviour

	std::uniform_int_distribution<> dist(1, diceSides);
	int total = 0;
	for (int i = 0; i < numDice; i++)
		total += dist(rng);
	return total + flatDmg;
}
