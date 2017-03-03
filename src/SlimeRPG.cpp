#include "SlimeRPG.hpp"
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>
#include "location.hpp"
#include "monster.hpp"
#include "player.hpp"

// parses a command, returning true if the game should be terminated
static bool parseCommand(const std::string& cmd);

// commands
static bool help();
static bool stats();
static bool fight();
static bool flee();
static bool recover();
static bool journey();
static bool backtrack();
static bool leave();

void input(std::string& ref, const std::string& msg)
{
	std::cout << msg;
	std::getline(std::cin, ref);
}

void sleep(unsigned milliseconds)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void dotdotdot()
{
	std::cout << '.';
	sleep(1000);
	std::cout << '.';
	sleep(1000);
	std::cout << '.';
	sleep(1000);
	std::cout << '\n';
}

// the main player
Player player
{
	// format: nam, chp, mhp, lvl, exp, atk, def, xpt, loc
	"Nameless Hero", 10, 10, 1, 0, 5, 5, 10, 0
};

// pointer to the monster that the player is battling
Monster* encounterPtr{ nullptr };

// vector index for the encountered monster
uint8_t encounterIndex;

// list of monsters
std::vector<Monster> monsters
{
	// format: nam, chp, mhp, lvl, exp, atk, def, msg
	Monster
	{
		"Green Slime",
		5, 5, 1, 4, 3, 3,
		"A green Slime appeared!\n",
	},
	Monster
	{
		"Blue Slime",
		8, 8, 2, 6, 5, 5,
		"A blue Slime appears to avenge its little brother...\n",
	},
	Monster
	{
		"Red Slime",
		10, 10, 3, 8, 25, 0,
		"A Slime, red with fury, approaches you\n",
	},
	Monster
	{
		"Yellow Slime",
		16, 16, 4, 10, 3, 10,
		"A matured, yellow Slime confronts you\n",
	},
	Monster
	{
		"Ghost Slime",
		// good luck fighting THAT
		65535, 65535, 65535, 65535, 65535, 65535,
		"The ghost of your victims appears...\n",
	}
};

// list of locations
std::vector<Location> locations
{
	// format: nam, lvl, thr, msg, dth
	Location
	{
		"Slime Breeding Grounds", 1,
		{
			monsters[0], monsters[0], monsters[0]
		}, // 3 individual encounterable Green Slimes
		{ // messages randomly displayed when recovering.
			"Slimes, in their infancy, are green-colored, frolicking in the fields\n",
			"A bright green slime approaches you and asks, \"Mama?\"\n",
			"Some older green slimes seem to have a blue-ish tint to them\n"
		},
		{ // messages when you've killed every monster here
			"You don't see as much slimes here...\n",
			"Many slimes are living in fear now that their youthful generation is dead\n"
		}
	},
	Location // if you kill or injure a monster, it stays dead/injured.
	{        // so you can essentially fight it again when you recover.
		"Path of Slime", 2,
		{
			monsters[0], monsters[1], monsters[1]
		},
		{
			"You observe a group of blue-tinted green slimes mature into a complete blue\n",
			"Some younger green slimes follow their older blue friends, though still immature\n"
		},
		{
			"A golden flower seems to be judging you for your sins...\n",
			"A group of slimes seem to be talking about \"He\"...\n"
		}
	},
	Location
	{
		"Forest of Slime", 3,
		{
			monsters[2], monsters[2], monsters[2], monsters[1],
			monsters[0]
		},
		{
			"If a slime harbors anger for too long, it starts to acquire a red-ish tint\n",
			"An old rivalry of two slimes have turned them blood red with chronic hostility\n"
		},
		{
			"You observe a slime feeling triumphant now that its rival is dead for no reason\n",
			"It looks like that golden flower is talking to you...\n"
		}
	},
	Location
	{
		"Slime Boot Camp", 4,
		{
			monsters[3], monsters[3], monsters[3], monsters[3],
			monsters[2], monsters[1], monsters[1]
		},
		{
			"You observe matured yellow slimes training with some kind of slime weapon...\n",
			"It seems that blue slimes aren't actually mature, but more of a teenager\n"
		},
		{
			"A slime bullet flies past you. It seems that you are being hunted...\n",
			"You see a jar of peanut butter under a cardboard box held up by a stick\n"
		},
	},
	Location
	{
		"Slime Cemetery", 5,
		{
			monsters[4]
		},
		{
			"A funeral is taking place. You see dried slime being dumped into a grave\n",
			"How does a slime cry? I don't even know what I saw...\n",
			"Was that a ghost moaning just now?\n"
		},
		{
			"Wait you killed the ghost slime? Wow. Gg you dirty hacker...\n"
		}
	}
};

// list with corresponding locations, flagging them as still having monsters or not, for changing the recovery messages
std::vector<bool> death{ false, false, false, false, false };

// string to be used as the command input
std::string cmd;

// used to check if the player is battling, so the command loop will change the command options and whatever else
bool battling{ false };

