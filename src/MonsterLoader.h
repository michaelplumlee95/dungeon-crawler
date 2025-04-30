#ifndef MONSTERLOADER_H
#define ITEMLOADER_H

#include <vector>
#include "monster.h"

std::vector<Monster> loadMonstersFromCSV(const std::string& filename);

#endif
