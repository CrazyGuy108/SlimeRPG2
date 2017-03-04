#include "SlimeRPG.hpp"
#include "location.hpp"
#include "monster.hpp"
#include "player.hpp"
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>

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
	// name, currentHealth, maxHealth, level, experience, attack, defense,
	//  expRequired, location
	"Nameless Hero",
	10, 10, 1, 0, 5, 5, 10, 0
};

// iterator pointing to the monster that the player is battling
Location::monster_iterator_t monster;

// list of monsters
Location::monster_container_t monsters
{
	// name, currentHealth, maxHealth, level, experience, attack, defense,
	//  encounterMessage
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
	// name, levelRequirement, enemies, recoveryMessages, killerMessages
	Location
	{
		"Slime Breeding Grounds", 1,
		{
			// 3 individual encounterable Green Slimes
			monsters[0], monsters[0], monsters[0]
		},
		{ // messages randomly displayed when recovering
			"Slimes, in their infancy, are green-colored, "
				"frolicking in the fields",
			"A bright green slime approaches you and asks, \"Mama?"
				"\"",
			"Some older green slimes seem to have a blue-ish tint "
				"to them"
		},
		{ // messages when you've killed every monster here
			"You don't see as much slimes here...",
			"Many slimes are living in fear now that their "
				"youthful generation is dead"
		}
	},
	Location // if you kill or injure a monster, it stays dead/injured
	{        // so you can essentially fight it again when you recover
		"Path of Slime", 2,
		{
			monsters[0], monsters[1], monsters[1]
		},
		{
			"You observe a group of blue-tinted green slimes "
				"mature into a complete blue",
			"Some younger green slimes follow their older blue "
				"friends, though still immature"
		},
		{
			"A golden flower seems to be judging you for your "
				"sins...",
			"A group of slimes seem to be talking about \"He\"..."
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
			"If a slime harbors anger for too long, it starts to "
				"acquire a red-ish tint",
			"An old rivalry of two slimes have turned them blood "
				"red with chronic hostility"
		},
		{
			"You observe a slime feeling triumphant now that its "
				"rival is dead for no reason",
			"It looks like that golden flower is talking to you..."
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
			"You observe matured yellow slimes training with some "
				"kind of slime weapon...",
			"It seems that blue slimes aren't actually mature, "
				"but more of a teenager"
		},
		{
			"A slime bullet flies past you. It seems that you are "
				"being hunted...",
			"You see a jar of peanut butter under a cardboard box "
				"held up by a stick"
		},
	},
	Location
	{
		"Slime Cemetery", 5,
		{
			monsters[4]
		},
		{
			"A funeral is taking place. You see dried slime being "
				"dumped into a grave",
			"How does a slime cry? I don't even know what I "
				"saw...",
			"Was that a ghost moaning just now?"
		},
		{
			"Wait you killed the ghost slime? Wow. Gg you dirty "
				"hacker..."
		}
	}
};

// string to be used as the command input
std::string cmd;

// used to check if the player is battling, so the command loop will change
//  the command options and whatever else
bool battling{ false };

int main()
{
	std::cout << "Loading...\n";
	dotdotdot();
	// initialize the rest of the player object
	
	// get player name to finish loading the game
	input(player.getName(), "Done!\nWhat is your name?\n\n");
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
			"sts - Stats....List the stats of your character and "
				"the monster\n"
			"fgt - Fight....*Chants* fite fite fite fite fite\n"
			"fle - Flee.....Only nubs flee, like you...\n";
	}
	else // regular help message
	{
		std::cout <<
			"hlp - Help........List available commands\n"
			"sts - Stats.......List the stats of your character\n"
			"rec - Recover.....Treat your wounds and rest, "
				"observing the scenery\n"
			"fgt - Fight.......Engage in battle with a nearby "
				"monster\n"
			"jrn - Journey.....Go forward to the next area\n"
			"bkt - Backtrack...Revisit the location you were just "
				"at\n"
			"lev - Leave.......Going so soon? Fine, but you can't "
				"save! >:D\n";
	}
	return false;
}

static bool stats()
{
	std::cout
		<< "name........." << player.getName() << '\n'
		<< "health......." << player.getCurrentHealth() << '/' <<
			player.getMaxHealth() << '\n'
		<< "level........" << player.getLevel() << '\n'
		<< "experience..." << player.getExperience() << '/' <<
			player.getExpRequired() << '\n'
		<< "attack......." << player.getAttack() << '\n'
		<< "defense......" << player.getDefense() << '\n'
		<< "location....." << locations[player.getLocation()]
			.getName() << '\n';
	if (battling) // also lists monster stats if battling
	{
		std::cout
			<< "\nMonster\n"
			<< "name....." << monster->getName() << '\n'
			<< "health..." << monster->getCurrentHealth() << '/' <<
				monster->getMaxHealth() << '\n'
			<< "level...." << monster->getLevel()
			<< (monster->getLevel() == 65535 ?
				"\nGetrekt nub\n" : "\n");
	}
	return false;
}

