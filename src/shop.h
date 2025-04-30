#ifndef SHOP_H
#define SHOP_H

#pragma once
#include <vector>
#include "items.h"
#include "player.h"
#include "rng.h"

class Shop {
	std::vector<Item> stock;
private:
void show(const Player& p) const;
public:
	Shop(const std::vector<Item>& allItems, int rarity);
	void enter(Player& p);
};
#endif
