#include "rng.h"
#include "player.h"
#include "items.h"
#include "ItemLoader.h"
#include "monster.h"
#include "MonsterLoader.h"
#include "room.h"
#include "shop.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;
void printMenuScreen();
void toLower(string& s);
Monster spawnMonster(int currentDepth, const vector<Monster>& prototypes);
string readCommand(const std::string &prompt = "> "); 
Item spawnItem(int rarity, const vector<Item>& prototypes);
int rarityForDepth(int depth);
void printIntro();
void printDeath();
void printCredits();
void typeWrite(const std::string& text, unsigned int delayMs);

enum GameState 
{
	MAIN_MENU,
	IN_GAME,
	GAME_OVER,
	QUIT
};

int main()
{
	GameState currentState = MAIN_MENU;
	bool running = true;
	auto allItems = loadItemsFromCSV("data/item_data.csv");
	vector<Monster> allMonsters = loadMonstersFromCSV("data/monster_list.csv");
	Player player("Bob", 5, 14, 1);
	int currentDepth = 0;

	// add a potion to the players inventory
	for (const Item& i : allItems) 
	{
		if (i.getName() == "mace")
		{
			player.addItemToInventory(i);
			break;
		}
	}

	while (running)
	{
		switch(currentState)
		{
			case MAIN_MENU:
				{
					clearScreen();
					printMenuScreen();
					cout << "====Main Menu====" << endl;
					cout << "1. Start Game\n2. Quit\n";
					string cmd = readCommand("What would you like to do?\n> ");

					if (cmd == "1") 
					{
						currentState = IN_GAME;
						currentDepth = 0; // reset dungeon depth incase of replay
					}
					else
					{
						currentState = QUIT;
					}
					break;
				}

			case IN_GAME:
				// *** INSERT LORE FUNCTIONS HERE TO PRINT AFTER GAME START ***
				printIntro();
				while (running && player.isAlive())
				{
					clearScreen();
					bool inCombat = false;
					// Generate a new room
					currentDepth++;
					Room room = room.generateRoom();
					if (currentDepth % 5 == 0)
					{
						room.setisMonster(false);
						room.setisTreasure(false);
						room.setisShop(true);
						int r = rarityForDepth(currentDepth);
						Shop shop( allItems, r);
						shop.enter(player);
					}

					// If there is a monster in this room, enter combat
					if (room.getisMonster())
					{
						cout << "You found a monster! Now you must fight\n";
						pressAnyKey();
						clearScreen();
						Monster badguy = spawnMonster(currentDepth, allMonsters);
						inCombat = true;

						while (inCombat == true && player.isAlive() && badguy.isAlive())
						{
							clearScreen();
							// Show status for the player
							cout << "Player HP: " << player.getHP() << "/" << player.getMaxHP() << endl;
							cout << "Monster: " << badguy.getName() << " HP: " << badguy.getHP() << endl;

							// Prompt for combat commands only
							string cmd = readCommand("What would you like to do? (attack, examine, use <item>, inventory)\n> ");
							if (cmd == "attack")
							{
								if (player.attackRoll() > badguy.getAC())
								{
									int damageRoll = player.damageRoll();
									badguy.takeDmg(damageRoll);
									cout << "You hit " << badguy.getName() << "for " << damageRoll << " damage!\n"; 
								}
								else 
								{
									cout << "You missed!\n";
								}
							}
// 							else if (cmd == "flee")
// 							{
// 								if (player.attemptFlee())
// 								{
// 									cout << "You escape!\n";
// 									inCombat = false;
// 									break;
// 								}
// 								else
// 								{
// 									cout << "You couldn't get away!\n";
// 								}
// 							}
							else if (cmd.rfind("use ", 0) == 0)
							{
								//strip off the use prefix
								string item = cmd.substr(4);
								player.useItem(item);
							}
							else if (cmd == "inventory")
							{
								clearScreen();
								cout << "Inventory:\n";
								cout << "=======================================" << endl;
								for (Item it : player.getPlayerInventory())
								{
									cout << it.getName() << endl;
								}
								pressAnyKey();
								continue; // reprompt without going to monster turn
							}
							else if (cmd == "examine")
							{
								cout << badguy.getAscii() << endl;
								typeWrite(badguy.getBio(), 30);
								cout << '\n' << '\n';
								pressAnyKey();
								continue;
							}
							else
							{
								cout << "Invalid command! Try: attack, use <item>, or examine.\n";
								continue; // reprompt without going to monsters turn
							}
							turnDelay();

							// Check for victory
							if (!badguy.isAlive())
							{
								cout << "You defeated the " << badguy.getName() << "!\n";
								player.addGold(badguy.getGold());
								inCombat = false;
								room.setisMonster(false);
								break;
							}

							// Monster Turn
							if (badguy.attackRoll() > player.getArmourClass())
							{
								int mdmg = badguy.getDamageRoll();
								player.takeDmg(mdmg);
								cout << '\n' << "You take " << mdmg << " damage!\n";
							}
							else
							{
								cout << '\n' << badguy.getName() << " misses!\n";
							}
							turnDelay();
							turnDelay();
							turnDelay();
							// Check for defeat if (!player.isAlive())
							if (!player.isAlive())
							{
								clearScreen();
								typeWrite("Uh Oh... You died!\n", 15);
								pressAnyKey();
								currentState = GAME_OVER;
								break;
							}

						}
					}
					else		// if the room doesn't have a monster:
					{
						room.describe();
					}
					// No monster -> allow exploration commands
					while (player.isAlive())
					{
						string cmd = readCommand("What would you like to do?\n(describe / clear / equip <item> / explore / inventory / loot / status / quit)\n> ");
						if (cmd == "describe")
						{
							room.describe();
						}
						else if (cmd == "clear")
						{
							clearScreen();
							continue;
						}
						else if (cmd == "inventory")
						{
							cout << "Inventory:\n";
							cout << "=======================================" << endl;
							for (Item it : player.getPlayerInventory())
							{
								cout << it.getName() << endl;
							}
						}
						else if (cmd == "status")
						{
							player.showStatus();
						}
						else if (cmd.rfind("equip ", 0) == 0)
						{
							//strip off the use prefix
							string item = cmd.substr(6);
							player.equipItem(item);
						}
						else if (cmd == "quit")
						{
							running = false;
							currentState = QUIT;
							break;
						}
						else if (cmd == "explore")
						{
							break;	// break out of the loop and go to the next room
						}
						else if (cmd == "loot")
						{
							// add a random item to the players inventory
							if (room.getisTreasure())
							{
								Item treasure = spawnItem(2, allItems);
								cout << "You found a " << treasure.getName() <<"!\n";
								player.addItemToInventory(treasure);
								room.setisTreasure(false);
								continue;
							}
							else
							{
								cout << "There isn't anything to loot here!\n";
							}
						}
						else
						{
							cout << "Not a valid command! Try explore, inventory, status, quit\n";
						}
					}

			}
				break;
			case GAME_OVER:
				{
					clearScreen();
					printDeath();
					string cmd = readCommand("Game over!\nPress 1 for main menu and press 2 to quit!\n> ");
					if (cmd == "1")
					{
						player = Player("Bob", 25, 14, 1); // reset the player object
						running = true;
						currentState = MAIN_MENU;
					}
					else
					{
						currentState = QUIT;
					};
				}
				break;

			case QUIT:
				printCredits();
				running = false;
				cout << '\n';
				cout << '\n';
				pressAnyKey();
				break;
		}
	}
}