int main()
{
	std::cout << "Loading...\n";
	dotdotdot();
	// initialize the rest of the player object
	
	// get player name to finish loading the game
	input(player.nam, "Done!\nWhat is your name?\n\n");
	std::cout << "\nType \"hlp\" for a list of commands\n";
	// command loop
	while (true)
	{
		// re-initialize random number generator to maximize randomness
		srand(time(NULL));
		// command input
		input(cmd, "\n");
		// line break for clarity
		std::cout << '\n';
		// parse the command
		if (parseCommand(cmd))
		{
			break;
		}
	}
	return 0;
}

bool parseCommand(const std::string& cmd)
{
	// if/elseif chain to identify command
	if (cmd == "hlp") // help
	{
		return help();
	}
	else if (cmd == "sts") // stats
	{
		return stats();
	}
	else if (cmd == "fgt") // fight
	{
		return fight();
	}
	else if (cmd == "fle") // flee
	{
		return flee();
	}
	else if (cmd == "rec") // recover
	{
		return recover();
	}
	else if (cmd == "jrn") // journey
	{
		return journey();
	}
	else if (cmd == "bkt") // backtrack
	{
		return backtrack();
	}
	else if (cmd == "lev") // leave
	{
		return leave();
	}
	std::cout << "Invalid command!\n";
	return false;
}

static bool help()
{
	if (battling) // battle help message
	{
		std::cout <<
			"hlp - Help.....List available commands\n"
			"sts - Stats....List the stats of your character and the monster\n"
			"fgt - Fight....*Chants* fite fite fite fite fite\n"
			"fle - Flee.....Only nubs flee, like you...\n";
	}
	else // regular help message
	{
		std::cout <<
			"hlp - Help........List available commands\n"
			"sts - Stats.......List the stats of your character\n"
			"rec - Recover.....Treat your wounds and rest, observing the scenery\n"
			"fgt - Fight.......Engage in battle with a nearby monster\n"
			"jrn - Journey.....Go forward to the next area\n"
			"bkt - Backtrack...Revisit the location you were just at\n"
			"lev - Leave.......Going so soon? Fine, but you can't save! >:D\n";
	}
	return false;
}

static bool stats()
{
	std::cout
		<< "nam..." << player.nam << '\n'
		<< "hp...." << player.chp << '/' << player.mhp << '\n'
		<< "lvl..." << player.lvl << '\n'
		<< "exp..." << player.exp << '\n'
		<< "xpt..." << player.xpt << '\n'
		<< "atk..." << player.atk << '\n'
		<< "def..." << player.def << '\n'
		<< "loc..." << locations[player.loc].nam << '\n';
	if (battling) // also lists monster stats if battling
	{
		std::cout
			<< "\nMonster\n"
			<< "nam..." << encounterPtr->nam << '\n'
			<< "hp...." << encounterPtr->chp << '/' <<
				encounterPtr->mhp << '\n'
			<< "lvl..." << encounterPtr->lvl
			<< (encounterPtr->lvl == 65535 ?
				"\nGetrekt nub\n" : "\n");
	}
	return false;
}

