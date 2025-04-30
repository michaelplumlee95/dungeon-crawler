#ifndef ITEMLOADER_H
#define ITEMLOADER_H

#include <vector>
#include "items.h"

std::vector<Item> loadItemsFromCSV(const std::string& filename);

#endif