void printMenuScreen()
{
	cout << R"(
▄▄▄█████▓ ██░ ██ ▓█████    ▓█████▄  █    ██  ███▄    █   ▄████ ▓█████  ▒█████   ███▄    █
▓  ██▒ ▓▒▓██░ ██▒▓█   ▀    ▒██▀ ██▌ ██  ▓██▒ ██ ▀█   █  ██▒ ▀█▒▓█   ▀ ▒██▒  ██▒ ██ ▀█   █
▒ ▓██░ ▒░▒██▀▀██░▒███      ░██   █▌▓██  ▒██░▓██  ▀█ ██▒▒██░▄▄▄░▒███   ▒██░  ██▒▓██  ▀█ ██▒
░ ▓██▓ ░ ░▓█ ░██ ▒▓█  ▄    ░▓█▄   ▌▓▓█  ░██░▓██▒  ▐▌██▒░▓█  ██▓▒▓█  ▄ ▒██   ██░▓██▒  ▐▌██▒
  ▒██▒ ░ ░▓█▒░██▓░▒████▒   ░▒████▓ ▒▒█████▓ ▒██░   ▓██░░▒▓███▀▒░▒████▒░ ████▓▒░▒██░   ▓██░
  ▒ ░░    ▒ ░░▒░▒░░ ▒░ ░    ▒▒▓  ▒ ░▒▓▒ ▒ ▒ ░ ▒░   ▒ ▒  ░▒   ▒ ░░ ▒░ ░░ ▒░▒░▒░ ░ ▒░   ▒ ▒
    ░     ▒ ░▒░ ░ ░ ░  ░    ░ ▒  ▒ ░░▒░ ░ ░ ░ ░░   ░ ▒░  ░   ░  ░ ░  ░  ░ ▒ ▒░ ░ ░░   ░ ▒░
  ░       ░  ░░ ░   ░       ░ ░  ░  ░░░ ░ ░    ░   ░ ░ ░ ░   ░    ░   ░ ░ ░ ▒     ░   ░ ░
          ░  ░  ░   ░  ░      ░       ░              ░       ░    ░  ░    ░ ░           ░
                            ░                                                             )" << endl << endl;
}

