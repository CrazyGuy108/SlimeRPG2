#include "game.hpp"
#include "location.hpp"
#include "monster.hpp"
#include "player.hpp"
#include "world.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

// the kinds of monsters that can be encountered
Monster monsters[]
{
	// name, currentHealth, maxHealth, level, experience, attack, defense,
	//  encounterMessage
	Monster
	{
		"Green Slime",
		5, 5, 1, 4, 3, 3,
		"A green Slime appeared!",
	},
	Monster
	{
		"Blue Slime",
		8, 8, 2, 6, 5, 5,
		"A blue Slime appears to avenge its little brother...",
	},
	Monster
	{
		"Red Slime",
		10, 10, 3, 8, 25, 0,
		"A Slime, red with fury, approaches you",
	},
	Monster
	{
		"Yellow Slime",
		16, 16, 4, 10, 3, 10,
		"A matured, yellow Slime confronts you",
	},
	Monster
	{
		"Ghost Slime",
		// good luck fighting THAT
		65535, 65535, 65535, 65535, 65535, 65535,
		"The ghost of your victims appears...",
	}
};

// a world full of different locations
World world
{
	// name, levelRequirement, enemies, recoveryMessages, killerMessages,
	//  exits
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
		},
		{ 1 }
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
		},
		{ 0, 2 }
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
		},
		{ 1, 3 }
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
		{ 2, 4 }
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
		},
		{ 3 }
	}
};

// the main player
Player player
{
	// name, currentHealth, maxHealth, level, experience, attack, defense,
	//  expRequired, location
	"Nameless Hero",
	10, 10, 1, 0, 5, 5, 10, &world.getLocation(0)
};

int main()
{
	std::cout << "What is your name? ";
	std::cin >> player.getName();
	std::cout << "\nType \"help\" for a list of commands\n\n";
	srand(time(NULL));
	Game game{ player, world };
	game.start();
	return 0;
}
