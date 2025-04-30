#include "rng.h"
#include <iostream>
#include <limits>
#ifdef _WIN32
	#include <conio.h>
#else
	#include <cstdio>
#endif

std::mt19937 rng{ std:: random_device{}() }; // seed once
std::uniform_int_distribution<> d20 (1, 20); // construct once
std::uniform_int_distribution<> d6 (1, 6); // construct once
std::uniform_int_distribution<> d8 (1, 8); // construct once
std::uniform_int_distribution<> d10 (1, 10); // construct once

bool coinFlip()
{
	static std::bernoulli_distribution flip(0.5);
	return flip(rng);
}

void pressAnyKey()
{
	std::cout << "\nPress enter to continue..." << std::flush;
#ifdef _WIN32
	_getch(); // Waits for a single keypress, no need to hit enter
#else
	// Linux / MacOS
	// Eat the pending newline left in the input buffer
	if (std::cin.rdbuf()->in_avail() > 0)
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	// getchar() blocks until one key is pressed
	std::cin.get();
#endif
}