void toLower(string& s)				// normalizes inputs to lowercase
{
    std::transform(
      s.begin(), 
      s.end(), 
      s.begin(),
      [](unsigned char c) -> char { 
          return static_cast<char>(std::tolower(c)); 
      }
    );
}
Monster spawnMonster(int currentDepth, const vector<Monster>& prototypes)
{
	// Collect pointers that point at eligible prototypes for spawn conditions
	vector<const Monster*> pool;
	for (const auto& m : prototypes)
	{
		if (m.getMinSpawnDepth() <= currentDepth)
		{
			pool.push_back(&m);
		}
	}
	if (pool.empty())
	{
		cout << "There are no appropriate monsters for this depth!\n";
	}

	// Pick one of the eligible monsters at random
	int idx = (d20(rng) - 1) % static_cast<int>(pool.size());
	return *pool[idx]; // This is the line that ensures you get a copy of the monster, and are not fighting monsters in the
					  // prototype list
}
Item spawnItem(int rarity, const vector<Item>& prototypes)
{
	// Collect pointers that point at eligible prototypes for spawn conditions
	vector<const Item*> pool;
	for (const auto& i : prototypes)
	{
		if (i.getRarity() <= rarity)
		{
			pool.push_back(&i);
		}
	}
	if (pool.empty())
	{
		cout << "There are no appropriate items for this rarity!\n";
	}

	// Pick one of the eligible monsters at random
	int idx = (d20(rng) - 1) % static_cast<int>(pool.size());
	return *pool[idx]; // This is the line that ensures you get a copy of the item
}

string readCommand(const std::string &prompt) 
{
    cout << prompt;
    string input;
    getline(std::cin, input);
    toLower(input);
    return input;
}
int rarityForDepth(int depth)
{
	if (depth < 10) return 1; //common
	if (depth < 20) return 2; //common
	return 3; //common
}
void printIntro()
{
	clearScreen();
	typeWrite("Arise! Arise, my glorious skeletal champion! Crafted from the finest bones I could... eh, find lying around. Welcome back to the land of the living-sort of.", 30);
	pressAnyKey();
	clearScreen();
	typeWrite("Right, introductions. I'm Johnny. Necromancer. Genius. Sufferer of mild-to-severe monster phobia. I may have dropped my Necronomicon in that cursed dungeon over there, and—well—I’m not going back in there. Too many teeth. Too many eyes. Some of them not even attached to anything!", 30);
	pressAnyKey();
	clearScreen();
	typeWrite("So! You’re going in instead. Retrieve my precious book, try not to die too often, and I’ll keep an eye on you from the safety of my totally not monster-infested tower. Oh, and don’t worry—I can talk directly into your skull. No pressure, champ!", 30);
	pressAnyKey();
	clearScreen();
	typeWrite("Now, march your rattling self into that dungeon, fetch my Necronomicon, and try not to get smashed, squished, scorched, or soul-nibbled. I'll be watching from up here-cheering you on! Spiritually. From a safe distance. Preferably with snacks.", 30);
	typeWrite("Go forth, my bony champion!", 30);
	pressAnyKey();
}

