#include "game.hpp"
#include "location.hpp"
#include "monster.hpp"
#include "player.hpp"
#include "world.hpp"
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

enum class Game::State
{
	PLAYING, FIGHTING, DEAD
};

Game::Game(Player& player, World& world)
	: player{ player }, world{ world }, monster{ nullptr }, monsterId{ 0 },
	state{ State::PLAYING }
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
	if (cmd == "help")
	{
		help();
	}
	else if (cmd == "stats")
	{
		stats();
	}
	else if (cmd == "fight")
	{
		fight();
	}
	else if (cmd == "flee")
	{
		flee();
	}
	else if (cmd == "rest")
	{
		rest();
	}
	else if (cmd == "travel")
	{
		travel();
	}
	else if (cmd == "leave")
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
			"help....List available commands\n"
			"stats...List the stats of your character and the "
				"monster\n"
			"fight...*Chants* fite fite fite fite fite\n"
			"flee....Only nubs flee, like you...\n";
	}
	else // regular help message
	{
		std::cout <<
			"help......List available commands\n"
			"stats.....List the stats of your character\n"
			"recover...Treat your wounds and rest, observing the "
				"scenery\n"
			"fight.....Engage in battle with a nearby monster\n"
			"travel....Attempt to go to another area\n"
			"leave.....Going so soon? Fine, but you can't save! "
				">:D\n";
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
		<< "location....." << player.getLocation()->getName() << '\n';
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
		Location& l{ *player.getLocation() };
		if (l.allMonstersDead())
		{
			std::cout << "But no slimes appear, and you have a "
				"feeling that none ever will\nHe's coming for "
				"you. Run...\n";
		}
		else
		{
			// get a random enemy from the current location
			monsterId = l.getRandomMonsterId();
			monster = l.getMonster(monsterId);
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

void Game::rest()
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
			"Fully recovered, you observe your surroundings\n" <<
			player.getLocation()->getRandomMessage() << '\n';
	}
}

void Game::travel()
{
	if (state == State::FIGHTING)
	{
		std::cout << "This command can't be used during battle!\n";
	}
	else
	{
		std::vector<size_t>& exits{ player.getLocation()->getExits() };
		for (size_t i{ 0 }; i < exits.size(); ++i)
		{
			std::cout << '(' << i << ") " <<
				world.getLocation(exits[i]).getName() << '\n';
		}
		std::cout << "Your choice: ";
		size_t choice;
		std::cin >> choice;
		if (std::cin.good())
		{
			if (choice < exits.size())
			{
				travelTo(exits[choice]);
			}
			else
			{
				std::cout << "You can't go to that area. "
					"Blame the dev.\n";
			}
		}
		else
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>
				::max(), '\n');
			std::cout << "That's not a valid input!\n";
		}
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
	player.getLocation()->removeEnemy(monsterId);
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

void Game::travelTo(size_t location)
{
	std::cout << "You set off to the next area, with dried slime on your "
		"hands...\n";
	dotdotdot();
	Location& l{ world.getLocation(location) };
	if (l.getLevelRequirement() > player.getLevel())
	{
		std::cout << "You realize that the slimes there are too "
			"strong for you\nYou turn back\n";
	}
	else
	{
		player.setLocation(&l);
		std::cout << "You arrive at the " << l.getName() <<
			". Your slaughter continues\n";
	}
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
