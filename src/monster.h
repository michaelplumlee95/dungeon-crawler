#ifndef BEASTIARY_H
#define BEASTIARY_H

#include <string>

class Monster {
	private:
		std::string name;
		int HP;
		int atkBonus;
		int AC;
		int gold;
		int minSpawnDepth;     // Earliest floor it can appear
		int spawnWeight;       // How likely it is to appear
		int numDice = 0;
		int diceSides = 0;
		int flatDmg = 0;
		std::string asciiArt;
		std::string bio;
	public:
		// Constructor
		Monster(const std::string& name,
				int HP,
				int atkBonus,
				int AC,
				int gold,
				int minSpawnDepth,
				int spawnWeight,
				int diceCount = 0,
				int diceSides = 0,
				int flatBonus = 0,
				const std::string& asciiArt = "",
				const std::string& bio = "");
		// Getter functions
		const std::string& getName() const;
		int getHP() const;
		int getAtkBonus() const;
		int getAC() const;
		int getGold() const;
		int getMinSpawnDepth() const;
		int getSpawnWeight() const;
		int getDamageRoll() const;
		const std::string& getAscii() const { return asciiArt; };
		const std::string& getBio() const { return bio; }
		// Behavior
		int attackRoll();
		void takeDmg(int amount);
		bool isAlive() const;
		int rollDamage() const;
	};

#endif
