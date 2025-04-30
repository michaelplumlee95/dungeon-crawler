#include "shop.h"
#include <algorithm>
#include <iostream>
#include <limits>

Shop::Shop(const std::vector<Item>& allItems, int rarity)
{
	std::vector<Item> pool;
	std::copy_if(allItems.begin(), allItems.end(), std::back_inserter(pool),
			[rarity](const Item& i){ return i.getRarity() == rarity;  });

	std::shuffle(pool.begin(), pool.end(), rng); // shuffles the item order
	for (int i = 0; i < 5 && i < static_cast<int>(pool.size()); i++)
		stock.push_back(pool[i]);
}

void Shop::show(const Player& p) const
{
	std::cout << "\n=== SHOP (Gold: " << p.getGold() << ") ===\n";
	for (std::size_t i = 0; i < stock.size(); i++)
	{
		std::cout << i+1 << "." << stock[i].getName()
			<< " - " << stock[i].getPrice() << "g\n";
	}
	std::cout << "0. leave\n";
}

void Shop::enter(Player& p)
{
	while (true) 
	{
		show(p);
		int choice; std::cout << "> "; std::cin >> choice;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear newline from buffer
		if (choice == 0) break;
		if (choice < 1 || choice > static_cast<int>(stock.size()))
		{std::cout << "?!\nThat doesn't make any sense lad. Try again.\n"; continue; }
		Item item = stock[choice-1];
		if (p.getGold() < item.getPrice()) { std::cout << "Not enough cheddar for that lad.\nTry Again.\n"; continue; }

		p. addItemToInventory(item);
		p.spendGold(item.getPrice());
		std::cout << "Bought " << item.getName() <<"!\n";
	}
}
