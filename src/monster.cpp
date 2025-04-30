#include "monster.h"
#include "rng.h"

// Constructor
Monster::Monster(const std::string& name,
		int HP,
		int atkBonus,
		int AC,
		int gold,
		int minSpawnDepth,
		int spawnWeight,
		int diceCount,
		int diceSides,
		int flatDmg,
		const std::string& asciiArt,
		const std::string& bio)
	: name(name),
	HP(HP),
	atkBonus(atkBonus),
	AC(AC),
	gold(gold),
	minSpawnDepth(minSpawnDepth),
	spawnWeight(spawnWeight),
	numDice(diceCount),
	diceSides(diceSides),
	flatDmg(flatDmg),
	asciiArt(asciiArt),
	bio(bio)
{}

// Getters
const std::string& Monster::getName() const
{
	return name;
}
int Monster::getHP() const
{
	return HP;
}
int Monster::getAtkBonus() const
{
	return atkBonus;
}

int Monster::getAC() const
{
	return AC;
}
int Monster::getGold() const
{
	return gold;
}
int Monster::getMinSpawnDepth() const
{
	return minSpawnDepth;
}
int Monster::getSpawnWeight() const
{
	return spawnWeight;
}
int Monster::getDamageRoll() const
{
	return rollDamage();
}

// Behavior
int Monster::attackRoll()
{
	int roll = d20(rng);
	return roll + Monster::getAtkBonus();
}
void Monster::takeDmg(int amount)
{
	HP -= amount;
}
bool Monster::isAlive() const
{
	return HP > 0;
}

int Monster::rollDamage() const
{
	if (diceSides == 0) return flatDmg; // handles nonrandom damage type

	std::uniform_int_distribution<> dist(1, diceSides);
	int total = 0;
	for (int i = 0; i < numDice; i++)
		total += dist(rng);
	return total + flatDmg;
}