void printDeath()
{
    cout << R"(
          ▄████  ▄▄▄       ███▄ ▄███▓▓█████     ▒█████   ██▒   █▓▓█████  ██▀███
         ██▒ ▀█▒▒████▄    ▓██▒▀█▀ ██▒▓█   ▀    ▒██▒  ██▒▓██░   █▒▓█   ▀ ▓██ ▒ ██▒
        ▒██░▄▄▄░▒██  ▀█▄  ▓██    ▓██░▒███      ▒██░  ██▒ ▓██  █▒░▒███   ▓██ ░▄█ ▒
        ░▓█  ██▓░██▄▄▄▄██ ▒██    ▒██ ▒▓█  ▄    ▒██   ██░  ▒██ █░░▒▓█  ▄ ▒██▀▀█▄
        ░▒▓███▀▒ ▓█   ▓██▒▒██▒   ░██▒░▒████▒   ░ ████▓▒░   ▒▀█░  ░▒████▒░██▓ ▒██▒
         ░▒   ▒  ▒▒   ▓▒█░░ ▒░   ░  ░░░ ▒░ ░   ░ ▒░▒░▒░    ░ ▐░  ░░ ▒░ ░░ ▒▓ ░▒▓░
          ░   ░   ▒   ▒▒ ░░  ░      ░ ░ ░  ░     ░ ▒ ▒░    ░ ░░   ░ ░  ░  ░▒ ░ ▒░
        ░ ░   ░   ░   ▒   ░      ░      ░      ░ ░ ░ ▒       ░░     ░     ░░   ░
              ░       ░  ░       ░      ░  ░       ░ ░        ░     ░  ░   ░
                                                             ░
                                           ........
                             .....                          ......
                        ....                                     ......
                     ...                                           .....:.
                 ....                                               ......:::.
              .......                                             .........:::::
            .:............                                    .............:::::-:
          .:::::................                          ...............:::::::---:
         :::---:::...................            ..   ................:::::::::------.
        :::---=--::.............................   ...............:::::::::::--====---:
       ::::-===+=::..............     .......   .........    ........::::::---=====--==.
      :::::==+++=:......           ...... .   ...:..   .................::::--=+++=====-
     .--::--+++=...      .......     ...:   ::..::.....       .............::-=+*++=====
     .-----==-:....::--==========----::::   -------:::::::::---=========--::..:-+*+====+.
     .=---=-..:-=+*#%%%%@@@@@@@@%%#*+++====   ===========++*%%%@@@@%%%%%%%#*+=-:-=++==++:
     .=====--=+*%@%%%%%%%%%%%@@@@@@@%*+++==-   ---==++++*%@@@%%%%%%%%%%%%%%%%#+==+++++++:
     .===++===*%%%%%%%%%%%%%%%%%%%%%%%+=-::..:   .::-==+%%%%%%%%%%%%%%%%%%%%%%#=-=**++++.
      -+++=-:-#%%%%%%%%%%%%%%%%%%%%%%%*:::. .:.   ..:--+%%%%%%%%%%%%%%%##%%%%%%=:-+*+++=
      :+++=-::#%%%#############%%%%%%%=..:+@@@@@   *::-=%%%%%%%%#############%%=:-=+**+:
      .=++=-:.+#######***##########%#-..:+%@@@@@@*   :.:=#%%%#######******#####-:-=+**-
       .*+--:::+###***********####+:...-%@@@@@@@@@#-   ..:-+#####***********##=:-==+*-
        --:::::.:=****+++++++=:.......-#@@%%%@%%%%%+:.   ......-=++++++++++=::---====.
      :=-:::::::::....................+%%%%%%@%###%#-:::   :::::::::..:::::-------====.
       =+-----:::::::::::=*#*=-.......=#####%#%#****-::   :::-=#%%%*=-::::--------==+.
        .=+==-------==++++*%%%+:.......-=++=---=++--:   :::::+%%**++++++=========++:
            .::=###%%%%%%#+--=:.....  ......::...:.   ....:::-=+++**##%%#####+:..
                *#*##%%%%%*=:::...    ..    ::      .......:::-=+*%%%%%%%##*.
                -*++*%%%%#+-::.:::--::--==----   -==-----=-:---==*%%%%%%*++-
                 ++=+#%%%#*++-:++.  :*+.      -#=.  .=*: .-+=-=++*#%%%%#==-
                 -=--*####+==:.=:.  .*:.      .*:   .:=:..:=-:-==*#%%##=-=.
                 :==:=*####%%##%%+==+#      +----=#*----+##+++#*=++*#%%##+-==
                 :==::=+####%%%%@@@@   @@@@@@@@@@@@@@@@@@@@@%%%#####*=--+=
                 -==-::--+=-=#%%%%%%%   %%%%%%%%%%%%%%%%%%%%##*=-++==-:=+=
                 ====-:--::=-:-:-=-=+##   ##%%#%%%####%%#**+::-=====-:-+++.
                 :=+==-:-==--==-==:.-+:.:   =:..--...:-=::-=-=+==++=--=+++.
                  .=+==---=====--:---=-:==-   :-++-::-=+=-=--==+++=-=++++.
                    .=+=---===========----::-   ---::-====+++++++===++=.
                      .=+=-----====--=---------   ---========+====++-
                        .=+=-----------::::::::::   ------======++-
                          .=+=-::::::::.........   .::::-----==+:
                            .===-::::.........   .....:::--=++:
                               :+==--:::::::   ::::::::--=+=.
                                  .-++++==   =========++=.                                   )" << endl << endl;
