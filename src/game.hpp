#ifndef GAME_HPP
#define GAME_HPP

#include "monster.hpp"
#include <string>
#include <vector>

class Player;
class World;

class Game
{
public:
	Game(Player& player, World& world);

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
	void rest();
	void advance();
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
	World& world;
	State state;
};

#endif // GAME_HPP
