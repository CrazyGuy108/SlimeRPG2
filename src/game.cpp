#include "game.hpp"
#include "player.hpp"
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

enum class Game::State
{
	PLAYING, FIGHTING, DEAD
};

Game::Game(Player& player, std::vector<Location>& locations)
	: player{ player }, locations{ locations }, state{ State::PLAYING }
{
}

void Game::start()
{
	std::string cmd;
	while (state != State::DEAD)
	{
		std::cout << '\n';
		std::cin >> cmd;
		std::cout << '\n';
		execute(cmd);
	}
}

void Game::execute(const std::string& cmd)
{
	if (cmd == "hlp") // help
	{
		help();
	}
	else if (cmd == "sts") // stats
	{
		stats();
	}
	else if (cmd == "fgt") // fight
	{
		fight();
	}
	else if (cmd == "fle") // flee
	{
		flee();
	}
	else if (cmd == "rec") // recover
	{
		recover();
	}
	else if (cmd == "jrn") // journey
	{
		journey();
	}
	else if (cmd == "bkt") // backtrack
	{
		backtrack();
	}
	else if (cmd == "lev") // leave
	{
		leave();
	}
	else
	{
		std::cout << "Invalid command!\n";
	}
}

void Game::help()
{
	if (state == State::FIGHTING) // battle help message
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
}

void Game::stats()
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
	if (state == State::FIGHTING) // also lists monster stats if battling
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
}

void Game::fight()
{
	if (state == State::FIGHTING) // fights the monster if battling already
	{
		battle();
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
			state = State::FIGHTING;
		}
	}
}

void Game::flee()
{
	if (state == State::FIGHTING)
	{
		std::cout << "You fled from the fight YOU started!\nPick your "
			"fights more carefully, coward...\n";
		state = State::PLAYING;
	}
	else
	{
		std::cout << "This command can't be used outside of battle!\n";
	}
}

void Game::recover()
{
	if (state == State::FIGHTING)
	{
		std::cout << "This command can't be used during battle!\n";
	}
	else
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
}

void Game::journey()
{
	if (state == State::FIGHTING)
	{
		std::cout << "This command can't be used during battle!\n";
	}
	else
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
}

void Game::backtrack()
{
	if (state == State::FIGHTING)
	{
		std::cout << "This command can't be used during battle!\n";
	}
	else
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
	
}

void Game::leave()
{
	state = State::DEAD;
}

void  Game::battle()
{
	// player's turn
	// attack the monster
	uint16_t dmg{ player.damage(*monster) };
	// monster roasts you if you did only 1 damage
	if (dmg == 1)
	{
		std::cout << "You only did 1 damage...\n" <<
			monster->getName() << ": Gitgud nub >->\n";
		// you just got ROASTed!!!
		player.setRoasted(true);
	}
	else // regular non-roast message
	{
		std::cout << "You did " << dmg << " damage to the slime!\n";
	}
	// checks if the monster died
	if (monster->isDead())
	{
		winBattle();
		// no need to process the monster's next turn because it's
		//  already dead
		return;
	}
	// now that you've taken your turn, it's the monster's turn now
	// be afraid, very afraid
	dmg = monster->damage(player);
	// checks if the damage dealt was only 1, indicating that a roast is
	//  necessary
	if (dmg == 1)
	{
		// player reminds the monster that they should gitgud
		std::cout << "The " << monster->getName() << " did only did 1 "
			"damage...\n" << player.getName() << ": Gitgud scrub "
			">->\n";
		// oooh you just dissed that monster
		monster->setRoasted(true);
	}
	else
	{
		std::cout << monster->getName() << " did " << dmg << " damage "
			"to you!\n";
	}
	// checks if the damage was too much for the player
	if (player.isDead())
	{
		loseBattle();
	}
}

void Game::winBattle()
{
	// good riddance
	// monster death message
	std::cout << "You mercilessly slaughtered the slime!\nYou feel like a "
		"terrible person...\n";
	// special dialogue for if the monster insulted you before
	if (player.isRoasted())
	{
		std::cout << player.getName() << ": Who's the nub now? >->\n";
		player.setRoasted(false);
	}
	// exp gain
	std::cout << "You gained " << monster->getExperience() << " exp!\n";
	// check if the player leveled up
	if (player.gainExperience(monster->getExperience()))
	{
		std::cout << "You leveled up to level " << player.getLevel() <<
			"!\n";
	}
	// remove monster from location's enemies vector
	locations[player.getLocation()].removeEnemy(monster);
	// the battle is now over
	state = State::PLAYING;
}

void Game::loseBattle()
{
	// player death message
	std::cout << monster->getName() << " has killed you! Looks like you "
		"got a taste of your own medicine...\n";
	// special dialogue for fighting ghost slime
	if (monster->getLevel() == 65535)
	{
		std::cout << "Gg scrub\n";
	}
	// special dialogue for if the player insulted it before
	if (monster->isRoasted())
	{
		std::cout << monster->getName() << ": Who's the scrub now? >->"
			"\n";
	}
	// line break for clarity
	std::cout << '\n';
	// terminates the command loop because you are dead
	state = State::DEAD;
}

void Game::dotdotdot()
{
	std::cout << '.';
	sleep(1000);
	std::cout << '.';
	sleep(1000);
	std::cout << '.';
	sleep(1000);
	std::cout << '\n';
}

void Game::sleep(unsigned milliseconds)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}