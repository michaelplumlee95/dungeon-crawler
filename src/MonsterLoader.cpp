#include "MonsterLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

vector<Monster> loadMonstersFromCSV(const string& filename)
{
	vector<Monster> monsters;
	ifstream file(filename);

	if (!file.is_open())
	{
		cout << "Error: Could not open Monsters file!" << endl;
		return monsters; // return empty if file couldn't be opened.
	}

	string line;
	bool firstline = true; // this is for skipping the header of the csv
	while (getline(file,line))
	{
		if (firstline)
		{
			firstline = false;
			continue;
		}
		if (line.empty()) continue; // skip empty lines if they exist

		stringstream ss(line);
		string name,
			   HPstr,
			   atkBonusstr,
			   ACstr,
			   goldstr,
			   minSpawnDepthstr,
			   damageRollstr,
			   spawnWeightstr, // read in everything as a string, then convert values down below
			   asciiPath,
			   bio;				// Bio sits directly in csv

		// parse the CSVs
		if (getline(ss, name, ',') &&
			getline(ss, HPstr, ',') &&
			getline(ss, atkBonusstr, ',') &&
			getline(ss, ACstr, ',') &&
			getline(ss, goldstr, ',') &&
			getline(ss, minSpawnDepthstr, ',') &&
			getline(ss, spawnWeightstr, ',') &&
			getline(ss, damageRollstr, ',') &&
			getline(ss, asciiPath, ',') &&
			getline(ss, bio))
		{
			int HP = stoi(HPstr);
			int atkBonus = stoi(atkBonusstr);
			int AC = stoi(ACstr);
			int gold = stoi(goldstr);
			int minSpawnDepth = stoi(minSpawnDepthstr);
			int spawnWeight = stoi(spawnWeightstr);
			int numDice = 0;
			int diceSides = 0;
			int flatDmg = 0;

			// parse dice notation from csv
			if (damageRollstr.empty() || damageRollstr == "0")
			{
				// leave it, monster does no bonus damage
			}
			else if (damageRollstr.find('d') != string::npos)
			{
				size_t dPos = damageRollstr.find('d');
				string left = damageRollstr.substr(0,dPos);
				string right = damageRollstr.substr(dPos + 1);

				numDice = left.empty() ? 1: stoi(left); // d8 = 1d8
				diceSides = stoi(right);
			}
			else
			{
				flatDmg = stoi(damageRollstr);
			}

			string art;
			if (!asciiPath.empty())
			{
				ifstream afile(asciiPath);
				art.assign(istreambuf_iterator<char>(afile),
						istreambuf_iterator<char>());
			}
			// Construct Monster object with parsed data
			Monster newMonster(name, HP, atkBonus, AC, gold, minSpawnDepth, spawnWeight, numDice, diceSides, flatDmg, art, bio);
			monsters.push_back(newMonster);
		}
	}
	file.close();
	return monsters;
}
