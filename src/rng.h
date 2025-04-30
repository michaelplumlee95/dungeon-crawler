#pragma once
#include <random>
#include <iostream>
#include <chrono>
#include <thread>

extern std::mt19937 rng;
extern std::uniform_int_distribution<> d20;
extern std::uniform_int_distribution<> d6;
extern std::uniform_int_distribution<> d8;
extern std::uniform_int_distribution<> d10;

// 5050 logic
bool coinFlip();

// clearscreen functionality

inline void clearScreen()
{
#ifdef _WIN32           // Windows terminal
    std::system("cls");
#else                   // Linux / macOS / WSL
    // Faster/safer than system("clear"):
    std::cout << "\033[2J\033[H" << std::flush;   // ANSI “erase + home”
#endif
}

inline void turnDelay(std::chrono::milliseconds ms = std::chrono::milliseconds{500})
{
	std::this_thread::sleep_for(ms);
}

// pressAnyKey pause functionality
void pressAnyKey();