static bool fight()
{
	if (battling) // fights the monster if battling already
	{
		// player's turn
		// attack the monster
		uint16_t dmg{ player.damage(*monster) };
		// monster roasts you if you did only 1 damage
		if (dmg == 1)
		{
			std::cout << "You only did 1 damage...\n" <<
				monster->getName() <<
				": Gitgud nub >->\n";
			// you just got ROASTed!!!
			player.setRoasted(true);
		}
		else // regular non-roast message
		{
			std::cout << "You did " << dmg <<
				" damage to the slime!\n";
		}
		// checks if the monster died
		if (monster->isDead())
		{
			// good riddance
			// monster death message
			std::cout << "You mercilessly slaughtered the slime!\n"
				"You feel like a terrible person...\n";
			// special dialogue for if the monster insulted you
			//  before
			if (player.isRoasted())
			{
				std::cout << player.getName() <<
					": Who's the nub now? >->\n";
				player.setRoasted(false);
			}
			// exp gain
			std::cout << "You gained " <<
				monster->getExperience() << " exp!\n";
			// check if the player leveled up
			if (player.gainExperience(monster->getExperience()))
			{
				std::cout << "You leveled up to level " <<
					player.getLevel() << "!\n";
			}
			// remove monster from location's enemies vector
			locations[player.getLocation()].removeEnemy(monster);
			// the battle is now over
			battling = false;
			// no need to process the monster's next turn because
			//  it's already dead
			return false;
		}
		// now that you've taken your turn, it's the monster's turn now
		// be afraid, very afraid
		dmg = monster->damage(player);
		// checks if the damage dealt was only 1, indicating that a
		//  roast is necessary
		if (dmg == 1)
		{
			// player reminds the monster that they should gitgud
			std::cout << "The " << monster->getName() <<
				" did only did 1 damage...\n" <<
				player.getName() << ": Gitgud scrub >->\n";
			// oooh you just dissed that monster
			monster->setRoasted(true);
		}
		else
		{
			std::cout << monster->getName() << " did " <<
				dmg << " damage to you!\n";
		}
		// checks if the damage was too much for the player
		if (player.isDead())
		{
			// player death message
			std::cout << monster->getName() << " has killed you! "
				"Looks like you got a taste of your own "
				"medicine...\n";
			// special dialogue for fighting ghost slime
			if (monster->getLevel() == 65535)
			{
				std::cout << "Gg scrub\n";
			}
			// special dialogue for if the player insulted it
			//  before
			if (monster->isRoasted())
			{
				std::cout << monster->getName() <<
					": Who's the scrub now? >->\n";
			}
			// line break for clarity
			std::cout << '\n';
			// terminates the command loop because you are dead
			return true;
		}
	}
	else // if not already battling, attempt to initiate an encounter
	{
		std::cout << "You look around for a slime to fight\n";
		dotdotdot();
		// check if all the monsters are dead
		Location& l{ locations[player.getLocation()] };
		if (l.allMonstersDead())
		{
			std::cout << "But no slimes appear, and you have a "
				"feeling that none ever will\nHe's coming for "
				"you. Run...\n";
		}
		else
		{
			// get a random enemy from the current location
			monster = l.getRandomMonster();
			// plays the monster's encounter message
			std::cout << monster->getMessage() << '\n';
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
		std::cout << "You fled from the fight YOU started!\nPick your "
			"fights more carefully, coward...\n";
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
		player.recoverHealth();
		std::cout <<
			"Fully recovered, you observe your surroundings\n";
		// randomly select a recovery message
		const Location& l{ locations[player.getLocation()] };
		std::cout << l.getRandomMessage() << '\n';
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
		std::cout << "You set off to the next area, with dried slime "
			"on your hands...\n";
		dotdotdot();
		// checks if the location's level requirement is higher than
		//  the player's current level
		if (locations.at(player.getLocation() + 1)
			.getLevelRequirement() > player.getLevel())
		{
			std::cout << "You realize that the slimes there are "
				"too strong for you\nYou turn back\n";
		}
		else
		{
			// next location
			player.journey();
			// at() will crash the program if the index is beyond
			//  the vector's bounds
			std::cout << "You arrive at the " <<
				locations.at(player.getLocation()).getName() <<
				". Your slaughter continues\n";
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
		std::cout << "You retrace your steps to look for any "
			"stragglers...\n";
		dotdotdot();
		// previous location
		player.backtrack();
		std::cout << "You arrive at " << locations.at(
			player.getLocation()).getName() <<
			". Your search resumes\n";
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
