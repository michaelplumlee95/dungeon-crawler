#include "ItemLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;


vector<Item> loadItemsFromCSV(const string& filename)
{
	vector<Item> items;
	ifstream file(filename);

	if (!file.is_open())
	{
		cout << "Error: Could not open item file!" << endl;
		return items; // return empty if couldn't open item file
	}
	
	string line;
	bool firstline = true;
	while (getline(file, line))
	{
		if (firstline)
		{
			firstline = false;
			continue;
		}
		if (line.empty()) continue; //skip empty lines

		stringstream ss(line);
		string name,
			   description,
			   priceStr,
			   itemtype,
			   rarityStr,
			   healAmountStr,
			   attackBonusStr,
			   defBonusStr,
			   damageStr; // read in ints as strings to start

		// parse the CSVs
		if (getline(ss, name, ',') && getline(ss, description, ',') && getline(ss, priceStr, ',') && getline(ss, itemtype, ',') &&
				getline(ss, rarityStr, ',') && getline(ss, healAmountStr, ',') && getline(ss, attackBonusStr, ',') && 
				getline(ss, defBonusStr, ',') && getline(ss, damageStr, ',')) 
		{
			int price = stoi(priceStr);
			int rarity = stoi(rarityStr);
			int healAmount = stoi(healAmountStr);
			int attackBonus = stoi(attackBonusStr);
			int defBonus = stoi(defBonusStr);
			int numDice   = 0;
			int diceSides = 0;
			int flatDmg   = 0;

			if (damageStr.find('d') != string::npos) {          // "2d6" style
				size_t dPos = damageStr.find('d');
				string left  = damageStr.substr(0, dPos);
				string right = damageStr.substr(dPos + 1);

				numDice   = left.empty()  ? 1 : stoi(left);     // allow "d8" == 1d8
				diceSides = stoi(right);
			} else {                                                 // plain number
				flatDmg = stoi(damageStr);
			};

			// Construct Item object with parsed data
			Item newItem(name, description, price, itemtype, rarity, healAmount, attackBonus, defBonus, numDice, diceSides, flatDmg);
			items.push_back(newItem);
		}
	}
	file.close();
	return items;
}