string outro[] = 
	{
		R"(
	"Well... that was a mess. Something hit you, or bit you, or maybe just looked at you funny. Either way—you’re dead. Again."
	"I can patch you up and toss you back in, if you’re feeling brave.
	Or I can summon someone new. Up to you, bones.")",
	R"(
	"Oof. That went about as well as a wet fireball scroll. You crumbled
	like stale bread in a windstorm."
	"Want another go? I can bring you back—same bones, new regrets. Or
	I can try raising a slightly smarter skeleton. Your call.")",
	R"(
	"And down you go! Collapsed in a heap like a spooky lawn ornament.
	Impressive, in a ‘please never do that again’ kind of way."
	"I can revive you, if you're into that whole 'unfinished business'
	vibe. Or I could just summon a replacement. Less work for me.")",
	R"(
	"Well, that escalated... poorly. Whatever happened in there, it
	clearly involved some screaming and regrettable choices."
	"Want to try again? I’ll fix you up, throw you back in. Or we cut
	our losses and I conjure someone less breakable.")",
	R"(
	"Aaand you're dead. Again. You're really making skeletons look
	bad here, y’know."
	"But hey—I’m generous. I can bring you back. Or, if you’d rather
	call it a day, I’ll just animate the next unlucky soul. Deal?")"
	};
	//cout << outro[d20(rng)%5] << endl << endl;
	typeWrite(outro[d20(rng)%5],30);
}

void printCredits()
{
    string credits = R"(
"See you next time Bone-Brains!"

Credits:

Tylar Wolff: Master of world creation, map design and generation, resident Dungeon Builder

Madelyn Kempka: Empress of Shopkeeping, shop designer, resident merchant

Ethan Jackson: Godfather of monsters, lore, and art, resident monster summoner

Michael Plumlee: Overlord of the Dungeon, item designer and the one to put the
code together, only CS major, resident Blacksmith

ChatGPT: Chief of assistance, provided assistance when needed, created Johnny
ASCII Art, resident Dungeon Ghost

                    Thanks for playing!

                  ___====-_  _-====___
             _--^^^#####//      \\#####^^^--_
          _-^##########// (    ) \\##########^-_
         -############//  |\^^/|  \\############-
       _/############//   (@::@)   \\############\_
      /#############((     \\//     ))#############\
     -###############\\    (oo)    //###############-
    -#################\\  / UUU \  //#################-
   -###################\\/  (   )  \//###################-
  _/####################/  (     )  \####################\_
 /#####################(   (       )   )#####################\
-######################\   \     /   /######################-
-########################\   \   /   /########################-
-#########################\   | |   /#########################-
-##########################\  | |  /##########################-
 -##########################\| |/##########################-
  -###########################/###########################-
   -##########################/##########################-
    -########################/##########################-
      -####################/##########################-
        -##############/############################-
           -######/#############################-
              -/#############################-)";
typeWrite(credits, 30);
}

void typeWrite(const std::string& text, unsigned int delayMs)
{
    using namespace std::chrono_literals;               // for 30ms syntax
    // Make sure output shows up immediately.
    std::cout << std::flush;

    for (char ch : text)
    {
        std::cout << ch << std::flush;                  // print + flush
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
}
