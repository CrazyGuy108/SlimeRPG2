#ifndef GAME_HPP
#define GAME_HPP

#include "location.hpp"
#include "monster.hpp"
#include <string>
#include <vector>

class Player;

class Game
{
public:
	Game(Player& player, std::vector<Location>& locations);

	void start();

private:
	enum class State;

	// parses and executes a command
	void execute(const std::string& cmd);

	// commands
	void help();
	void stats();
	void fight();
	void flee();
	void recover();
	void journey();
	void backtrack();
	void leave();

	// helper methods
	void battle();
	void winBattle();
	void loseBattle();
	void dotdotdot();
	void sleep(unsigned milliseconds);

	Player& player;
	std::vector<Monster>::iterator monster;
	std::vector<Location>& locations;
	State state;
};

#endif // GAME_HPP
