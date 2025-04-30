#include "items.h"
#include <iostream>
#include "ItemLoader.h"
#include "player.h"

using namespace std;

int main()
{
	Player p("TestPlayer", 50, 10, 2);
	cout << "Created player. HP " << p.getHP() << "/" << p.getMaxHP() << endl;

	// Add test items to the players inventory
	Item potion("Potion", "Heals 10 HP", 5, "consumable", 1,10,0,0);
	Item sword("Sword", "Basic sword", 15, "weapon", 1,0,3,0);
	Item leatherArmour("Leather Armour", "Armour made from cowhide", 10, "armour", 1,0,0,2);

	// Simulate looting
	p.useItem("Potion"); // Should say don't have
	p.addItemToInventory(potion);
	p.addItemToInventory(sword);

	// Let's check Item equipping
	vector<Item> temp ={ potion, sword, leatherArmour };
	for (Item& i : temp)
		p.equipWeapon(i.getName());

	// Add items to inventory for use
	p.useItem("Potion"); // This should pass since it is now in the inventory.
	cout << "\n -- Testing Combat Stats -- " << endl;
	cout << "Atk Bonus: " << p.getAtkBonus() << endl;
	cout << "AC: " << p.getArmourClass() << endl;

	return 0;
}