static bool fight()
{
	if (battling) // fights the monster if battling already
	{
		// player's turn
		// used in calculating damage
		uint16_t dmg{ 1 };
		// special roast flags
		bool playerInsulted{ false };
		bool monsterInsulted{ false };
		// current damage formula: dmg = player.atk - monster.def
		// checks if the dmg calculation would result in anything at most 1
		if (player.atk - encounterPtr->def <= 1)
		{
			// if so, damage stays at 1, and the monster reminds the player that they should gitgud
			std::cout << "You only did 1 damage...\n" << encounterPtr->nam << ": Gitgud nub >->\n";
				// that scrub just dissed you, man
			playerInsulted = true;
		}
		else // if not, then damage goes as normally. The program now needs to check if the damage would kill the monster
		{
			dmg = player.atk - encounterPtr->def;
				std::cout << "You did " << dmg << " damage to the slime!\n";
		}
		// checks if the damage would kill the monster
		if (dmg >= encounterPtr->chp)
		{
			// dead monster now, good riddance
			encounterPtr->chp = 0;
			// monster death message
			std::cout << "You mercilessly slaughtered the slime!\nYou feel like a terrible person...\n";
			// special dialogue for if the monster insulted you before
			if (playerInsulted)
			{
				std::cout << player.nam << ": Who's the nub now? >->\n";
			}
			// exp gain
			std::cout << "You gained " << encounterPtr->exp << " exp!\n";
			player.exp += encounterPtr->exp;
			// checks for levelup
			if (player.exp >= player.xpt)
			{
				std::cout << "You levelled up to level " << ++player.lvl << "!\n";
				// calculates next stats
				// xpt increases by 80%, other stats by 40%
				player.chp *= 1.4;
				player.mhp *= 1.4;
				player.exp -= player.xpt;
				player.xpt *= 1.8;
				player.atk *= 1.4;
				player.def *= 1.4;
				// compound interest formulas:
				// xpt = 10(1.8^(lvl-1))
				// hp = 10(1.4^(lvl-1))
				// atk/def = 5(1.4^(lvl-1))
			}
			// remove monster from location's thr vector
			locations[player.loc].thr.erase(locations[player.loc].thr.begin() + encounterIndex);
			// checks if the monster just deleted was the last
			if (locations[player.loc].thr.size() == 0)
			{
				// flags the location in the death list so recovery observations change
				death[player.loc] = true;
			}
			// the battle is now over
			battling = false;
			// no need to process the monster's next turn because it's already dead
			// jumps back to the top of the command loop
			return false;
		}
		else // monster survives the hit
		{
			// deducts damage from monster hp.
			encounterPtr->chp -= dmg;
		}
		dmg = 1;
		// now that you've taken your turn, it's the monster's turn now
		// be afraid, very afraid
		// checks if the dmg calculation would result in a negative number or 0
		if (encounterPtr->atk <= player.def)
		{
			// if so, damage stays as is, and the player reminds the monster that they should gitgud
			std::cout << "The " << encounterPtr->nam << " did only did 1 damage...\n" << player.nam << ": Gitgud scrub >->\n";
			// oooh you just dissed that monster
			monsterInsulted = true;
		}
		else // if not, then damage goes as normally, and the program now needs to check if the damage would kill the player
		{
			// if fighting ghost slime, the damage will be fixed to 65535
			dmg = (encounterPtr->lvl == 65535) ? 65535 : encounterPtr->atk - player.def;
			std::cout << encounterPtr->nam << " did " << dmg << " damage to you!\n";
		}
		// checks if the damage would kill the monster
		if (dmg >= player.chp)
		{
			// gg scrub
			player.chp = 0;
			// player death message
			std::cout << encounterPtr->nam << " has killed you! Looks like you got a taste of your own medicine...\n";
			// special dialogue for fighting ghost slime
			if (encounterPtr->lvl == 65535)
			{
				std::cout << "Gg scrub\n";
			}
			// special dialogue for if the player insulted it before
			if (monsterInsulted)
			{
				std::cout << encounterPtr->nam << ": Who's the scrub now? >->\n";
			}
			// line break for clarity
			std::cout << '\n';
			// terminates the command loop because you are dead
			return true;
		}
		else // lucky player survives the hit
		{
			// deducts damage from player hp
			player.chp -= dmg;
		}
	}
	else // if not already battling, attempt to initiate an encounter
	{
		std::cout << "You look around for a slime to fight\n";
		dotdotdot();
		// if death list has this location flagged, that indicates no more monsters will be present
		if (death[player.loc])
		{
			std::cout << "But no slimes appear, and you have a feeling that none ever will\nHe's coming for you. Run...\n";
		}
		else
		{
			// randomly select a monster from the current location's list of monsters
			encounterIndex = rand() % locations[player.loc].thr.size();
			// set encounterPtr to the randomly selected monster's address
			encounterPtr = &locations[player.loc].thr[encounterIndex];
			// plays the monster's encounter message
			std::cout << encounterPtr->msg;
			// set the current state to battling
			battling = true;
		}
	}
	return false;
}

static bool flee()
{
	if (battling)
	{
		std::cout << "You fled from the fight YOU started!\nPick your fights more carefully, coward...\n";
		battling = false;
	}
	else
	{
		std::cout << "This command can't be used outside of battle!\n";
	}
	return false;
}

static bool recover()
{
	if (!battling)
	{
		std::cout << "You rest and treat your wounds\n";
		dotdotdot();
		// player's current HP now back to max
		player.chp = player.mhp;
		std::cout << "Fully recovered, you observe your surroundings\n";
		// changes recovery message when randomly selecting
		if (death[player.loc])
		{
			// randomly select a location death message
			std::cout << locations[player.loc].dth[rand() % locations[player.loc].dth.size()];
		}
		else
		{
			// randomly select a location message
			std::cout << locations[player.loc].msg[rand() % locations[player.loc].msg.size()];
		}
	}
	else
	{
		std::cout << "This command can't be used during battle!\n";
	}
	return false;
}

static bool journey()
{
	if (!battling)
	{
		std::cout << "You set off to the next area, with dried slime on your hands...\n";
		dotdotdot();
		// checks if the location's level requirement is higher than the player's level
		if (locations.at(player.loc + 1).lvl > player.lvl)
		{
			std::cout << "You realize that the slimes there are too strong for you\nYou turn back\n";
		}
		else
		{
			// next location
			++player.loc;
			// at() will crash the program if beyond the vector's range. Any controlled location change does this
			std::cout << "You arrive at the " << locations.at(player.loc).nam << ". Your slaughter continues\n";
		}
	}
	else
	{
		std::cout << "This command can't be used during battle!\n";
	}
	return false;
}

static bool backtrack()
{
	if (!battling)
	{
		std::cout << "You retrace your steps to look for any stragglers...\n";
		dotdotdot();
		// previous location
		--player.loc;
		std::cout << "You arrive at " << locations.at(player.loc).nam << ". Your search resumes\n";
	}
	else
	{
		std::cout << "This command can't be used during battle!\n";
	}
	return false;
}

static bool leave()
{
	return true;
}
